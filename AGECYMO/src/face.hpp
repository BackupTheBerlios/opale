#ifndef CLASS_FACE_H
#define CLASS_FACE_H

#include <iostream>

#include "qgl.h"

#include "absface.hpp"
#include "point.hpp"

class Face : public AbsFace
{
  private:
  int _numberOfPts;
  int* _indexPts;

  
//   gml::Vector3D _normal;
//   gml::Point3D _n1; 
//   gml::Point3D _center;

  
  
  public:
  Face(std::vector<int> *indexes,
       std::vector<gml::Point3D> *points,
       int numberOfPoints = 5);

  
  bool containVertex(int vertexIndex) const;
  
  virtual std::vector<int> *getIndexes();

  ~Face();

  void render();

  void renderNormal();
  
  void renderWithNormal();

  void updateNormal();
    
  friend std::ostream& operator<<(std::ostream& os, Face const& f);
};



#endif
