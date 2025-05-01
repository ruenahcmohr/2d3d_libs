

#include  <math.h>
#include  "3d.h"
#include  <stdio.h>
#include  "Stuff.h"


void Init3d      (point3d_t *this) { 
  this->x = 0;
  this->y = 0;
  this->z = 0;
}

double Dist3d   (point3d_t this, point3d_t that) { 
    return sqrt(SQR((this.x)-(that.x)) + SQR((this.y)-(that.y)) + SQR((this.z)-(that.z)) );
}

void Set3d       (point3d_t *this, point3d_t that) { 
  this->x = that.x;
  this->y = that.y;
  this->z = that.z;
}

void Scale3d     (point3d_t *this, point3d_t that) { 
  this->x *= that.x;
  this->y *= that.y;
  this->z *= that.z;
}

void Rotate3d    (point3d_t *this, point3d_t that) { 

  point3d_t temp;
  
  // x rotation
   temp.y  = (this->y * cos(deg2rad(that.x))) - (this->z * sin(deg2rad(that.x)));
   this->z = (this->y * sin(deg2rad(that.x))) + (this->z * cos(deg2rad(that.x)));
   this->y = temp.y;
    
  // y rotation
   temp.z = (this->z * cos(deg2rad(that.y))) - (this->x * sin(deg2rad(that.y)));
   this->x = (this->z * sin(deg2rad(that.y))) + (this->x * cos(deg2rad(that.y)));
   this->z = temp.z;
     
  // z rotation
   temp.x = (this->x * cos(deg2rad(that.z))) - (this->y * sin(deg2rad(that.z)));
   this->y = (this->x * sin(deg2rad(that.z))) + (this->y * cos(deg2rad(that.z)));
   this->x = temp.x;
}

void Translate3d (point3d_t *this, point3d_t that) { 
  this->x += that.x;
  this->y += that.y;
  this->z += that.z;
}

void Print3d(point3d_t *this) {
  printf("Point <%f, %f, %f>\n", this->x, this->y, this->z);
}

