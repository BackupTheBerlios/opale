#ifndef CLASS_VECTOR_H
#define CLASS_VECTOR_H

#include "absVector.hpp"

//#include <cmath>
#include <cassert>

// gml = Geometrical Modeling Library
namespace gml
{
  using namespace std;

  /**
   * This class modelises a N dimensional vector of type T. 
   *
   */
  template<typename T = double, int N = 3>
  class Vector : public AbsVector<T, N>
  {
    public:

    T    squareNorm() const; // returns the square of the norm

    double    norm()  const; //returns the norm

    void normalize()       ; 
    
    
    //operator overloading
    template <typename T2>
    Vector<T, N>& operator=(Vector<T2, N> const& v2); //T must contains T2
    
    template <typename T2>
    Vector<T, N> operator*(T2 l);
    
    template <typename T2>
    Vector<T, N> operator/(T2 l);
    
    template <typename T2>
    Vector<T, N> operator-(Vector<T2, N> const& v2) const;
    
  };//end of class vector declaration
  
  typedef Vector<double, 3> Vector3D;
  typedef Vector<float, 3> Vector3F;
  
  //Static methods
  template<typename T, int N>
  static T dot(Vector<T, N> const& v1, Vector<T, N> const& v2)
  {
    T dotProduct = 0.0;
    
    for (int i=0; i<N; i++)
    {
      dotProduct += v1[i] * v2[i];
    }
        
    return  dotProduct;
  }

  template<typename T, int N>
//  template<typename T2>
  static Vector<T, N> cross(Vector<T, N> const& v1, Vector<T, N> const& v2)
  {
    //WARNING: Works  only for N = 3
    //TODO : generalizes this function to N dimension
    assert( N == 3);
    
    Vector<T, N> res;

    res[0] = v1[1]*v2[2] - v1[2]*v2[1] ;
    
    res[1] = v1[2]*v2[0] - v1[0]*v2[2];

    res[2] = v1[0]*v2[1] - v1[1]*v2[0];
    
    return  res;
  }
    
  //non member methods
  // T must contains T2 or you will get truncature error
  template<typename T, typename T2, int N>
  Vector<T, N> operator+(Vector<T, N> const& v1, Vector<T2, N> const& v2)
  {
    Vector<T, N> v3;
    for (int  i=0; i<N; i++)
    {
      v3[i] = v1[i] + v2[i];
    }
    return v3;
  }
  
  
  // Class vector : Methods implementation
  template<typename T, int N>
  T Vector<T, N>::squareNorm() const
  {
    T norm2 = 0;

    for (int i=0; i<N; i++)
    {
      norm2 += _data[i]*_data[i];
    }
    return norm2;
  }
  
  template<typename T, int N>
  double Vector<T, N>::norm() const
  {
    double norm = 0.0;
    norm = std::sqrt( static_cast<double>(squareNorm()) ) ;
    return norm;
  }

  template<typename T, int N>
  void Vector<T, N>::normalize()
  {
    double norm = this->norm();
//    assert( norm != 0);

    for (int i=0; i<N; i++)
    {
      _data[i] = _data[i] / norm;
    }
  }

  //operator overloading
  template<typename T, int N>
  template <typename T2>
  Vector<T, N>& Vector<T, N>::operator=(Vector<T2, N> const & v2)
  {
    AbsVector<T, N>::operator=(v2);
    return *this;
  }

  template<typename T, int N>
  template<typename T2>
  Vector<T, N> Vector<T, N>::operator*(T2 l)
  {
    Vector<T, N> v2;

    for (int i=0; i<N; i++)
    {
      v2[i] = _data[i] * l;
    }
    
    return v2;
  }
      
  template<typename T, int N>
  template<typename T2>
  Vector<T, N> Vector<T, N>::operator/(T2 l)
  {
    Vector<T, N> v2;

    for (int i=0; i<N; i++)
    {
      v2[i] = _data[i] / l;
    }
    
    return v2;
  }

  template<typename T, int N>
  template <typename T2>
  Vector<T, N> Vector<T, N>::operator-(Vector<T2, N> const& v2) const
  {
    Vector<T, N> v;

    for (int i=0; i<N; i++)
    {
      v[i] = _data[i] - v2[i];
    }
    return v;
  }
        
  typedef Vector<double, 3> Vector3D;

} // end of namespace gml
    
#endif
