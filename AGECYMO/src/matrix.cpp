#include "matrix.hpp"


Matrix3D::Matrix3D
()
{
  loadIdentity();
}

Matrix3D::Matrix3D 
(double m0_p,  double m1_p,  double m2_p,  double m3_p,
 double m4_p,  double m5_p,  double m6_p,  double m7_p,
 double m8_p,  double m9_p,  double m10_p, double m11_p,
 double m12_p, double m13_p, double m14_p, double m15_p)
{
  m[0] = m0_p;  m[1] = m1_p;  m[2] = m2_p;  m[3] = m3_p;
  m[4] = m4_p;  m[5] = m5_p;  m[6] = m6_p;  m[7] = m7_p;
  m[8] = m8_p;  m[9] = m9_p;  m[10]= m10_p; m[11]= m11_p;
  m[12]= m12_p; m[13]= m13_p; m[14]= m14_p; m[15]= m15_p;
}

void
Matrix3D::loadIdentity
()
{
  m[0] = 1;   m[1] = 0;   m[2] = 0;  m[3] = 0;
  m[4] = 0;   m[5] = 1;   m[6] = 0;  m[7] = 0;
  m[8] = 0;   m[9] = 0;   m[10]= 1;  m[11]= 0;
  m[12]= 0;   m[13]= 0;   m[14]= 0;  m[15]= 1;
}

Vector3D
Matrix3D::operator*  // Multiplie (x,y,z,0) par la matrice puis jette la 4e comp (qui est nulle)
(const Vector3D& vec_p)
{
  Vector3D v1;

  v1[0] = m[0] * vec_p[0] + m[1] * vec_p[1] + m[2] * vec_p[2];
  v1[1] = m[4] * vec_p[0] + m[5] * vec_p[1] + m[6] * vec_p[2];
  v1[2] = m[8] * vec_p[0] + m[9] * vec_p[1] + m[10] * vec_p[2];
  
  return v1;
  
//     Vector3D(m[0]*vec_p[0] + m[1]*vec_p[1] + m[2]*vec_p[2],
//              m[4]*vec_p[0] + m[5]*vec_p[1] + m[6]*vec_p[2],
//              m[8]*vec_p[0] + m[9]*vec_p[1] + m[10]*vec_p[2]);
}

Point3D
Matrix3D::operator*
(const Point3D& pt_p)   // Multiplie (x,y,z,1) la matrice courante
{
  Point3D p1;

  p1[0] = m[0]*pt_p[0] + m[1]*pt_p[1] + m[2]*pt_p[2]  + m[3];
  p1[1] = m[4]*pt_p[0] + m[5]*pt_p[1] + m[6]*pt_p[2]  + m[7];
  p1[2] = m[8]*pt_p[0] + m[9]*pt_p[1] + m[10]*pt_p[2] + m[11];
  
  return p1;
  
  //   Point3D(m[0]*pt_p[0] + m[1]*pt_p[1] + m[2]*pt_p[2]  + m[3],
//             m[4]*pt_p[0] + m[5]*pt_p[1] + m[6]*pt_p[2]  + m[7],
//             m[8]*pt_p[0] + m[9]*pt_p[1] + m[10]*pt_p[2] + m[11];
}

Matrix3D
Matrix3D::operator*
(const Matrix3D& m_p)
{
  const double *m2 = m_p.m;
  return Matrix3D(m[0]*m2[0]+m[1]*m2[4]+m[2]*m2[8],
                  m[0]*m2[1]+m[1]*m2[5]+m[2]*m2[9],
                  m[0]*m2[2]+m[1]*m2[6]+m[2]*m2[10],
                  m[0]*m2[3]+m[1]*m2[7]+m[2]*m2[11]+m[3],
                  
                  m[4]*m2[0]+m[5]*m2[4]+m[6]*m2[8],
                  m[4]*m2[1]+m[5]*m2[5]+m[6]*m2[9],
                  m[4]*m2[2]+m[5]*m2[6]+m[6]*m2[10],
                  m[4]*m2[3]+m[5]*m2[7]+m[6]*m2[11]+m[7],
                  
                  m[8]*m2[0]+m[9]*m2[4]+m[10]*m2[8],
                  m[8]*m2[1]+m[9]*m2[5]+m[10]*m2[9],
                  m[8]*m2[2]+m[9]*m2[6]+m[10]*m2[10],
                  m[8]*m2[3]+m[9]*m2[7]+m[10]*m2[11]+m[11],

                  0,0,0,1);
}

Matrix3D Matrix3D::scale(double sx,double sy,double sz)
{
  return Matrix3D(sx, 0, 0, 0,
                  0, sy, 0, 0, 
                  0, 0, sz, 0,
                  0, 0, 0, 1);

}

Matrix3D Matrix3D::rotationX(double angle)
{
  double sinO, cosO;
  sinO = sin(angle);
  cosO = cos(angle);
  
  return  Matrix3D(1, 0, 0, 0,
                   0, cosO, -sinO, 0,
                   0, sinO, cosO, 0,
                   0, 0, 0, 1);

}


Matrix3D Matrix3D::rotationY(double angle)
{
  double sinO, cosO;
  sinO = sin(angle);
  cosO = cos(angle);
 
  return Matrix3D(cosO, 0, sinO, 0,
                  0, 1, 0, 0,
                  -sinO, 0, cosO, 0,
                  0, 0, 0, 1);  
}

Matrix3D Matrix3D::rotationZ(double angle)
{
  double sinO, cosO;
  sinO = sin(angle);
  cosO = cos(angle);

  return Matrix3D(cosO, -sinO, 0, 0,
                  sinO, cosO, 0, 0,
                  0, 0, 1, 0,
                  0, 0, 0, 1);
}


Matrix3D Matrix3D::translation(double tx, double ty, double tz)
{
  return Matrix3D(1, 0, 0, tx,
                  0, 1, 0, ty,
                  0, 0, 1, tz,
                  0, 0, 0, 1);
}

ostream&
operator<<
( ostream& os, const Matrix3D &mat)
{
 
  os << mat.m[0] << " " << mat.m[1] << " " << mat.m[2] << " " << mat.m[3] << "|"
     << mat.m[4] << " " << mat.m[5] << " " << mat.m[6] << " " << mat.m[7] << "|"
     << mat.m[8] << " " << mat.m[9] << " " << mat.m[10] << " " << mat.m[11] << "|"
     << mat.m[12] << " " << mat.m[13] << " " << mat.m[14] << " " << mat.m[15];
  return os;
}
