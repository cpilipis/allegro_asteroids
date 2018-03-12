#include "coor.h"
#include "player.h"
#include "drawing.h"
#include "asteroid.h"

typedef struct bullet
{
  coor velocity;
  coor location;
  int age; //used to despawn bullets
  player *parent;
}bul;

bul fire(player * p)
{
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
{
  b->location.x += b->velocity.x;
  b->location.y += b->velocity.y;
  b->location.x = b->location.x > SCREEN_W + 35 ? b->location.x - (SCREEN_W + 60) : b->location.x;
  b->location.y = b->location.y > SCREEN_H + 35 ? b->location.y - (SCREEN_H + 60) : b->location.y;
  b->location.x = b->location.x < -35 ? b->location.x + (SCREEN_W + 60) : b->location.x;
  b->location.y = b->location.y < -35 ? b->location.y + (SCREEN_H + 60) : b->location.y;
  if (b->age != 0)
  {
    b->age--;
  }
  return *b;
}


ast checkAst(ast * a, bul * shot)
{
  float shotX = shot->location.x;
  float shotY = shot->location.y;
  float astX = a->location.x;
  float astY = a->location.y; //shorthands for these respective values
  if(isInAsteroid(shot->location, a->location, a->size) && shot->age != 0)
  {
    //return the split up new asteroids
    shot->age = 0;//kill the shot
    shot->parent->score += 100 - a->size;
    if (shot->parent->score > shot->parent->oneUpScore){shot->parent->oneUpScore += 10000; shot->parent->lives++;}
    coor thing;
    return breakAsteroid(a, shot->velocity);
  }
  else
  {
    //return a filler asteroid with size 0 anyways
    ast b;
    b.location = a->location;
    b.velocity = a->velocity;
    b.size = 0;
    return b;
  }
}
