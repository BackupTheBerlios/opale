#include "faces.hpp"


Faces::Faces(std::vector<gml::Point3D> points,
             std::vector<AbsFace*> *faces)
    : _nbPoints(points.size()),
      _nbFaces((*faces).size()),
      _points(points),
      _faces(faces)
{
}


Faces::~Faces()
{
}


void
Faces::render() const
{
  std::cout << "dans faces render" << std::endl;
  
  std::vector<AbsFace*> faces = *_faces;
  
  std::vector<AbsFace*>::iterator i;  
  for(i = faces.begin(); i != faces.end(); i++)
  {
    (*i)->render();
  }  
}


std::vector<gml::Point3D> const &
Faces::points()
{
  return _points;
}

std::vector<AbsFace*> const &
Faces::faces()
{
  return *_faces;
}


std::ostream&
operator<<(std::ostream& os, Faces const& f)
{
  os << "Model contains [ " << f._nbPoints << " points; " 
     << f._nbFaces << " faces ] " << std::endl
     << "Points : " << std::endl;
  
  for (int i=0; i<f._points.size(); i++)
  {
    os << f._points[i];
  }

  os << std::endl << "Faces : " << std::endl;
  
  std::vector<AbsFace*> lesfaces = *(f._faces);
  
  for (int i=0; i<f._faces->size(); i++)
  {
    os << *(lesfaces[i]);
  }
  
  return os;
    
}

  
