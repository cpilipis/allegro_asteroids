#include "coor.h"
#include "player.h"
#include "drawing.h"
#include "asteroid.h"

typedef struct bullet
{ //the type for the laser the player fires
  coor velocity;
  coor location;
  int age; //used to despawn bullets after a time, ticks down to 0
  player *parent;
}bul;

bul fire(player * p)
{ //Put a shot at the tip of the player's ship with the player's velocity direction.
  bul shot;
  //Spawn a bullet at the tip of the player ship's nose
  shot.location.x = cos(p->dir) * 25 + p->location.x;
  shot.location.y = sin(p->dir) * 25 + p->location.y;
  //Give the bullet a velocity based on the ship's direction
  shot.velocity.x = cos(p->dir) * 10;
  shot.velocity.y = sin(p->dir) * 10;
  shot.age = 60;
  shot.parent = p; //The bullet now knows the player's memory addess, so we can increase the player's score when this bullet hits something
  return shot;
}


bul updateShot(bul * b)
{ //Move a shot by its velocity an loop it around the screen.
  b->location.x += b->velocity.x;
  b->location.y += b->velocity.y;
  b->location.x = b->location.x > SCREEN_W + 35 ? b->location.x - (SCREEN_W + 60) : b->location.x;
  b->location.y = b->location.y > SCREEN_H + 35 ? b->location.y - (SCREEN_H + 60) : b->location.y;
  b->location.x = b->location.x < -35 ? b->location.x + (SCREEN_W + 60) : b->location.x;
  b->location.y = b->location.y < -35 ? b->location.y + (SCREEN_H + 60) : b->location.y;
  if (b->age != 0)
  { //oh, and age the shot.
    b->age--;
  }
  return *b;
}


ast checkAst(ast * a, bul * shot)
{ //Check if the shot is inside an asteroid
  //if so, we'll return two asteroids, one that is alive and may or may not be split up,
  //and another that may or may not be a live asteroid or a dead filler.
  float shotX = shot->location.x;
  float shotY = shot->location.y;
  float astX = a->location.x;
  float astY = a->location.y; //shorthands for these respective values
  if(isInAsteroid(shot->location, a->location, a->size) && shot->age != 0)
  {
    //return the split up new asteroids
    shot->age = 0;//kill the shot
    shot->parent->score += 100 - a->size; //reward the player who fired the asteroid with points
    if (shot->parent->score > shot->parent->oneUpScore){shot->parent->oneUpScore += 10000; shot->parent->lives++;} //If the score is enough for a one-up, grant a one-up
    return breakAsteroid(a, shot->velocity);
  }
  else
  { //If the shot isn't in an asteroid
    //return a filler asteroid with size 0 anyways
    ast b;
    b.location = a->location;
    b.velocity = a->velocity;
    b.size = 0;
    return b;
  }
}
