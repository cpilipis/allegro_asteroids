#include "coor.h"
#include "drawing.h"
#include <math.h>
//Let's create the particle type, for representing on screen particles, like those seen after the player blows up an asteroid.
typedef struct particle
{
  coor location;
  coor velocity;
  int color[3];
  int timeout;
} part;
//particles have a location and velocity, a timeout for timing how long it takes them to die, and a color.
int maxParticles = 150;
part particles[150] = {}; //I would put maxParticles inside the size of particles, but that causes an error.
int partIndex = 0; //Instead of handling the particle table in the main loop, we'll just handle it within the particle functions directly
//In hindsight, I could have done this with the asteroids and shots and the like as well

void partIndexInc()
{
  partIndex++;
  printf("%d\n", partIndex);
  if (partIndex == maxParticles){partIndex = 0;} //increment the index of the particles with bound checking so that once we make the 100th particle, it loops back to 0
  //at this point, particle 0 will be a dead particle
}

void newParticle(coor loc, coor vel, int r, int g, int b)
{ //create a new particle given a point, velocity, and color
  //It will use a default timeout of 1 second
  part p;
  p.location = loc;
  p.velocity = vel;
  p.color[0] = r;
  p.color[1] = g;
  p.color[2] = b;
  p.timeout = 60;
  particles[partIndex] = p;
  partIndexInc();
}
void updateParticle(part *p)
{ //update the particle by moving it and ticking the timeout
  p->location.x += p->velocity.x;
  p->location.y += p->velocity.y;
  p->timeout--;
}
void particleExplosion(coor loc, int r, int g, int b)
{//Create an explosion of particles in all directions
  for (int i = 0; i < 16; i++)
  {
    part p;
    p.location = loc;
    p.velocity.x = cos(2*PI - i * PI/8); //get the X and Y of the velocity based on cos and sin of which one this is.
    p.velocity.y = sin(2*PI - i * PI/8); //For example, the first one would have a yvel of 0 and xvel of 1, the fifth one would go up and a little left, etc.
    p.color[0] = r;
    p.color[1] = g;
    p.color[2] = b;
    p.timeout = 60;
    particles[partIndex] = p;
    partIndexInc();
  }
}
