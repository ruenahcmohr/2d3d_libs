
// number type fallback #define with gcc paramiter -DDIMTYPE3D=float
#ifndef DIMTYPE3D
  #define DIMTYPE3D double
#endif


#ifndef header3d_h
  #define header3d_h
  
#define pt3(X,Y,Z) ((point3d_t){X,Y,Z})

#define Project3d(P,d)  Scale3d((P),pt3(1.0/(P->z/d), 1.0/(P->z/d), 0));

  typedef struct point3d_s {
    DIMTYPE3D x, y, z;
  } point3d_t;

  void   Init3d      (point3d_t *this) ;
  double Dist3d      (point3d_t this, point3d_t that) ;
  void   Set3d       (point3d_t *this, point3d_t that) ;
  void   Scale3d     (point3d_t *this, point3d_t that) ;
  void   Rotate3d    (point3d_t *this, point3d_t that) ;
  void   Translate3d (point3d_t *this, point3d_t that) ;
  void   Print3d     (point3d_t *this) ;



#endif
