#include "absface.hpp"

/**************************************************************
 *
 *  constructor for AbsFace class
 *  @param points a vector of points used in the face
 *
 *************************************************************/
AbsFace::AbsFace(std::vector<gml::Point3D> *points)
{
  _points = points;
  _normals = NULL;
}

/**************************************************************
 *
 *  copy constructor for AbsFace class
 *  @param t1 another Tria
 *
 *************************************************************/
AbsFace::AbsFace(AbsFace const & f1)
{
  _points = f1._points;
}

/**************************************************************
 *
 *  destructor for AbsFace 
 *
 *************************************************************/
AbsFace::~AbsFace()
{
}

/**************************************************************
 *
 *  set points of the face
 *  @param pts a vector of points
 *
 *************************************************************/
void
AbsFace::setPoints(std::vector<gml::Point3D> * pts)
{
  assert(pts != NULL);
  _points = pts;
}

std::vector<gml::Point3D> const &
AbsFace::getPoints() 
{
  return *_points;
}

/**************************************************************
 *
 *  get the normal
 *  @return the normal of the face
 *
 *************************************************************/
gml::Vector3D
AbsFace::normal() const
{
  return _normal;
}

/**************************************************************
 *
 *  set the normal of the face per vertex
 *  @param the vector of normals
 *
 *************************************************************/
void
AbsFace::setNormals(std::vector<gml::Vector3D> * anormals)
{
  assert(anormals != NULL);
  _normals = anormals;
}

/**************************************************************
 *
 *  define the equal operator
 *
 *************************************************************/
AbsFace&
AbsFace::operator=(AbsFace const& f2)
{ 
  if ( (void *) this == (void  *) &f2) //assignment to itself ?
  {
    return *this;
  }

  _points = f2._points;
  
  return *this;
}

/**************************************************************
 *
 *  define the display operator
 *
 *************************************************************/
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



