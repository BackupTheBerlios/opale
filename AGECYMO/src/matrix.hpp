#ifndef CLASS_MATRIX_H
#define CLASS_MATRIX_H

#include <iostream>
//#include <math>

#include "point.hpp"
#include "vector.hpp"

using namespace gml;

/****************************************************/
/*    3D MATRIX                                     */
/*     m[0]  m[1]  m[2]  m[3]                       */
/*     m[4]  m[5]  m[6]  m[7]                       */
/*     m[8]  m[9]  m[10] m[11]                      */
/*     m[12] m[13] m[14] m[15]                      */
/****************************************************/
class Matrix3D
{
 public:
  double m[16];

  Matrix3D    ();
  Matrix3D    (double, double, double, double,
               double, double, double, double,
               double, double, double, double,
               double, double, double, double);
  
  void     loadIdentity();
  
  Vector3D operator*   (const Vector3D&);
  Point3D  operator*   (const Point3D&);
  Matrix3D operator*   (const Matrix3D&);

  static Matrix3D scale(double, double, double);
  static Matrix3D rotationX(double);
  static Matrix3D rotationY(double);
  static Matrix3D rotationZ(double);
  static Matrix3D translation(double, double, double);
};

ostream& operator<< (ostream& os, const Matrix3D &mat);

#endif
