#ifndef CLASS_ABSVECTOR_H
#define CLASS_ABSVECTOR_H

#include <iostream>
#include <cassert>


namespace gml
{
  using namespace std;

  /**
   * This class modelises a N dimensional vector of type T. 
   *
   */
  template<typename T = double, int N = 3>
  class AbsVector
  {
    protected:
    T _data[N];

    public:

    AbsVector();

    //operator overloading
    T  operator[](int indice) const;
    
    T& operator[](int indice);

    template <typename T2>
    AbsVector<T, N>& operator=(AbsVector<T2, N> const& v2); //T must contains T2
    
  };

  template<typename T, int N>
  ostream& operator<<(ostream& os, AbsVector<T, N> const& v)
  {
    os << "[ ";

    for (int i=0; i<(N-1); i++)
    {
      os << v[i] << "; " ;
    }
    os << v[N-1] << " ]";
    return os;
  }

  //Default Constructor
  template<typename T, int N>
  AbsVector<T,N>::AbsVector()
  {
    for (int i=0; i<N; i++)
    {
      _data[i] = 0;
    }
  }
    
  //operator overloading
  template<typename T, int N>
  T AbsVector<T, N>::operator[](int indice) const
  {
    assert( ( indice >= 0 ) && ( indice <= (N-1) ) );
    return _data[indice];
  }
 
  template<typename T, int N>
  T& AbsVector<T, N>::operator[](int indice)
  {
    assert( ( indice >= 0 ) && ( indice <= (N-1) ) );
    return _data[indice];
  }

  template<typename T, int N>
  template <typename T2>
  AbsVector<T, N>& AbsVector<T, N>::operator=(AbsVector<T2, N> const & v2)
  {
    if ( (void *) this == (void  *) &v2) //assignment to itself ?
    {
      return *this;
    }

    for (int i=0; i<N; i++)
    {
      _data[i] = v2[i];
    }    
    return *this;
  }
  
}
#endif
