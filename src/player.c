#include "coor.h"
#include "asteroid.h"
#include "drawing.h"
#include "sound.h"
#include "particle.h"
#include <allegro5/allegro.h>

typedef struct player
{
  double dir; //Dir is in radians. We will use it to do math on the player's direction to do stuff with velocity
  int score;
  int lives;
  int respawn; //respawn timer after the player is killed
  coor location;
  coor velocity;
  int oneUpScore;
  float power; //how fast this player flies
  int maxBullets; //how many shots this player can have spawned at once
  int bullet; //how many shots this player does have at once
  bool canFire; //Can the player fire this frame?
  //This variable will be used to make sure the player can't hold the space key to spam lasers.
} player;

player newPlayer()
{
  player myPlayer;
  myPlayer.location.x = SCREEN_W/2;
  myPlayer.location.y = SCREEN_H/2;
  myPlayer.velocity.x = 0;
  myPlayer.velocity.y = 0;
  myPlayer.dir = 0;
  myPlayer.score = 0;
  myPlayer.lives = 3;
  myPlayer.respawn = 360;
  myPlayer.power = .1;
  myPlayer.maxBullets = 5;
  myPlayer.oneUpScore = 10000;
  myPlayer.bullet = 0;
  myPlayer.canFire = true;
  return myPlayer;
}

void killPlayer(player * p)
{
  printf("Looks like the player has died!");
  playExplosion();
  if (p->lives > 0)
  {
    printf(" Respawning...\n");
    p->lives--;
    p->respawn = 600; //600 ticks at 60 ticks a second would be 10 seconds
    //keep in mind that the player comes back at 300 ticks left and can fly around without limitation
    //but is invulnerable until p->respawn = 0
    p->location.x = SCREEN_W/2;
    p->location.y = SCREEN_H/2;
    p->velocity.x = 0;
    p->velocity.y = 0;
  }
  else
  {
    p->lives--;
    printf(" No lives left... \n");
    p->respawn = -1; //The player never respawns if this value is less than 0
  }
}

bool playerVsAst(player * p, ast * a, bool checkOnly)
{
  coor pVerts[6]; //Shorthand for Player Veriticies
  pVerts[0].x = cos(p->dir) * 22 + p->location.x;
  pVerts[0].y = sin(p->dir) * 22 + p->location.y;
  pVerts[1].x = cos(p->dir + PI/2) * 8 + p->location.x;
  pVerts[1].y = sin(p->dir + PI/2) * 8 + p->location.y;
  pVerts[2].x = cos(p->dir + PI/2) * 8 + p->location.x;
  pVerts[2].y = sin(p->dir + PI/2) * 8 + p->location.y;
  pVerts[3] = midpoint(pVerts[0], pVerts[1]);
  pVerts[4] = midpoint(pVerts[1], pVerts[2]);
  pVerts[5] = midpoint(pVerts[0], pVerts[2]);
  bool asteroidHit = false;
  for (int i = 0; i < 6; i++)
  {
    if(isInAsteroid(pVerts[i], a->location, a->size) && a->size != 0)
    {
      asteroidHit = true;
      particleExplosion(pVerts[i], 255, 165, 0);
      break;
    }
  }
  if (asteroidHit && !checkOnly)
  {
    printf("Player was hit by an asteroid at (%f, %f), with a size of %d\n",a->location.x, a->location.y, a->size);
    killPlayer(p);
    return true;
  }else if (asteroidHit)
  {
    return true;
  }
  return false;
}

player boundPlayer(player * p) //this function handles the player going out of bounds.
{ //right now it just keeps the player in the screen, using the screen height and width to do stuff
  p->location.x = p->location.x > SCREEN_W + 35 ? p->location.x - (SCREEN_W + 60) : p->location.x;
  p->location.y = p->location.y > SCREEN_H + 35 ? p->location.y - (SCREEN_H + 60) : p->location.y;
  p->location.x = p->location.x < -35 ? p->location.x + (SCREEN_W + 60) : p->location.x;
  p->location.y = p->location.y < -35 ? p->location.y + (SCREEN_H + 60) : p->location.y;
  return *p;
}
