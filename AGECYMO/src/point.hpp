#ifndef CLASS_POINT_H
#define CLASS_POINT_H

#include <math.h>


#include "absVector.hpp"
#include "vector.hpp"
#include <vector>

#include "precision.hpp"
// #ifdef CORE_LEVEL
// #include "CORE/CORE.h"
// #endif


// gml = Geometrical Modeling Library
namespace gml
{
  using namespace std;

  // The class Point.
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
    bool Point<T, N>::isTheSame(Point<T2, N> const &p2) const;
        
    template <typename T2>
    Point<T, N> Point<T, N>::middle(Point<T2,N> const &p2) const;

    //Test if the current point belongs to the edge composed by the two
    // passed points with a given epsilon and sets the value t if the test is true
    template <typename T2>
    bool isOnEdge(Point<T2, N> const & p1,
                  Point<T2, N> const & p2,
                  double * t) const;

    template <typename T2>
    bool onPlane(std::vector< Point<T2,N> > const &points) const;

    template <typename T2>
    bool onFace(vector < Point<T2,N> > const & points) const;

    template <typename T2>
    int inter(vector< Point<T2, N> > const &points,
              double* t1, double* t2) const;
     
    template <typename T2>
    bool interPlan(Point<T2,N> point,
                   vector < Point<T2,N> > const & points,
                   double *t) const; 
    
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
  
  ////////////////////////////////////////////////////
  //middle of an edge defined by two points ok
  template<typename T, int N>
  template <typename T2>
  Point<T, N> Point<T, N>::middle(Point<T2,N> const &p2) const
  {
    Point<T, N> result;
    double two=2.0;
    double one=1.0;
   
    for (int i=0; i<3 ;i++) {
      result[i] = (p2[i] + _data[i])/two;
    }
    for (int i=3; i<N ;i++) {
      result[i] = one;
    }
    return result;
  }

  /////////////////////////////////////////////////////
  // Compute a point along an edge 
  template<typename T, int N>
  template <typename T2>
  Point<T, N> Point<T, N>::collinear(Point<T2,N> const &p2, double t) const
  {
    Point<T, N> result;

    result = *this + (p2 - *this)*t;
    return result;
  }


  /////////////////////////////////////////////////////
  // Define if the point is at the same place of another point ok
  template<typename T, int N>
  template <typename T2>
  bool Point<T, N>::isTheSame(Point<T2, N> const &p2) const
  {
    for (int i=0; i<N ; i++)
    {
      if( ! isEqual(this->_data[i], p2[i]) );
      {
        return false;
      }
    }
    return true;
  }
  
  /////////////////////////////////////////////////////
  // Define if the point is on an edge ok
  template<typename T, int N>
  template <typename T2>
  bool Point<T, N>::isOnEdge(Point<T2, N> const & p1, Point<T2, N> const & p2,
                             double * t) const
  {
    
    // two points of the edge are at the same place
    if (p1.isTheSame(p2))
    {
      if ( this->isTheSame(p1) )
      {
        *t = 0.0;
        return true;
      }
      else
      {
        return false;
      }
    }

    // point at the same place as p1
    if ( this->isTheSame(p1) )
    {
      *t = 0.0;
      return true;      
    }
    // point at the same place as p2
    else if ( this->isTheSame(p2) )
    {
      *t = 1.0;
      return true;
    }
    //test if the point is between the two points on the edge
    else
    {
      double deltaX, deltaY, deltaZ;
      deltaX = (this->_data[0] - p1[0])/(p2[0] - p1[0]);
      deltaY = (this->_data[1] - p1[1])/(p2[1] - p1[1]);
      deltaZ = (this->_data[2] - p1[2])/(p2[2] - p1[2]);
      
      if ( gml::isEqual(deltaX, deltaY) &&
           gml::isEqual(deltaY, deltaZ))
      {
        if (isGreaterOrEqual(deltaX, 0) &&
            isLesserOrEqual(deltaX, 1) )
        {
          *t = deltaX;
          return true;
        }
      } 
    }
    return false;
  }
  

  /////////////////////////////////////////////////////
  // défine a plane with given points 
  template<typename T, int N>
  inline vector<double> definePlane(std::vector < Point<T,N> > const &points)
  {
    int len=0;
    double a, b, c, norm;
    double xi, yi, zi, xj, yj, zj, xc, yc, zc;
    int i= 0;
    vector<double> result;
    int iNxt;

    a = b = c = xc = yc = zc = 0.0;
    do
    {
      iNxt = 0;

      xi = points[i][0];
      yi = points[i][1];
      zi = points[i][2];
      
      iNxt= (i == (int)points.size()-1)?0:i+1;
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
    }
    while( i < (int)points.size() );
    
    norm = sqrt( a * a + b * b + c * c );
    double w = (-len);

    if(! isEqual(norm, 0) )
    {
      result.push_back(a / norm);
      result.push_back(b / norm);
      result.push_back(c / norm);
      result.push_back((result[0] * xc + result[1] * yc + result[2] * zc) 
		       / w);
      return result;
    }
    
    return result;
  }

  ///////////////////////////////////////////////////////
  //Returns true if the given points is in the same plane of the current point
  template<typename T, int N>
  template <typename T2>
  bool Point<T,N>::onPlane(vector < Point<T2,N> > const & points) const
  {
    vector<double> plane;
    double dist= 0.0;

    vector <int> samePoints;

    vector < Point<T2,N> > allPoints;

    // Erase point if there are same point in points
    for(int i=0; i<(int)points.size(); i++)
    {
      for(int j=i+1; j<(int)points.size();j++)
      {
        //Est ce que la méthode isTheSame ne devrait elle pas etre utilisée plutot 
        // que comparer valeur par valeur ?
        if (isEqual(points[i][0], points[j][0]) &&
            isEqual(points[i][1], points[j][1]) &&
            isEqual(points[i][2], points[j][2]))
        {
          samePoints.push_back(i);  
        }
      }
    }
	
    bool diff=true;
    
    for (int i=0; i<(int)points.size();i++)
    {
      int j=0;
      while (j<(int)samePoints.size() && diff)
      {
        if (i==samePoints[j])
        {
          diff = false;
        }
        else
        {
          j++;
        }
      }
	
      if (diff)
      {  
        allPoints.push_back(points[i]);
      }
      diff = true;
    }

    plane = definePlane(allPoints);
    if(plane.empty())
    {
      return false;
    }

    if (N==3)
    {
      dist = _data[0]*plane[0] + _data[1]*plane[1] + _data[2]*plane[2] + plane[3];
    }
    else
    {
      dist = _data[0]*plane[0] + _data[1]*plane[1] + _data[2]*plane[2] + _data[3]*plane[3];
    }
    
    if( isEqual(dist, 0) )
    {
      return true;
    }
    return false;
  }

  /////////////////////////////////////////////////////////////////
  //check if the point is on the face
  template<typename T, int N>
  template <typename T2>
  bool Point<T,N>::onFace(vector < Point<T2,N> > const & points) const
  {

    vector<double> plane;
    double dist= 0.0;
    vector <int> samePoints;
    vector < Point<T2,N> > allPoints;
    

    // Firstly copy of the vector points in the vector 
    // samePoints, if all the points are different
    for(int i=0; i<(int)points.size(); i++)
    {
      for(int j=i+1; j<(int)points.size();j++)
      {
        //Est ce que la méthode isTheSame ne devrait elle pas etre utilisée plutot 
        // que comparer valeur par valeur ?
        if (isEqual(points[i][0], points[j][0]) &&
            isEqual(points[i][1], points[j][1]) &&
            isEqual(points[i][2], points[j][2]))
        {
          samePoints.push_back(i);
        }
      }
    }
    
    // Construction of the vector allPoints, with only the different points
    bool diff=true;
    for (int i=0; i<(int)points.size();i++)
    {
      int j=0;
      while (j<(int)samePoints.size() && diff)
      {
        if (i==samePoints[j])
        {
          diff = false;
        }
        else
        {
          j++;
        }
      }
      
      if (diff)
      {  
        allPoints.push_back(points[i]);
      }
      diff = true;
    }


    // 1) Check if the vector allPoints is a really a plan
    plane = definePlane(allPoints);
    if( plane.empty() )
    {
      return false;
    }
    
    // 2) Check if the current point is on the plan
    if( !onPlane(allPoints) )
    {
      return false;
    }

    // 3) Check if the point belows to one of edge of the face
    for (int i=0 ; i<(int)allPoints.size() ; i++)
    {
      int next = i+1;
      if (next == (int)allPoints.size())
      {
        next = 0;
      }
      double t;

      if (isOnEdge(allPoints[i], allPoints[next], &t))
      {
        return true;
      }
    }
   
    // 4) Computation of a line
    double diffx = allPoints[0][0] - allPoints[1][0];
    double diffy = allPoints[0][1] - allPoints[1][1];
    double diffz = allPoints[0][2] - allPoints[1][2];

    Point<T,N> newPoint;
    newPoint[0] = (*this)[0] + diffx;
    newPoint[1] = (*this)[1] + diffy;
    newPoint[2] = (*this)[2] + diffz;
    
    // 5) Check if the line cut or not the plan
    int nbCut = 0;
    for (int i=0 ; i<(int)allPoints.size() ; i++)
    {
      int next = i+1;
      if (next == (int)allPoints.size())
      {
        next = 0;
      }

      vector< Point<T2, N> > newPlane;
      newPlane.push_back(newPoint);
      newPlane.push_back(allPoints[i]);
      newPlane.push_back(allPoints[next]);

      double t1, t2;
      int valueCut = (*this).inter(newPlane, &t1, &t2);
      if (valueCut > 0)
      {
        if (isGreaterOrEqual(t1, 0) &&
            isGreaterOrEqual(t2, 0) &&
            isLesserOrEqual(t2, 1))
        { 
          nbCut++;
        }
      }

      if (nbCut == 1)
      {
        return true;
      }
    }
    return false; 
  }


  ////////////////////////////////////////////////////////////
  // intersection segment(this-1erpoint vector)/segment(2e et 3e point du vecteur)
  template<typename T, int N>
  template <typename T2>
  int Point<T, N>::inter(vector< Point<T2, N> > const &points,
                         double* t1, double* t2) const
  {
    double one = 1;
    double null_value = 0;
    
    int i;
    double d, a[3], b[3], c[3];
    vector< Point<T2, N> > allPoints;
     
    allPoints.push_back(*this);
    allPoints.push_back(points[0]);
    allPoints.push_back(points[1]);
    allPoints.push_back(points[2]);
 

    //define if all the points are on the plane
    if( !allPoints[0].onPlane(allPoints) )
    {
      return 0;
    }

    if( !allPoints[1].onPlane(allPoints) )
    {
      return 0;
    }

    if( !allPoints[2].onPlane(allPoints) )
    {
      return 0;
    }

    if( !allPoints[3].onPlane(allPoints) )
    {
      return 0;
    }


    for(i=0; i<3; i++)
    {
      a[i]= allPoints[1][i] - allPoints[0][i];
      b[i]= -allPoints[3][i] + allPoints[2][i];
      c[i]= allPoints[0][i] - allPoints[2][i];
    }
    
    for(i=0; i<3; i++)
    {
      int j, j_nxt;
      
      j=i;
      j_nxt=(i==2)?0:i+1;

      d= a[j]*b[j_nxt] - b[j]*a[j_nxt];
      
      if( ! isEqual(d, 0.0) )
      {
        *t1= (-c[j]*b[j_nxt] + b[j]*c[j_nxt])/d;
        *t2= (-a[j]*c[j_nxt] + c[j]*a[j_nxt])/d;
	
//        if( *t1 < -tolerance || *t1 > 1.+tolerance )
        if( isLesser(*t1, null_value) || isGreater(*t1, one) ) 
        {
          return 2;
        }
        
//        if( *t2 < -tolerance || *t2 > 1.+tolerance )
        if( isLesser(*t2, null_value) || isGreater(*t2, one) ) 
        {
          return 2;
        }
        return 1;
      }
    }
    return 0;
  }
  
  ////////////////////////////////////////////////////////////
  // define if a segment intersect a plane
  template<typename T, int N>
  template <typename T2>
  bool Point<T,N>::interPlan(Point<T2,N> point, 
                             vector < Point<T2,N> > const & points,
                             double *t) const
  {
    vector<double> plane;
    double null_value = 0.0;
    double one = 1.0;

    // 1) If the normal of the plan and the vector of the 
    //edge are perpendicular, then there is no verification
    double vectorEdgeX = _data[0] - point[0];
    double vectorEdgeY = _data[1] - point[1];
    double vectorEdgeZ = _data[2] - point[2];

    plane = definePlane(points);
    if( plane.empty() )
    {
      return false;
    }

    //  if (plane[0]*vectorEdgeX + plane[1]*vectorEdgeY +	plane[2]*vectorEdgeZ
    //    == null_value)

    // BUG !!! PROBLEME 
    //Test incomplet pour conclure il faut s assure que la droite n est PAS coplanaire au plan
    if ( isEqual((plane[0]*vectorEdgeX + plane[1]*vectorEdgeY +	plane[2]*vectorEdgeZ),
                 null_value))
    {
      return false;
    }
    
    // 2) If the edge is an edge of the face
    bool found1 = false;
    bool found2 = false;
    int i=0;
    while ((!found1 || !found2 ) && i<points.size())
    {
      
      // Mauvais d ou la ligne commentee parce que :
      //      1) epsilon non utilise
      //      2) fonction isTheSame non utilisee
      // if (points[i][0] == _data[0] && points[i][1] == _data[1] && points[i][2] == _data[2])
      if ( isTheSame( points[i]) ) 
      {
        found1 = true;
      }
      // Mauvais d ou la ligne commentee parce que :
      //      1) epsilon non utilise
      //      2) fonction isTheSame non utilisee
      // if (points[i][0] == point[0] && points[i][1] == point[1] && points[i][2] == point[2])
      if ( point.isTheSame(points[i]) )
      {
        found2 = true;
      }
      i++;
    }
    
    if (found1 && found2)
    {
      return false;
    }

    // 3) Compute of t
    *t = (-plane[0]*_data[0] - plane[1]*_data[1] - plane[2]*_data[2] - plane[3]) /
      (plane[0]*vectorEdgeX + plane[1]*vectorEdgeY + plane[2]*vectorEdgeZ);

    //Intersection avec la droite mais PAS le segment
    if ( isLesser(*t, null_value) || isGreater(*t ,one) )
    {
      return false;
    }
    else
    {
      Point<T,N> interPoint = collinear(point, *t);
      if (!interPoint.onFace(points))
      {
        return false;
      }
      else
      {
        return true;
      }
    }
  }
  
  typedef Point<int, 2> Point2D;
  typedef Point<double, 3> Point3D;
  typedef Point<double, 4> PointH;
  
}


#endif
