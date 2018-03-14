#include "coor.h"
#include "drawing.h"
#include "sound.h"
#include "particle.h"

typedef struct asteroid
{
  coor location;
  coor velocity;
  int size;
} ast;

ast spawnAsteroid()
{
  ast newAst;
  newAst.location.x = rand() % SCREEN_W;
  newAst.location.y = rand() % SCREEN_H;
  newAst.velocity.x = (float) (rand() % 100 - 50)/100;
  newAst.velocity.y = (float) (rand() % 100 - 50)/100;
  newAst.size = rand() % 70 + 30;
  return newAst;
}



ast updateAsteroid(ast * a)
{
  a->location.x += a->velocity.x;
  a->location.y += a->velocity.y;
  a->location.x = a->location.x > SCREEN_W + a->size ? a->location.x - (SCREEN_W + a->size * 2) : a->location.x;
  a->location.y = a->location.y > SCREEN_H + a->size ? a->location.y - (SCREEN_H + a->size * 2) : a->location.y;
  a->location.x = a->location.x < -a->size ? a->location.x + (SCREEN_W + a->size * 2) : a->location.x;
  a->location.y = a->location.y < -a->size ? a->location.y + (SCREEN_H + a->size * 2) : a->location.y;
}

ast breakAsteroid(ast * a, coor bulVel)
{
  playExplosion();
  particleExplosion(a->location, 255, 255, 255);
  //This function handles splitting an asteroid into two smaller pieces
  //we input a pointer to the original asteroid and that pointer is used to change the original into a smaller piece.
  //Then a new asteroid, the second one, is created, and is returned by this function.
  //move the new asteroid to one half of the space the old one took up
  float slope = (double) ((bulVel.y)/(bulVel.x));
  double angleOfBreak = atan(slope) + PI/2;
  ast b;
  b = *a;
  a->location.x -= a->size * cos(angleOfBreak);
  a->location.y -= a->size * sin(angleOfBreak);
  //multiply the velocity of the new one by 2 in the opposite direction than it was going, BUT add an element of randomness.
  a->velocity.x *= cos(angleOfBreak) * 2.75;
  a->velocity.y *= sin(angleOfBreak) * 2.75;
  //Oh, and reduce the first halve's size
  a->size = a->size / 2;
  if (a->size < 5){a->size = 0;}
  b.location.x += b.size * cos(angleOfBreak);
  b.location.y += b.size * sin(angleOfBreak);
  //set B's velocity to A's velocity, but in the opposite direction. No random here.
  b.velocity = a->velocity;
  b.velocity.x *= -1;
  b.velocity.y *= -1;
  //set them both to the same size.
  b.size = a->size;
  if (a->size < 5){a->size = 0; b.size = 0;} //if the new asteroids gets too small, give it a size of 0.
  //Now they will be a vacant spot and will not be updated, but will be available for new asteroids to take the place of.
  return b;
}
