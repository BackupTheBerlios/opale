#include "absface.hpp"


AbsFace::AbsFace(std::vector<gml::Point3D> *points)
{
  _points = points;
}

AbsFace::AbsFace(AbsFace const & f1)
{
  _points = f1._points;
}

AbsFace::~AbsFace()
{
}

// void
// AbsFace::setPoints(gml::Point3D * pts)
// {
//   assert(pts != NULL);
//   _points = pts;
// }

void
AbsFace::setPoints(std::vector<gml::Point3D> * pts)
{
  assert(pts != NULL);
  _points = pts;
}



// void
// AbsFace::render() const
// {
//   std::cout << "render de absface" << std::endl;ca
  
// }

AbsFace&
AbsFace::operator=(AbsFace const& f2)
{
  std::cout << "Dans operator = de AbsFace" << std::endl;
  
  if ( (void *) this == (void  *) &f2) //assignment to itself ?
  {
    return *this;
  }

  _points = f2._points;
  
  return *this;
}


std::ostream& operator<<(std::ostream& os, AbsFace const& f)
{
  os << "[ Face point's address is :" << f._points << std::endl;

  std::vector<gml::Point3D>::iterator i;  
  for(i = f._points->begin(); i != f._points->end(); i++)
  {
    std::cout << (*i) << std::endl;
  }    
  
  
  return os;
}


/*int AbsFace::nbPoints()
{}

int AbsFace::getIndex(int num)
{}
*/



