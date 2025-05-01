#include <math.h>
#include "Stuff.h"

typedef  double dist;  // in mm
typedef  double angle;      // in degrees

// rebuild angle units to anything you want  - this is for degrees

//#define fromRads(A) ((A)*180.0/M_PI)
//#define toRads(A)   ((A)*M_PI/180.0)



dist dist3d(dist p1x, dist p1y, dist p1z, dist p2x, dist p2y, dist p2z);
angle elbow(dist C, dist A, dist B); // returns angle c
angle dir(dist x, dist y);
