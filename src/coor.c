#include <stdio.h>
#include <math.h>
#include <allegro5/allegro.h>
//Create a new variable type, the coordinate
//this will represent a point in a 2D space and will be used not just for positions, but also for velocity
typedef struct coordinate
{
  float x;
  float y;
}coor; //define an (x,y) coordinate to work with

coor midpoint(coor c1, coor c2)
{//A function to easily get the midpoint between two points
  coor newCoor;
  newCoor.x = (c1.x + c2.x)/2;
  newCoor.y = (c1.y + c2.y)/2;
  return newCoor;
}

bool isInAsteroid(coor objPt, coor astPt, int astSize)
{ //a function to check if a coordinate is within the space of an asteroid
  if(abs(objPt.x - astPt.x) < astSize && abs(objPt.y - astPt.y) < astSize)
  {
    return true;
  }
  return false;
}
