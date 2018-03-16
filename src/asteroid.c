#include "coor.h"
#include "drawing.h"
#include "sound.h"
#include "particle.h"

typedef struct asteroid
{
  coor location;
  coor velocity;
  int size;
} ast; //The asteroid structure carries it's location, velocity, and size

ast spawnAsteroid()
{
  ast newAst;
  newAst.location.x = rand() % SCREEN_W;
  newAst.location.y = rand() % SCREEN_H;
  newAst.velocity.x = (float) (rand() % 100 - 50)/100;
  newAst.velocity.y = (float) (rand() % 100 - 50)/100;
  newAst.size = rand() % 70 + 30;
  //spawn an asteroid at a random spot with a random slow velocity and a random size between a radius of 30 and 100 pixels
  return newAst;
}



ast updateAsteroid(ast * a)
{
  //add the asteroid's velocity to it's location, and loop it around the screen
  a->location.x += a->velocity.x;
  a->location.y += a->velocity.y;
  a->location.x = a->location.x > SCREEN_W + a->size ? a->location.x - (SCREEN_W + a->size * 2) : a->location.x;
  a->location.y = a->location.y > SCREEN_H + a->size ? a->location.y - (SCREEN_H + a->size * 2) : a->location.y;
  a->location.x = a->location.x < -a->size ? a->location.x + (SCREEN_W + a->size * 2) : a->location.x;
  a->location.y = a->location.y < -a->size ? a->location.y + (SCREEN_H + a->size * 2) : a->location.y;
}

ast breakAsteroid(ast * a, coor bulVel)
{
  /*
  KilL tHe aSTeROid!11!!1!
  this function accepts the pointer to the asteroid being destroyed so we can change it to a smaller asteroid
  and it returns another smaller asteroid
  this is how you pump multiple asteroids out of one function
  */
  playExplosion();
  particleExplosion(a->location, 255, 255, 255); //make a graphical explosion
  //move the new asteroid to one half of the space the old one took up
  //and figure out which way it was blown up to determine which direction the asteroid should split in half
  float slope = (double) ((bulVel.y)/(bulVel.x));
  double angleOfBreak = atan(slope) + PI/2; //use the arctangent of the slope to get the angle from which it broke
  ast b;
  b = *a; //We create our second asteroid and, for now, set it to exactly the same as the one that was blown up.
  //We'll use these old values to help build the new one
  a->location.x -= a->size * cos(angleOfBreak);
  a->location.y -= a->size * sin(angleOfBreak); //use the angle to choose the location of the first one
  //multiply the velocity of the new one by 2 in the opposite direction than it was going.
  a->velocity.x *= cos(angleOfBreak) * 2.75;
  a->velocity.y *= sin(angleOfBreak) * 2.75;
  //Oh, and reduce the first halve's size
  a->size = a->size / 2;
  if (a->size < 5){a->size = 0;}
  b.location.x += b.size * cos(angleOfBreak);
  b.location.y += b.size * sin(angleOfBreak); //like what we did with a, but in the opposite direction
  //set B's velocity to A's velocity, but in the opposite direction.
  b.velocity = a->velocity;
  b.velocity.x *= -1;
  b.velocity.y *= -1;
  //set them both to the same size.
  b.size = a->size;
  if (a->size < 5){a->size = 0; b.size = 0;} //if the new asteroids gets too small, give it a size of 0.
  //Now they will be a vacant spot and will not be updated, but will be available for new asteroids to take the place of.
  return b;
}
