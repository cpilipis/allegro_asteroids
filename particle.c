#include "coor.h"
#include "drawing.h"
#include <math.h>

typedef struct particle
{
  coor location;
  coor velocity;
  int color[3];
  int timeout;
} part;

part particles [100] = {};
int partIndex = 0;

void partIndexInc()
{
  partIndex++;
  if (partIndex == 100){partIndex = 0;}
}

void newParticle(coor loc, coor vel, int r, int g, int b)
{
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
{
  p->location.x += p->velocity.x;
  p->location.y += p->velocity.y;
  p->timeout--;
}
void particleExplosion(coor loc, int r, int g, int b)
{
  for (int i = 0; i < 16; i++)
  {
    part p;
    p.location = loc;
    p.velocity.x = cos(2*PI - i * PI/8);
    p.velocity.y = sin(2*PI - i * PI/8);
    p.color[0] = r;
    p.color[1] = g;
    p.color[2] = b;
    p.timeout = 80;
    particles[partIndex] = p;
    partIndexInc();
  }
}
