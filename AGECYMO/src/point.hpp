#ifndef CLASS_POINT_H
#define CLASS_POINT_H

#include "absVector.hpp"
#include "vector.hpp"

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
  
  typedef Point<int, 2> Point2D;
  typedef Point<double, 3> Point3D;
  typedef Point<double, 4> PointH;
  
  
}

#endif
