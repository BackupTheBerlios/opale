#ifndef CLASS_POINT_H
#define CLASS_POINT_H

#include "absVector.hpp"
#include "vector.hpp"
#include <vector>
#include <math.h>

// gml = Geometrical Modeling Library
namespace gml
{
  using namespace std;

  
  template<typename T = double, int N = 3>
  class Point : public AbsVector<T, N>
  {
    public:
    template <typename T2>
    Point<T, N>& operator=(Point<T2, N> const& v2); //T must contains T2

    template <typename T2>
    Vector<T, N> operator-(Point<T2, N> const& p2) const;

    template <typename T2>
    Point<T, N> operator+(Vector<T2, N> const& v1) const;
    
    template <typename T2>
    Point<T,N> collinear(Point<T2,N> const &p2, double t) const;

    template <typename T2>
    bool isTheSame(Point<T2, N> const &p2, double tolerance) const;

    template <typename T2>
    Point<T, N> Point<T, N>::middle(Point<T2,N> const &p2) const;

    //Test if the current point belongs to the edge composed by the two
    // passed points with a given epsilon and sets the value t if the test is true
    //
    template <typename T2>
    bool isOnEdge(Point<T2, N> const & p1, Point<T2, N> const & p2,
                  double tolerance, double * t) const;

    template <typename T2>
    bool onPlane(std::vector< Point<T2,N> > const &points, double tolerance) const;

    template <typename T2>
    bool onFace(vector < Point<T2,N> > const & points, double tolerance) const;

    template <typename T2>
    int inter(vector< Point<T2, N> > const &points, double* t1, double* t2, double tolerance) const;
    
  };
  
  template<typename T, int N>
  template<typename T2>
  Point<T, N>& Point<T, N>::operator=(Point<T2, N> const& p2)
  {
    AbsVector<T, N>::operator=(p2);
    return *this;
  }

  template<typename T, int N>
  template <typename T2>
  Vector<T, N> Point<T, N>::operator-(Point<T2, N> const& p2) const
  {
    Vector<T, N> v;

    for (int i=0; i<N; i++)
    {
      v[i] = _data[i] - p2[i];
    }
    return v;
  }

  
  template<typename T, int N>
  template <typename T2>
  Point<T, N> Point<T, N>::operator+(Vector<T2, N> const& v1) const
  {
    Point<T, N> result;

    for (int i=0; i<N; i++)
    {
      result[i] = this->_data[i] + v1[i];
    }
    
    return result;
  }
  

  // Compute the middle of an edge
  template<typename T, int N>
  template <typename T2>
  Point<T, N> Point<T, N>::middle(Point<T2,N> const &p2) const
  {
    
    Point<T, N> result;
    
    for (int i=0; i<3 ;i++) {
      result[i] = (p2[i] + _data[i])/2;
    }
    
    for (int i=3; i<N ;i++) {
      result[i] = 1.0;
    }

    return result;
  }


  // Compute a point on a edge
  template<typename T, int N>
  template <typename T2>
  Point<T, N> Point<T, N>::collinear(Point<T2,N> const &p2, double t) const
  {
    Point<T, N> result;

    result = *this + (p2 - *this)*t;
    return result;
  }


  // 
  template<typename T, int N>
  template <typename T2>
  bool Point<T, N>::isTheSame(Point<T2, N> const &p2, double tolerance) const
  {
    
    for (int i=0; i<N ; i++) {
      double delta = fabs( this->_data[i] -  p2[i] );
      if (delta > tolerance) {
	return false;
      }
    }

    return true;

  }
  


  template<typename T, int N>
  template <typename T2>
  bool Point<T, N>::isOnEdge(Point<T2, N> const & p1, Point<T2, N> const & p2,
                             double tolerance, double * t) const
  {
    
    // Edge reduces point
    if (p1.isTheSame(p2, tolerance)) {
      if ( this->isTheSame(p1, tolerance) ) {
        *t = 0.0;
        return true;
      }
      else {
        return false;
      }
    }

    if ( this->isTheSame(p1, tolerance) )
    {
      *t = 0.0;
      return true;      
    }
    else if ( this->isTheSame(p2, tolerance) )
    {
      *t = 1.0;
      return true;
    }
    else {
      double deltaX, deltaY, deltaZ;
      deltaX = (this->_data[0] - p1[0])/(p2[0] - p1[0]);
      deltaY = (this->_data[1] - p1[1])/(p2[1] - p1[1]);
      deltaZ = (this->_data[2] - p1[2])/(p2[2] - p1[2]);
      
      if (isEqual(deltaX, deltaY, tolerance) && isEqual(deltaY, deltaZ, tolerance)) {
        if (isGreaterOrEqual(deltaX, 0, tolerance) && isLesserOrEqual(deltaX, 1, tolerance)) {
          *t = deltaX;
          return true;
        }
      } 
    }
   
    
 
    return false;

  }
  
  template<typename T, int N>
  inline vector<double> definePlane(std::vector < Point<T,N> > const &points, double tolerance)
  {
    int len=0;
    double a, b, c, norm;
    double xi, yi, zi, xj, yj, zj, xc, yc, zc;
    int i= 0;
    vector<double> result;
    
    a = b = c = xc = yc = zc = 0.0;
    do {
      int iNxt;
      
      xi = points[i][0];
      yi = points[i][1];
      zi = points[i][2];
      
      iNxt= (i == points.size()-1)?0:i+1;
      xj = points[iNxt][0];
      yj = points[iNxt][1];
      zj = points[iNxt][2];
      
      a += ( yi - yj ) * ( zi + zj );
      b += ( zi - zj ) * ( xi + xj );
      c += ( xi - xj ) * ( yi + yj );
      xc += xi;
      yc += yi;
      zc += zi;
      len++;
      i++;
    } while( i < points.size() );
    
    norm = sqrt( a * a + b * b + c * c );
    if(!isEqual(norm, 0.0, tolerance)) {
      result.push_back(a / norm);
      result.push_back(b / norm);
      result.push_back(c / norm);
      result.push_back((result[0] * xc + result[1] * yc + result[2] * zc) / (double)(-len));
      return result;
    }
    
    return result;
  }


  template<typename T, int N>
  template <typename T2>
  bool Point<T,N>::onPlane(vector < Point<T2,N> > const & points, double tolerance) const {
    vector<double> plane;
    double dist= 0.0;

    vector <int> samePoints;

    vector < Point<T2,N> > allPoints;

    for (int i=0; i<(int)points.size();i++) {
      allPoints.push_back(points[i]);
      
    }
    

    
    
    for(int i=0; i<(int)allPoints.size(); i++) {
      for(int j=i+1; j<(int)allPoints.size();j++) {
	if (isEqual(allPoints[i][0], allPoints[j][0], tolerance) && isEqual(allPoints[i][1], allPoints[j][1], tolerance) && isEqual(allPoints[i][2], allPoints[j][2], tolerance)) {
	  samePoints.push_back(i);
	
	}
      }
    }
	
    bool diff=true;
    
    for (int i=0; i<(int)points.size();i++) {
      int j=0;

      while (j<(int)samePoints.size() && diff) {
	if (i==samePoints[j]) {
	  diff = false;
	}
	else {
	  j++;
	}

      }
	
      if (diff) {  

	allPoints.push_back(points[i]);
      }
      diff = true;
      
    }

    plane = definePlane(allPoints, tolerance);
    if(plane.empty()) {
      
      return false;
    }
    
    dist = _data[0]*plane[0] + _data[1]*plane[1] + _data[2]*plane[2] + _data[3]*plane[3];
    
    if(isEqual(dist, 0.0, tolerance)) {
      return true;
    }

    return false;
  }




  template<typename T, int N>
  template <typename T2>
  bool Point<T,N>::onFace(vector < Point<T2,N> > const & points, double tolerance) const {
    vector<double> plane;
    double dist= 0.0;
    



    vector <int> samePoints;

    vector < Point<T2,N> > allPoints;

    for (int i=0; i<(int)points.size();i++) {
      allPoints.push_back(points[i]);
      
    }
       
    
    for(int i=0; i<(int)allPoints.size(); i++) {
      for(int j=i+1; j<(int)allPoints.size();j++) {
	if (isEqual(allPoints[i][0], allPoints[j][0], tolerance) && isEqual(allPoints[i][1], allPoints[j][1], tolerance) && isEqual(allPoints[i][2], allPoints[j][2], tolerance)) {
	  samePoints.push_back(i);
	
	}
      }
    }
	
    bool diff=true;
    
    for (int i=0; i<(int)points.size();i++) {
      int j=0;

      while (j<(int)samePoints.size() && diff) {
	if (i==samePoints[j]) {
	  diff = false;
	}
	else {
	  j++;
	}

      }
	
      if (diff) {  

	allPoints.push_back(points[i]);
      }
      diff = true;
      
    }


    

    plane = definePlane(allPoints, tolerance);
    if(plane.empty()) {
      return false;
    }
    
    vector< Point<T2, N> > newplane;

    for (int i=0; i<allPoints.size()-1; i=i+2) {
      Point <T2, N> origine;
      for (int j=0; j<3; j++) {
	origine[j] = 0.0;
      }
      newplane.push_back(origine);
      newplane.push_back(allPoints[i]);
      newplane.push_back(allPoints[i+1]);
      
      double t1, t2;

      for (int i=0; i<newplane.size();i++) {
	cout << newplane[i][0] << " " << newplane[i][1] << " " << newplane[i][2] << endl;
      }

      if ((*this).inter(newplane, &t1, &t2, tolerance)==1) {
	return true;
      }
    }


    return false;
  }

  template<typename T, int N>
  template <typename T2>
  int Point<T, N>::inter(vector< Point<T2, N> > const &points, double* t1, double* t2, double tolerance) const {
    int i;
    
    double d, a[3], b[3], c[3];

    vector< Point<T2, N> > allPoints;
     
    allPoints.push_back(*this);
 
    allPoints.push_back(points[0]);
 
    allPoints.push_back(points[1]);
 
    allPoints.push_back(points[2]);
 

    if(!allPoints[0].onPlane(allPoints, tolerance)) {
      return 0;
    }

    if(!allPoints[1].onPlane(allPoints, tolerance)) {
      return 0;
    }

    if(!allPoints[2].onPlane(allPoints, tolerance)) {
      return 0;
    }

    if(!allPoints[3].onPlane(allPoints, tolerance)) {
      return 0;
    }


    for(i=0; i<3; i++) {
      a[i]= allPoints[1][i] - allPoints[0][i];
      b[i]= -allPoints[3][i] + allPoints[2][i];
      c[i]= allPoints[0][i] - allPoints[2][i];
    }
    
    for(i=0; i<3; i++) {

      int j, j_nxt;
      
      j=i;
      j_nxt=(i==2)?0:i+1;

      d= a[j]*b[j_nxt] - b[j]*a[j_nxt];

      
      if( !isEqual(d, 0.0, tolerance) ) {
	
	*t1= (-c[j]*b[j_nxt] + b[j]*c[j_nxt])/d;
	*t2= (-a[j]*c[j_nxt] + c[j]*a[j_nxt])/d;
	
	if( *t1 < -tolerance || *t1 > 1.+tolerance ) {
	  return 2;
	}
	
	if( *t2 < -tolerance || *t2 > 1.+tolerance ) {
	  return 2;
	}
	
	return 1;
      }
    }
    return 0;
  }
  
  

  inline bool isEqual(double a, double b, double tolerance) {
    double delta = fabs(a-b);
    return (delta <= tolerance);
  }
  
  inline bool isGreaterOrEqual(double a, double b, double tolerance) {
    return (a > b - tolerance);
  }
  
  inline bool isLesserOrEqual(double a, double b, double tolerance) {
    return (a < b + tolerance);
  }


  
  typedef Point<int, 2> Point2D;
  typedef Point<double, 3> Point3D;
  typedef Point<double, 4> PointH;
  
  
}

#endif
