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

