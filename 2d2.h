#ifndef __2d_h
#define __2d_h

#include <math.h>
#include "Stuff.h"

/*******************************

  all angles are in rads less polar, which is in degs

 for cartesian, X is amplitude, and Y is the angle in degrees

*******************************/


#define pt2 pt
#define pt(X,Y) ((point2d_t){X,Y})
#define l2d(A,B) ((line2d_t){A,B})

#define rotCos(A) cos(deg2rad(A))
#define rotSin(A) sin(deg2rad(A))

#define point2dDistSquared(A,B)   (SQR(A.x-B.x)+SQR(A.y-B.y))
#define geom2dOriginDistP(A)      (sqrt(SQR(A.x)+SQR(A.y)) )

//Are two points within a given distance of each other?     point, point, distance
#define pointsAreWithin(A,B,C)   (point2dDistSquared(A,B)<=(C*C))

// the dot product will tell you if the two vectors are on the same major heading or not
#define dot2d(A,B)  ((A.x*B.x)+(A.y*B.y))
#define vectDotPoint(A,B,P)   ( (P.x - B.x) * (B.x - A.x)  +  (P.y - B.y) * (B.y - A.y) )

// the cross product will tell you if the other vector is to your left or right
#define cross2d(A,B) ((A.x*B.y)-(A.y*B.x))
#define vectCrossPoint(A,B,P) ( (P.x - B.x) * (B.y - A.y)  -  (P.y - B.y) * (B.x - A.x) )

// positive for clockwise triangles
#define signedTriArea(A,B,C) (A.x*(C.y - B.y) + B.x*(A.y - C.y) + C.x*(B.y - A.y))/2

//#define geom2dOriginAngleP(A)     

// inclusive between
#define  colinearIsBetween(P,L) (vectDotPoint(L.p1, P, L.p2)>=0?1:0)
#define TOLERANCE 0.000000001
#define  colinearIsBetweenX(P,L) (vectDotPoint(L.p1, P, L.p2)>=(-TOLERANCE)?1:0)
#define  colinear(A,B,C)        (vectCrossPoint(A, B, C)==0?1:0)

#define GEOM2DPOINTDIR(A,B,P)   (SIGN(vectCrossPoint(A,B,P)))

/* 

  the following should jsut be macros:

  set, scale, offset


*/
typedef struct point2d_s {  // point
  double x, y;
} point2d_t;


typedef struct line2d_s {  // line
  point2d_t p1;
  point2d_t p2;
} line2d_t;

typedef struct arc2d_s {   // arc
  point2d_t c;      // centre   overlaps with point and first point on line.
  double    r;      // primary / circle radius
  double    r2;     // secondary radius for elliptical arc
  double    start;  // start angle
  double    end;    // end angle
  double    zrot;   // elliptical arc, offset angle.
} arc2d_t;



typedef struct vect2d_s {   // vector
  double t;
  double r;
} vect2d_t;

typedef struct line2dGF_s { // general form line
  double A, B, C;
} line2dGF_t;

typedef struct line2dHV_s {  // hybrid vector, used for chopping/extending lines
  point2d_t origin;
  vect2d_t  stroke;
} line2dHV_t;



// --- math support ---

double posatan2(point2d_t p);


// --- points and point things ---

point2d_t * point2dSet                 (point2d_t *p, point2d_t to);
point2d_t * point2dTranslate           (point2d_t *p, point2d_t by) ;
point2d_t * point2dRotateZ             (point2d_t *p, double by) ;
point2d_t * point2dRotateZAround       (point2d_t *p, point2d_t around, double by) ;
point2d_t * point2dScale               (point2d_t *p, point2d_t by) ;
point2d_t * point2dScaleAround         (point2d_t *p, point2d_t around, point2d_t by);
char      * point2d2s                  (char *s, int bl, point2d_t this) ;
void        point2dShow                (point2d_t p, char * pre, char * post);

point2d_t * point2dCart2Polar          (point2d_t *p, point2d_t cart);
point2d_t * point2dPolar2Cart          (point2d_t *p, point2d_t polar);

//vect2d_t  * point2Vect               (vect2d_t *v, point2d_t this);
//point2d_t * vect2Point               (point2d_t *p, vect2d_t v);

// --- lines and line things ---

line2d_t    * line2dInit               (line2d_t *l) ;
line2d_t    * line2dSet                (line2d_t *l, double x1, double y1, double x2, double y2) ;
line2d_t    * line2dSetPts             (line2d_t *l, point2d_t this, point2d_t that);
line2d_t    * line2dSetLine            (line2d_t *l, line2d_t to);
line2d_t    * line2dTrans              (line2d_t *l, point2d_t by) ;
line2d_t    * line2dRot                (line2d_t *l, double by) ;
line2d_t    * line2dRotAround          (line2d_t *l, point2d_t around, double by) ;
line2d_t    * line2dScale              (line2d_t *l, point2d_t by) ;
line2d_t    * line2dSetLen             (line2d_t *l, double to);        // the first point stays the same
line2d_t    * line2dOffset             (line2d_t *l, double by);
char        * line2d2s                 (char *s, int bl, line2d_t  this) ;
// joinLines
// 

line2dGF_t  * line2dLine2General       (line2dGF_t *g1, line2d_t this);

// --- arcs and arc things ---


arc2d_t     * arc2dInit                (arc2d_t *a) ;
arc2d_t     * arc2dSet                 (arc2d_t *a, double x1, double y1, double r, double start, double end) ;
arc2d_t     * arc2dSetPR               (arc2d_t *a, point2d_t c, double r, double start, double end);
arc2d_t     * arc2dSetArc              (arc2d_t *a, arc2d_t to);
arc2d_t     * arc2dTrans               (arc2d_t *a, point2d_t by);
arc2d_t     * arc2dRot                 (arc2d_t *a, point2d_t around, double by);
arc2d_t     * arc2dRotAround           (arc2d_t *a, point2d_t around, double by);
arc2d_t     * arc2dScale               (arc2d_t *a, point2d_t by);// !!!???!!!
arc2d_t     * arc2dScaleAround         (arc2d_t *a, point2d_t around, point2d_t by); // !!!???!!!
arc2d_t     * arc2dGetArcOn            (arc2d_t * a, point2d_t  this, point2d_t  that, point2d_t  other);
char        * arc2d2s                  (char *s, int bl, arc2d_t  this);    


// ------ geometry stuff ----

#define       geom2dDistPP(PA,PB)          (sqrt(point2dDistSquared(PA, PB)))
//double      geom2dDistPP                 (point2d_t this, point2d_t that);
double        geom2dAcute                  (point2d_t this, point2d_t that, point2d_t other);
point2d_t *   geom2dCentroid               (point2d_t *c, point2d_t this, point2d_t that, point2d_t other);
point2d_t *   geom2dGetOffset              (point2d_t *result, point2d_t this, point2d_t that);
double        geom2dGetAngleBetween        (point2d_t this, point2d_t that); 
double        geom2dTriArea                (point2d_t this, point2d_t that, point2d_t other) ;
unsigned int  geom2dIsPtInTri              (point2d_t P, point2d_t A, point2d_t B, point2d_t C) ;

point2d_t *   geom2dGetMidPoint            (point2d_t *mp, line2d_t l);
point2d_t *   geom2dGetSegmentIntersection (point2d_t * is, line2d_t  this, line2d_t  that);
unsigned char geom2dIsLineTouchingLine     (line2d_t this, line2d_t that);
point2d_t *   geom2dGetIntersection        (point2d_t * is, line2d_t  this, line2d_t  that);
point2d_t *   geom2dGetIntersectionGF      (point2d_t * is, line2dGF_t g1, line2dGF_t g2);
point2d_t *   geom2dGetClosestPointLine    (point2d_t *is, point2d_t this, line2d_t that);
double        geom2dGetClosestDistLine     (point2d_t this, line2d_t that);
unsigned char geom2dIsPointCloseToLine     (point2d_t p, line2d_t l, double t) ;
unsigned char geom2dIsPointOnLine          (point2d_t p, line2d_t l);
unsigned char geom2dIsPointPerp            (line2d_t base, point2d_t this);
         char geom2dPointDir               (point2d_t A, point2d_t B, point2d_t P);

// inclusive
// P is point, A is circle (arc)
#define     geom2dIsPointInCircle(P,A)   ((point2dDistSquared(P, A.c) <= SQR(A.r))?1:0)
#define     geom2dDoCirclesTouch(AA,AB)  ((geom2dDistPP(AA.c,AB.c) <= (AA.r+AB.r))?1:0)

// R is line (kittycorner straight rect)
#define     geom2dIsPointInRect(P,R)     ((WITHINI(R.p1.x, R.p2.x, P.x) & WITHINI(R.p1.y, R.p2.y, P.y))?1:0) 

// T is threshold
//#define     geom2dIsPointOnLine(P,L,T)   (ABS((L.p1.y - L.p2.y)*(L.p1.x - P.x) -( (L.p1.x - L.p2.x)*(L.p1.y - P.y))) <= T)?1:0

#endif

/*

closest point on line


 line segment a -> b, point c, projection of point onto line segment is (c-a).(b-a)/||b-a|| + a, unless the closest point is a or b
 
(c-a).(b-a)/||b-a||^2 * (b-a) + a

(b-a)/||b-a|| is a vector in the direction going from a to b, of unit length.  
(c-a) is a vector going from a to c.  
dot them together to find how much of the vector going from a to c, is in the direction of a to b.  
then multiply that magnitude by (b-a)/||b-a|| to get a directional vector, and add it to a



*/

















































