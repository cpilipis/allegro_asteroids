#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "coor.h"
#include "player.h"
#include "shot.h"
#include "asteroid.h"
#include "HUD.h"
#include "sound.h"
#include "particle.h"

#include <allegro5/allegro.h>
#include "allegro5/allegro_primitives.h"
enum MYKEYS {
 KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE
};


void drawPlayer(player * p)
{
  coor front = {cos(p->dir) * 22 + p->location.x, sin(p->dir) * 22 + p->location.y};
  coor top = {cos(p->dir + PI/2) * 8 + p->location.x, sin(p->dir + PI/2) * 8 + p->location.y};
  coor bottom = {cos(p->dir + 3*PI/2) * 8 + p->location.x, sin(p->dir + 3*PI/2) * 8 + p->location.y};
  al_draw_triangle(top.x, top.y, bottom.x, bottom.y, front.x, front.y, al_map_rgb(255, 255, 255), 0);
}


void drawShot(bul * b)
{
  float laserX = b->location.x;
  float laserMiddleX = b->location.x - b->velocity.x;
  float laserY = b->location.y;
  float laserMiddleY = b->location.y - b->velocity.y;
  al_draw_line(laserX, laserY, laserMiddleX, laserMiddleY, al_map_rgb(255, 100, 100), 0);
}
void drawParticle(part * p)
{
  al_draw_circle(p->location.x, p->location.y, 0.5, al_map_rgb(p->color[0], p->color[1], p->color[2]), 0);
}
void drawAsteroid(ast * a)
{
  al_draw_circle(a->location.x, a->location.y, a->size, al_map_rgb(255, 255, 255), 0);
}

void respawnAsteroids(ast a [], int numOfAsteroids, int maxAst)
{
  for (int i = 0; i < numOfAsteroids; i++)
  {
    a[i] = spawnAsteroid(); //spawn a certain number of asteroids that are live into the array
  }
  for (int i = numOfAsteroids; i < maxAst; i++)
  {
    a[i].location.x = 0;
    a[i].location.y = 0;
    a[i].velocity.x = 0;
    a[i].velocity.y = 0;
    a[i].size = 0; //spawn a dead asteroid
  }
}

int main(int argc, char **argv)
{
  srand(time(NULL));
  ALLEGRO_DISPLAY *display = NULL;
  ALLEGRO_EVENT_QUEUE *event_queue = NULL;
  ALLEGRO_TIMER *timer = NULL;
  bool key[5] = {false, false, false, false, false};
  bool redraw = true;
  bool doexit = false;
  player myPlayer = newPlayer();
  bul shots [25] = {};
  const int maxAst = 100;
  ast asteroids[100] = {};
  int particleTick = 0; //This will be used to time the spawning of particles from the player's thruster
  int countShots = 0;
  int astSpawnCount = 3;
  int astSpawnTimer = -1;

  respawnAsteroids(asteroids, astSpawnCount, maxAst);


  if(!al_init())
  {
    fprintf(stderr, "failed to initialize allegro!\n");
    return -1;
  }

  if(!al_install_keyboard())
  {
    fprintf(stderr, "failed to initialize the keyboard!\n");
    return -1;
  }

  timer = al_create_timer(1.0 / FPS);
  if(!timer)
  {
    fprintf(stderr, "failed to create timer!\n");
    return -1;
  }

  display = al_create_display(SCREEN_W, SCREEN_H);
  if(!display) {
    fprintf(stderr, "failed to create display!\n");
    al_destroy_timer(timer);
    return -1;
  }
  bool prim = al_init_primitives_addon();
  if(!prim)
  {
    fprintf(stderr, "failed to init primitives!\n");
    al_destroy_timer(timer);
    return -1;
  }

  event_queue = al_create_event_queue();
  if(!event_queue)
  {
    fprintf(stderr, "failed to create event_queue!\n");
    al_shutdown_primitives_addon();
    al_destroy_display(display);
    al_destroy_timer(timer);
    return -1;
  }

  bool fonts = al_init_font_addon();
  if(!fonts)
  {
    fprintf(stderr, "failed to init fonts!\n");
    al_shutdown_primitives_addon();
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
    return -1;
  }
  bool funts = al_init_ttf_addon();
  if(!funts)
  {
    fprintf(stderr, "failed to init fonts!\n");
    al_shutdown_primitives_addon();
    al_shutdown_font_addon();
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
    return -1;
  }
  bool sounds = al_install_audio();
  if (!sounds)
  {
    fprintf(stderr, "failed to init sounds!\n");
    al_shutdown_primitives_addon();
    al_shutdown_font_addon();
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
    al_shutdown_ttf_addon();
    return -1;
  }
  bool soundCodec = al_init_acodec_addon();
  if (!soundCodec)
  {
    fprintf(stderr, "failed to init sounds!\n");
    al_shutdown_primitives_addon();
    al_shutdown_font_addon();
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
    al_uninstall_audio();
    al_shutdown_ttf_addon();
    return -1;
  }

  initHud();
  initSounds();

  al_register_event_source(event_queue, al_get_display_event_source(display));

  al_register_event_source(event_queue, al_get_timer_event_source(timer));

  al_register_event_source(event_queue, al_get_keyboard_event_source());

  al_clear_to_color(al_map_rgb(0,0,0));

  al_flip_display();

  al_start_timer(timer);
  bool gamePaused = false;
  menu();
  al_flip_display();
  bool start = false;
  while(!start)
  {
    ALLEGRO_EVENT sev;
    al_wait_for_event(event_queue, &sev);
    if (sev.type == ALLEGRO_EVENT_KEY_DOWN)
    {
      start = true;
    }
    else if(sev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
      doexit = true;
      start = true;
    }
  }
  while(!doexit)
  {
    ALLEGRO_EVENT ev;
    al_wait_for_event(event_queue, &ev);
    if(gamePaused){}
    if(ev.type == ALLEGRO_EVENT_TIMER && !gamePaused)
    {
      particleTick++;
      if (myPlayer.respawn < 300 && myPlayer.respawn >= 0) //If the player respawned 5 seconds ago or longer
      {
        if (key[KEY_LEFT]){myPlayer.dir -= PI/30;}
        else if(key[KEY_RIGHT]){myPlayer.dir += PI/30;}
        if (key[KEY_UP])
        {
          coor newVel = {cos(myPlayer.dir) * myPlayer.power, sin(myPlayer.dir) * myPlayer.power};
          myPlayer.velocity.x += newVel.x;
          myPlayer.velocity.y += newVel.y;
          float opDir = myPlayer.dir + PI + ((float)(rand() % 100)/100 * PI/2 - PI/4);
          coor opVel;
          opVel.x = cos(opDir);
          opVel.y = sin(opDir);
          newParticle(myPlayer.location, opVel, 255, 100, 0);
        }
        myPlayer.location.x += myPlayer.velocity.x;
        myPlayer.location.y += myPlayer.velocity.y;
        myPlayer = boundPlayer(&myPlayer);
        if (key[KEY_SPACE] && myPlayer.canFire == true)
        {
          playShoot();
          if (countShots < 25)
          {
            //if we have room for new shots in our array, put the new shot fired there.
            shots[countShots] = fire(&myPlayer);
            countShots++;
          }
          else
          {
            //if there's not enough room, scan the main shots array for dead shots and replace those
            int i = 0;
            for (i; i < countShots; i++)
            {
              if (shots[i].age <= 0){break;}
            }
            if (shots[i].age <= 0){shots[i] = fire(&myPlayer);} //Make sure we didn't just get to the end of the array only to find a live shot.
          }
          myPlayer.canFire = false;
        }
        else if(!key[KEY_SPACE] && !key[KEY_DOWN])
        {
          myPlayer.canFire = true;
        }
        if(myPlayer.respawn != 0){myPlayer.respawn--;}
      }
      else
      {
        myPlayer.respawn--;
        stopThrustSound();
      }
      if (astSpawnTimer > -1)
      {
        astSpawnTimer--;
        if (astSpawnTimer == 0)
        {
          astSpawnCount++;
          respawnAsteroids(asteroids, astSpawnCount, maxAst);
        }
      }
      //update asteroids
      int liveCount = 0;
      int deadCount = 0;
      ast *liveAst [maxAst];
      ast *deadAst [maxAst];
      //These arrays will store pointers to the alive and dead asteroids respectively
      //first we check which asteroids are alive and which are dead. An asteroid with size 0 is a dead asteroid.
      for (int i = 0; i < maxAst; i++)
      {
        if(asteroids[i].size > 0)
        {
          updateAsteroid(&asteroids[i]);
          while (astSpawnTimer == 0 && playerVsAst(&myPlayer, &asteroids[i], true))
          {
            asteroids[i] = spawnAsteroid();
          }
          liveAst[liveCount] = &asteroids[i];
          liveCount++;
          if(myPlayer.respawn == 0){playerVsAst(&myPlayer, &asteroids[i], false);}
        }
        else
        {
          deadAst[deadCount] = &asteroids[i];
          deadCount++;
        }
      }
      if (liveCount == 0 && astSpawnTimer == -1)
      {
        astSpawnTimer = 180;
      }

      //update shots
      //oh, and collide shots with asteroids
      int deadIndex = 0;
      for (int i = 0; i < countShots; i++)
      {
        if(shots[i].age > 0)
        {
          shots[i] = updateShot(&shots[i]);
        }
        else
        {
          continue;
        }
        for (int a = 0; a < liveCount; a++)
        {
          ast maybeDeadAst = checkAst(liveAst[a], &shots[i]);
          if (maybeDeadAst.size != 0)
          {
            *deadAst[deadIndex] = maybeDeadAst;
	          deadIndex++;
          }
          if (shots[i].age == 0){break;}
        }
      }
      //update particles
      for(int i = 0; i < 100; i++)
      {
        if(particles[i].timeout > 0){updateParticle(&particles[i]);}
      }
      redraw = true;
    }
    else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
      doexit = true;
    }
    else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
    {
      switch(ev.keyboard.keycode)
      {
        case ALLEGRO_KEY_UP:
          key[KEY_UP] = true;
          if(myPlayer.respawn < 300 && myPlayer.respawn > -1){playThrust();}
          else{stopThrustSound();}
          break;

        case ALLEGRO_KEY_DOWN:
          key[KEY_DOWN] = true;
          break;

        case ALLEGRO_KEY_LEFT:
          key[KEY_LEFT] = true;
          break;

        case ALLEGRO_KEY_RIGHT:
          key[KEY_RIGHT] = true;
          break;

        case ALLEGRO_KEY_SPACE:
          key[KEY_SPACE] = true;
          break;
      }
    }
    else if(ev.type == ALLEGRO_EVENT_KEY_UP)
    {
      switch(ev.keyboard.keycode)
      {
        case ALLEGRO_KEY_UP:
          key[KEY_UP] = false;
          stopThrustSound();
          break;

        case ALLEGRO_KEY_DOWN:
          key[KEY_DOWN] = false;
          break;

        case ALLEGRO_KEY_LEFT:
          key[KEY_LEFT] = false;
          break;

        case ALLEGRO_KEY_RIGHT:
          key[KEY_RIGHT] = false;
          break;

        case ALLEGRO_KEY_ESCAPE:
          if (gamePaused){gamePaused = false;}
          else
          {
            gamePaused = true;
            drawPaused();
            al_flip_display();
          }
          break;

        case ALLEGRO_KEY_SPACE:
          key[KEY_SPACE] = false;
          break;
      }
    }

    if(redraw && al_is_event_queue_empty(event_queue))
    {
      redraw = false;
      al_clear_to_color(al_map_rgb(0,0,0));
      //If player is not dead, or player just respawned and is not at a certain tick.
      //Setting it so that some frames the player draws gives the player a flashing effect when invulnerable.
      if((myPlayer.respawn/10 % 2 != 0 && myPlayer.respawn < 300 && myPlayer.respawn > 0) || myPlayer.respawn == 0){drawPlayer(&myPlayer);}
      for (int i = 0; i < countShots; i++)
      {
        if(shots[i].age != 0){drawShot(&shots[i]);}
      }
      for (int i = 0; i < maxAst; i++)
      {
        if(asteroids[i].size > 0){drawAsteroid(&asteroids[i]);}
      }
      for(int i = 0; i < 100; i++)
      {
        if(particles[i].timeout > 0){drawParticle(&particles[i]);}
      }
      drawPlayerHud(myPlayer.score, myPlayer.lives);
      al_flip_display();
    }
  }
  al_destroy_timer(timer);
  al_destroy_display(display);
  al_destroy_event_queue(event_queue);
  al_shutdown_primitives_addon();
  al_uninstall_audio();
  //al_shutdown_font_addon();
  //al_shutdown_ttf_addon();
  killHud();
  return 0;
}
