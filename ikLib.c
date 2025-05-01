
#include "ikLib.h"

/*
length units are mm
angle units are degrees

len   = dist3d(dist p1x, dist p1y, dist p1z, dist p2x, dist p2y, dist p2z);
angle = elbow(dist d, dist l1, dist l2);
angle = dir(dist x, dist y);
 
*/

dist dist3d(dist p1x, dist p1y, dist p1z, dist p2x, dist p2y, dist p2z){
  return sqrt(SQR(p1x-p2x) + SQR(p1y-p2y) + SQR(p1z-p2z));
}

angle elbow(dist C, dist A, dist B){ // returns angle c
  return  rad2deg(
            acos(   
               ((double)SQR(A)+(double)SQR(B)-(double)SQR(C)) / ((double)2*(double)A*(double)B) 
            ) 
           );
}

angle dir(dist x, dist y){
  return rad2deg(atan2(y, x));
}

