#include "faces.hpp"
#include <exception>
#include <iostream>
#include <cstdlib>

Faces::Faces(std::vector<gml::Point3D> *points,
             std::vector<AbsFace*> *faces)
    : _nbPoints(points->size()),
      _nbFaces((*faces).size()),
      _points(points),
      _faces(faces)
  
{
//  std::cout << "liste de faces dans constructeur : " << *this << std::endl;
}


Faces::~Faces()
{
  delete _faces;
  delete _points;
}


void
Faces::render() const
{

//  std::cout << "dans faces render" << std::endl;

  
  int cpt = 0;

  std::vector<AbsFace*> faces = *_faces;

//  std::cout << "liste de faces dans faces render : " << *this << std::endl;
  
  std::vector<AbsFace*>::iterator i;  

//  std::cout << "Premier point dans faces render :" << ((_points)[0])[0] << std::endl;

  for(i = faces.begin(); i != faces.end(); i++)
  {
    (*i)->render();
    cpt++;
  }  
}


std::vector<gml::Point3D> const &
Faces::points()
{
  return *_points;
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
     << "Faces address : " << &f << std::endl
     << "Points : " << std::endl;
  
  
  std::vector<gml::Point3D> lespoints = *(f._points);
  
  for (int i=0; i<f._points->size(); i++)
  {
    os << lespoints[i];
  }

  os << std::endl << "Faces : " << std::endl;
  
  std::vector<AbsFace*> lesfaces = *(f._faces);
  
  for (int i=0; i<f._faces->size(); i++)
  {
    os << "Face " << i << " address : " << &lesfaces[i] << std::endl;
    os << *(lesfaces[i]);
  }
  
  return os;
    
}

  
