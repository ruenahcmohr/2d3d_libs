#include "2d2.h"

/************************************************************


line-line interaction
  can have 3 states, non-intersecting, intersecting, and overlapping.
  
  

****************************************************************/



double posatan2(point2d_t p){

  double rv;
  
  rv = rad2deg(atan2(p.y, p.x));  
  
  if (rv < 0) {  return rv+360;   }     
                 return rv;
  

}

// ================================================================= points and point things ===================================================================

inline point2d_t * point2dSet(point2d_t *p, point2d_t to) {
   p->x = to.x;
   p->y = to.y;
   return p;
}

inline point2d_t * point2dTranslate(point2d_t *p, point2d_t by) {
   p->x += by.x;
   p->y += by.y;
   return p;
}

// positive rotation is counterclockwise
point2d_t * point2dRotateZ(point2d_t *p, double by) {
   double xtemp; //, ytemp;
   double cosTheta, sinTheta;

  cosTheta = rotCos(by);
  sinTheta = rotSin(by);
  
   xtemp =             (p->x * cosTheta) - (p->y * sinTheta);
 /*ytemp =*/ p->y =    (p->x * sinTheta) + (p->y * cosTheta);
 
   p->x = xtemp;
/* p->y = ytemp;*/
   return p;
}


point2d_t * point2dRotateZAround(point2d_t *p, point2d_t around, double by) {
   double xtemp; //, ytemp;
   double cosTheta, sinTheta;  
   
   cosTheta = rotCos(by);
   sinTheta = rotSin(by);
   
   xtemp =  around.x + (((p->x) - (around.x)) * cosTheta) - (((p->y) - (around.y)) * sinTheta);
   p->y  =  around.y + (((p->x) - (around.x)) * sinTheta) + (((p->y) - (around.y)) * cosTheta); 
   p->x  =  xtemp;

   return p;
}


// scale p by by around 0
inline point2d_t * point2dScale(point2d_t *p, point2d_t by) {
  p->x *= by.x;
  p->y *= by.y;
  return p;
}

point2d_t * point2dScaleAround(point2d_t *p, point2d_t around, point2d_t by) {    
  p->x = ((p->x - around.x)* by.x ) + around.x;
  p->y = ((p->y - around.y)* by.y ) + around.y;
  return p;
}


// point to string.
char * point2d2s(char *s, int bl, point2d_t this){
    snprintf(s, bl, "%0.3f, %0.3f", this.x, this.y);
    return s;
}


void  point2dShow (point2d_t this, char * pre, char * post) {
    printf("%s %0.3f, %0.3f %s", pre, this.x, this.y, post);
}


//
// x <-> radius    y <-> theta
//
point2d_t * point2dCart2Polar(point2d_t *p, point2d_t cart){
  
  (*p).x = geom2dOriginDistP(cart);  
  (*p).y = posatan2(cart);
  
  return p;
}



//
// x <-> radius    y <-> theta
//
point2d_t * point2dPolar2Cart(point2d_t *p, point2d_t polar){

  (*p).y = polar.x * sin(deg2rad(polar.y)); 
  (*p).x = polar.x * cos(deg2rad(polar.y));

  return p;
}



//vect2d_t  * point2Vect                   (vect2d_t *v, point2d_t this);


//point2d_t * vect2Point                   (point2d_t *p, vect2d_t v);


// ========================================================= lines and line things ==================================================================


inline line2d_t *line2dInit(line2d_t *l) {
  l->p1.x = 0;
  l->p1.y = 0;
  l->p2.x = 1;
  l->p2.y = 0;
  return l;
}

inline line2d_t *line2dSet(line2d_t *l, double x1, double y1, double x2, double y2) {
  l->p1.x = x1;  l->p1.y = y1;
  l->p2.x = x2;  l->p2.y = y2;
  return l;
}

inline line2d_t    * line2dSetPts(line2d_t *l, point2d_t this, point2d_t that){
  point2dSet(&(l->p1), this);
  point2dSet(&(l->p2), that);
  return l;
}


inline line2d_t    * line2dSetLine (line2d_t *l, line2d_t to){
  point2dSet(&(l->p1), to.p1);
  point2dSet(&(l->p2), to.p2);
}


inline line2d_t *line2dTrans(line2d_t *l, point2d_t by) {
  point2dTranslate(&l->p1, by);
  point2dTranslate(&l->p2, by);
  return l;
}


line2d_t *line2dRot(line2d_t *l, double by) {  
   double xtemp; //, ytemp;
   double cosTheta, sinTheta;  
  
   cosTheta = rotCos(by);
   sinTheta = rotSin(by);
  
   xtemp   = (l->p1.x * cosTheta) - (l->p1.y * sinTheta);
   l->p1.y = (l->p1.x * sinTheta) + (l->p1.y * cosTheta); 
   l->p1.x = xtemp;

   xtemp   = (l->p2.x * cosTheta) - (l->p2.y * sinTheta);
   l->p2.y = (l->p2.x * sinTheta) + (l->p2.y * cosTheta); 
   l->p2.x = xtemp;
  
  return l;
}

line2d_t  * line2dRotAround(line2d_t *l, point2d_t around, double by) { 
   double xtemp; //, ytemp;
   double cosTheta, sinTheta;  
   
   cosTheta = rotCos(by);
   sinTheta = rotSin(by);
   
   xtemp    =  around.x + (((l->p1.x) - (around.x)) * cosTheta) - (((l->p1.y) - (around.y)) * sinTheta);
   l->p1.y  =  around.y + (((l->p1.x) - (around.x)) * sinTheta) + (((l->p1.y) - (around.y)) * cosTheta); 
   l->p1.x  =  xtemp;
  
   xtemp    =  around.x + (((l->p2.x) - (around.x)) * cosTheta) - (((l->p2.y) - (around.y)) * sinTheta);
   l->p2.y  =  around.y + (((l->p2.x) - (around.x)) * sinTheta) + (((l->p2.y) - (around.y)) * cosTheta); 
   l->p2.x  =  xtemp;
  
  return l;
}

line2d_t * line2dScale(line2d_t *l, point2d_t by) {
  point2dScale(&l->p1, by);
  point2dScale(&l->p2, by);
  return l;
}

// keep first point the same, modify second point.
line2d_t    * line2dSetLen             (line2d_t *l, double to){
  point2d_t temp;
  
  point2dTranslate( &(l->p2), pt(-l->p1.x, -l->p1.y)); // move line to 0,0  
  temp.y = posatan2(l->p2);
  temp.x = to;                       // modify the radius
  point2dPolar2Cart(&(l->p2), temp); // convert back to cartesion
  point2dTranslate( &(l->p2), l->p1);// offset by origional position.

  return l;

}


line2d_t    * line2dOffset   (line2d_t *l, double by){

  line2d_t  temp;
  point2d_t offset;
  
  line2dSetLine(&temp, *l);
  // rotate the line around point 1 by 90 degrees
  point2dRotateZAround  (&(temp.p2), temp.p1, 90) ;
  // change length to {by}
  line2dSetLen(&temp, by);
  // get difference of origional point 1 and new point 2
  geom2dGetOffset (&offset, temp.p2, l->p1);
  // translate both points by that amount
  line2dTrans (l, offset) ;

  return l;

}


char * line2d2s(char *s, int bl, line2d_t  this){
    char t1[255];
    char t2[255];
    snprintf(s, bl, "%s -> %s", point2d2s( t1, 254 , this.p1), point2d2s( t2, 254, this.p2));
    return s;
}



/*
  A*x + B*y = C
*/
line2dGF_t * line2dLine2General(line2dGF_t *g1, line2d_t this){    
  double dx, dy;
  
  g1->B = (this.p2.x) - (this.p1.x);
  g1->A = (this.p1.y) - (this.p2.y);
  
  // convert one line
  if (0) {
  // are points a vert  line?
  } else if (g1->B == 0) {
    g1->A = 1;
    g1->C = this.p1.x;
  // are points a horiz line?  
  } else if (g1->A == 0) {
    g1->B = 1;
    g1->C = this.p1.y;
  // regular line  
  } else {
    g1->C = -((this.p2.y) * (-(g1->B)) - ((this.p2.x) * (g1->A)));
  }
    
  return g1;

}



// =========================================== arcs and arc things =====================================================

arc2d_t     * arc2dInit  (arc2d_t *a) { 
 a->c.x   = 0;
 a->c.y   = 0;
 a->r     = 0;
 a->start = 0;
 a->end   = 360;
 return a;
}


arc2d_t     * arc2dSet     (arc2d_t *a, double x1, double y1, double r, double start, double end) { 
 a->c.x   = x1;
 a->c.y   = y1;
 a->r     = r;
 a->start = start;
 a->end   = end;
 return a;
}


arc2d_t     * arc2dSetPR      (arc2d_t *a, point2d_t c, double r, double start, double end){ 
 point2dSet(&(a->c), c);
 a->r     = r;
 a->start = start;
 a->end   = end;
 return a;
}


arc2d_t     * arc2dSetArc    (arc2d_t *a, arc2d_t to){ 
 a->c.x   = to.c.x;
 a->c.y   = to.c.y;
 a->r     = to.r;
 a->start = to.start;
 a->end   = to.end;
 return a;
}


arc2d_t     * arc2dTrans     (arc2d_t *a, point2d_t by){ 
 point2dTranslate(&(a->c), by);
 return a; 
}

arc2d_t     * arc2dRot       (arc2d_t *a, point2d_t around, double by){ 
 point2dRotateZ(&(a->c),  by) ;
 a->start += by;
 a->end   += by; 
 return a;
}

arc2d_t     * arc2dRotAround    (arc2d_t *a, point2d_t around, double by){ 
 point2dRotateZAround(&(a->c), around, by) ;
 a->start += by;
 a->end   += by; 
 return a;
}


arc2d_t     * arc2dScale        (arc2d_t *a, point2d_t by){ // position and size
 point2dScale(&(a->c), by);
 a->r *= by.x; // !!!???!!! oh damnit, what have I done!  
 return a;
} 


arc2d_t     * arc2dScaleAround         (arc2d_t *a, point2d_t around, point2d_t by){ // position and size
 point2dScaleAround(&(a->c), around, by);
 a->r *= by.x; // !!!???!!! oh damnit, what have I done!  
 return a;
} 




/*
  find the arc that hits the 3 given points
*/
arc2d_t * arc2dGetArcOn( arc2d_t * a, point2d_t this, point2d_t that, point2d_t other) {

  line2d_t    s1, s2;
  point2d_t m1, m2;
  //char      s[255];
  
  // create lines between the two points
  line2dSetPts(&s1, this, that);
  line2dSetPts(&s2, that, other);
  
  // rotate them 90 degrees around their midpoint
  line2dRotAround(&s1, *geom2dGetMidPoint(&m1, s1), deg2rad(90.0));  
  line2dRotAround(&s2, *geom2dGetMidPoint(&m2, s2), deg2rad(90.0));  
  
  // find the intersection -> arc centre
  geom2dGetIntersection(&(a->c), s1, s2);
  
  // find the radius
  a->r = geom2dDistPP(a->c, that);
  
  // start angle 0, end angle 0
  a->start = 0;
  a->end   = 0;

  return a;
}


// tell me about it.
char * arc2d2s  (char *s, int bl, arc2d_t  this) {
   char t[255];

    snprintf(s, bl, "c -> %s, r -> %f, start angle: %f, stop angle: %f", point2d2s( t, 254 , this.c), this.r, this.start, this.end);
    return s;
} 





// ==================================================== geometry stuff ==================================================================


unsigned int geom2dIsPtInTri( point2d_t P, point2d_t A, point2d_t B, point2d_t C) {

  point2d_t  v0, v1, v2;
  double dot00, dot01, dot02, dot11, dot12;
  double invDenom, u, v;
  
  geom2dGetOffset(&v0, C, A);
  geom2dGetOffset(&v1, B, A);
  geom2dGetOffset(&v2, P, A);
  
  dot01 = dot2d(v0, v1);
  dot02 = dot2d(v0, v2);
  dot12 = dot2d(v1, v2);
  
  dot00 = dot2d(v0, v0);
  dot11 = dot2d(v1, v1);
  
  invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
  u = (dot11 * dot02 - dot01 * dot12) * invDenom;
  v = (dot00 * dot12 - dot01 * dot02) * invDenom;
  
  if ((u >= 0) && (v >= 0) && (u + v < 1)) {
    return 1;     
  } else {
    return 0;
  }

}

/*

answer is -180 -> 180 depending on if other is clockwise or counterclockwise of this.

*/
double geom2dAcute (point2d_t this, point2d_t that, point2d_t other){

    point2d_t t1, t2, tc;
    point2d_t c1, c2;
    double a;          
    
    geom2dGetOffset(&t1, this, that);
    geom2dGetOffset(&t2, other, that);
        
    // x <-> radius    y <-> theta
    point2dCart2Polar(&c1, t1);
    point2dCart2Polar(&c2, t2);   
     
    a = c2.y - c1.y;

  //  printf("Uncorrected angle is: c1 %f - c2 %f = %f \n", c1.y, c2.y, a);
    
    if (0) {
    } else if (a > 180.0) { // we want the smaller angle. (reflex angle)
      a = -360 + a;
    } else if (a < -180.0) {
      a = 360 + a;
    }       
    
  //  if ((a < -180) || (a > 180)) {      printf("error, angle is %f\n", a);    }
           
    return a;
    
}


point2d_t * geom2dCentroid    (point2d_t *c, point2d_t this, point2d_t that, point2d_t other) {

  c->x = ((this.x)+(that.x)+(other.x))/3;
  c->y = ((this.y)+(that.y)+(other.y))/3;

  return c;

}

inline point2d_t * geom2dGetOffset    (point2d_t *result, point2d_t this, point2d_t that) {
  result->x = (this.x - that.x);   result->y = (this.y - that.y);
  return result;
}


double geom2dGetAngleBetween(point2d_t this, point2d_t that) {
  point2d_t temp1, temp2;
  
  geom2dGetOffset(&temp1, this, that);
  
  return posatan2(temp1)+90; // no idea why I need this fudge just yet

}



point2d_t * geom2dGetMidPoint(point2d_t *mp, line2d_t l){
  mp->x = ((l.p1.x)+(l.p2.x))/2;
  mp->y = ((l.p1.y)+(l.p2.y))/2;
  return mp;
}

/*
  This will return NULL if the two segments dont intersect within their length
*/
point2d_t * geom2dGetSegmentIntersection(point2d_t * is, line2d_t this, line2d_t that) {

   point2d_t intersect;

   if (geom2dGetIntersection( &intersect,  this, that) == NULL) return NULL;
   
   // because we know the point is true for both lines, we can do a simple test to make sure its within the lines scope
   if (InLimits(intersect.x ,this.p1.x, this.p2.x) && InLimits(intersect.y ,this.p1.y, this.p2.y) &&
       InLimits(intersect.x ,that.p1.x, that.p2.x) && InLimits(intersect.y ,that.p1.y, that.p2.y) ) {    
   
 //  if ( geom2dIsPointOnLine(intersect, this ) && geom2dIsPointOnLine(intersect, that )) {  // much slower
     is->x = intersect.x;
     is->y = intersect.y;
     return is;
     
   }else{
     return NULL;
   }
 
}


/*
  General form of line in A*x + B*y - C = 0   
  returns NULL if the lines are parallel
*/
point2d_t * geom2dGetIntersection(point2d_t * is, line2d_t  this, line2d_t  that) {
  line2dGF_t g1, g2;
  
  // to general form
  line2dLine2General(&g1, this);  // printf("A = %f, B = %f, C = %f\n", g1.A, g1.B, g1.C );
  line2dLine2General(&g2, that);  // printf("A = %f, B = %f, C = %f\n", g2.A, g2.B, g2.C );
    
  return geom2dGetIntersectionGF(is, g1, g2);

}


char geom2dPointDir(point2d_t A, point2d_t B, point2d_t P){
 
  return SIGN(vectCrossPoint(A,B,P));
  
}



/*  about 70000 intersection tests/ms on my machine  */
unsigned char geom2dIsLineTouchingLine(line2d_t this, line2d_t that) {

  char det0, det1, det2, det3;
  
  det0 = geom2dPointDir(this.p1, this.p2, that.p1); // 4 way projection test
  det1 = geom2dPointDir(this.p1, this.p2, that.p2);
  det2 = geom2dPointDir(that.p1, that.p2, this.p1);
  det3 = geom2dPointDir(that.p1, that.p2, this.p2);
  
  if ((det0 != det1) && (det2 != det3))
    return 1;
    printf("determinant fail\n");
  
  if ((colinearIsBetween(this.p1, that))==1) return 1; 
  printf("colinear fail 1\n");
  if ((colinearIsBetween(this.p2, that))==1) return 1;
  printf("colinear fail 2\n");
  if ((colinearIsBetween(that.p1, this))==1) return 1;
  printf("colinear fail 3\n");
  if ((colinearIsBetween(that.p2, this))==1) return 1;
  printf("colinear fail 4\n");
  
  return 0;
  
} 


point2d_t * geom2dGetIntersectionGF(point2d_t * is, line2dGF_t g1, line2dGF_t g2) {
 
  
  // find out of lines are parallel
  if (((g1.A*g2.B)-(g1.B*g2.A)) == 0)  {
    // printf("Lines are Parallel\n");
    
    // !!!???!!! hey, but are they overlapping?
    
    return NULL;
  }
  
  // automagic intersection formula,
  is->y = ((g2.A * g1.C) - (g2.C * g1.A)) / ((g2.A * g1.B) - ( g2.B * g1.A )); 
  if (g1.A != 0.0) {
    is->x = (g1.C - g1.B*is->y)/g1.A;
  } else {
    is->x = (g2.C - g2.B*is->y)/g2.A;
  }
  
  return is;

}



point2d_t *  geom2dGetClosestPointLine(point2d_t *is, point2d_t this, line2d_t that) {
  line2d_t intersector;
  line2dGF_t orig, solver;

  if (geom2dIsPointPerp  (that, this)) {

    line2dSetLine( &intersector, that);
    line2dRot( &intersector, 90);
    
    line2dLine2General(&solver, intersector);  
    line2dLine2General(&orig, that);  
    solver.C =  solver.A * this.x + solver.B * this.y;  // move the rotated line to go thru the point.
    geom2dGetIntersectionGF(is, orig, solver);
  
  } else {
 
    // we return the closest end of the line.
    if (point2dDistSquared(this, that.p1) < point2dDistSquared(this,that.p2)) {
       point2dSet(is, that.p1);
    } else {
       point2dSet(is, that.p2);
    }
 
  }  
    
  return is;

}


// if the point is not int eh perpendicular space of the line, it will return the distance to the nearest line endpoint
double  geom2dGetClosestDistLine (point2d_t this, line2d_t that){
  double  RV;
  double d1, d2, d3;
  
  d1 = point2dDistSquared(that.p1, that.p2);
  d2 = point2dDistSquared(that.p1, this);
  d3 = point2dDistSquared(that.p2, this);

  if ( (d3 <= (d1+d2)) & (d2 <= (d1+d3)) ) {   
    RV = (2*geom2dTriArea(this, that.p1, that.p2))/sqrt(d1);    
  } else {   
    RV = sqrt(Min(d2, d3));    
  }  
    
  return RV; 
}


unsigned char geom2dIsPointOnLine(point2d_t p, line2d_t l) {

  // colinear check, cross product
  if (!colinear(p,l.p1, l.p2)) return 0;
  return colinearIsBetween(p, l);
   
}


unsigned char geom2dIsPointCloseToLine(point2d_t p, line2d_t l, double t) {
   return ((geom2dGetClosestDistLine(p, l) < t)?1:0);   
}




double geom2dTriArea(point2d_t this, point2d_t that, point2d_t other) {
   double v;

 //  v = (this.x*(that.y - other.y) + that.x*(other.y - this.y) + other.x*(this.y - that.y))/2;
  
 v = signedTriArea(this,that,other);
 return ABS(v);
   
  // return ABS(signedTriArea(this,that,other));
}


// is point in the perpendicular space of a segment?
// we can do this by checking the two dot products
unsigned char geom2dIsPointPerp  (line2d_t base, point2d_t this) {

  point2d_t  v0, v1, v2, v3;
  double dot01, dot02; 

  geom2dGetOffset(&v0, this,    base.p1);
  geom2dGetOffset(&v1, base.p2, base.p1);
  geom2dGetOffset(&v2, this,    base.p2);
  geom2dGetOffset(&v3, base.p1, base.p2);

  dot01 = dot2d(v0, v1);
  dot02 = dot2d(v2, v3); 
  
 // printf("real: 1: %03f  2: %03f  -  \n", dot01, dot02);  
  
  if (SIGN(dot01) == SIGN(dot02)) {
    return 1;     
  } else {
    return 0;
  }
  





/*
  double d1, d2, d3;
  
  d1 = point2dDistSquared(base.p1, base.p2);
  d2 = point2dDistSquared(base.p1, this);
  d3 = point2dDistSquared(base.p2, this);
  
  if (d3 > (d1+d2)) return 0;
  if (d2 > (d1+d3)) return 0;
  return 1;
  */
  
}



/*

// is point on line

bool geomIsPointOnLine(point, line, thres) {

   return ((l.p1.y - l.p2.y)*(l.p1.x - p.x) -( (l.p1.x - l.p2.x)*(l.p1.y - p.y)) < thres)?1:0
  

}





*/






























