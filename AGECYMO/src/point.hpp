#ifndef CLASS_POINT_H
#define CLASS_POINT_H

#include "absVector.hpp"
#include "vector.hpp"

// gml = Geometrical Modeling Library
namespace gml
{
  using namespace std;

  const double EPSILON = 0.0000001;
  
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

    //Test if the current point belongs to the edge composed by the two
    // passed points with a given epsilon and sets the value t if the test is true
    //
    template <typename T2>
    bool isOnEdge(Point<T2, N> const & p1, Point<T2, N> const & p2,
                  double tolerance, double * t) const;
    
    
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
  
  template<typename T, int N>
  template <typename T2>
  Point<T, N> Point<T, N>::collinear(Point<T2,N> const &p2, double t) const
  {
    Point<T, N> result;

    result = *this + (p2 - *this)*t;
    return result;
  }
  
  template<typename T, int N>
  template <typename T2>
  bool Point<T, N>::isTheSame(Point<T2, N> const &p2, double tolerance) const
  {
    //TODO : FIX ME
    assert( N == 4);
    
    double deltaX = fabs( this->_data[0] -  p2[0] );
    double deltaY = fabs( this->_data[1] -  p2[1] );
    double deltaZ = fabs( this->_data[2] -  p2[2] );
    double deltaW = fabs( this->_data[3] -  p2[3] );


//     std::cout << "deltaX =" << deltaX << std::endl;
//     std::cout << "deltaY =" << deltaY << std::endl;
//     std::cout << "deltaZ =" << deltaZ << std::endl;
//     std::cout << "deltaW =" << deltaW << std::endl;
    
    return (deltaX <= tolerance) &&
      (deltaY <= tolerance) &&
      (deltaZ <= tolerance) &&
      (deltaW <= tolerance);
  }
  
  template<typename T, int N>
  template <typename T2>
  bool Point<T, N>::isOnEdge(Point<T2, N> const & p1, Point<T2, N> const & p2,
                             double tolerance, double * t) const
  {

    //Segment reduit a un point
    if ( p1.isTheSame(p2, tolerance) )
    {
      if (this->isTheSame(p1, tolerance))
      {
        *t = 0;
        return true;
      }
      else
      {
        return false;
      }
    }

    //Test si le point est confondu avec un des pts du segment
    if ( this->isTheSame(p1, tolerance) )
    {
      *t = 0.0;
      return true;      
    }
    else if ( this->isTheSame(p2, tolerance) )
    {
      std::cout << "here" << std::endl;
      
      *t = 1.0;
      return true;
    }
    
    return false;
  }
  
    
  
  typedef Point<int, 2> Point2D;
  typedef Point<double, 3> Point3D;
  typedef Point<double, 4> PointH;
  
  
}

#endif
