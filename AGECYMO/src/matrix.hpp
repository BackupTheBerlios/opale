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

  /**************************************************************
   *
   *  Matrix default constructor
   *
   *************************************************************/
  Matrix3D    ();

  /**************************************************************
   *
   *  Matrix constructor with all values
   *
   *************************************************************/
  Matrix3D    (double, double, double, double,
               double, double, double, double,
               double, double, double, double,
               double, double, double, double);
  
  /**************************************************************
   *
   *  load the identity matrix
   *
   *************************************************************/
  void     loadIdentity();
  
  /**************************************************************
   *
   *  define * operator for vector
   *
   *************************************************************/
  Vector3D operator*   (const Vector3D&);
  
  /**************************************************************
   *
   *  define * operator for point
   *
   *************************************************************/
  Point3D  operator*   (const Point3D&);

  /**************************************************************
   *
   *  define * operator for another matrix
   *
   *************************************************************/
  Matrix3D operator*   (const Matrix3D&);

  /**************************************************************
   *
   *  scale the matrix with x,y,z value
   *
   *************************************************************/
  static Matrix3D scale(double, double, double);

  /**************************************************************
   *
   *  rotatation operation on X axe
   *
   *************************************************************/
  static Matrix3D rotationX(double);

  /**************************************************************
   *
   *  rotatation operation on Y axe
   *
   *************************************************************/
  static Matrix3D rotationY(double);

  /**************************************************************
   *
   * rotatation operation on Z axe
   *
   *************************************************************/
  static Matrix3D rotationZ(double);

  /**************************************************************
   *
   *  translation with x,y,z value
   *
   *************************************************************/
  static Matrix3D translation(double, double, double);
};

ostream& operator<< (ostream& os, const Matrix3D &mat);

#endif
