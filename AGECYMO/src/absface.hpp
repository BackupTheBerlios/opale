#ifndef CLASS_ABSFACE_H
#define CLASS_ABSFACE_H

#include <vector>
#include <iostream>

#include "point.hpp"

class AbsFace
{
  protected:
  
  std::vector<gml::Point3D> *_points; //pointer to the point coordinates
  
  std::vector<gml::Vector3D> *_normals;  //pointer to the normal  coordinates

  
  gml::Vector3D _normal; //normal of the face NOT the vertex normal
  gml::Point3D _n1; //n1 - center = normalized normal of the triangle 
  gml::Point3D _center;
  
  public:

  AbsFace(std::vector<gml::Point3D> *points);
  AbsFace(AbsFace const & f1);
  
  virtual ~AbsFace();

  void setPoints(std::vector<gml::Point3D> * pts);
  
  virtual void render() = 0;

  virtual void renderWithNormal() = 0;

  virtual void renderNormal() = 0;
    
  virtual std::vector<int> *getIndexes()=0;

  virtual bool containVertex(int vertexIndex) const = 0;  

  gml::Vector3D normal() const;

  void setNormals(std::vector<gml::Vector3D> * anormals);
  
  
  AbsFace& operator=(AbsFace const& f2);

  friend std::ostream& operator<<(std::ostream& os, AbsFace const& f);
    
};

#endif
