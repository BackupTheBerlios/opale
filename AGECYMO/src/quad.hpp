#ifndef CLASS_QUAD_H
#define CLASS_QUAD_H

#include "qgl.h"

#include "absface.hpp"

class Quad : public AbsFace
{
  private:
  int _i1; //indexes
  int _i2;
  int _i3;
  int _i4;


  //See updateNormal for computing details
  //Quad is not necessarly a planar surface
  gml::Vector3D _normal;
  gml::Point3D _n1; //n1 - center = normalized normal of the triangle 
  gml::Point3D _center;

  public:
  Quad(std::vector<gml::Point3D> *points,
       int i1 = 0, int i2 =1,
       int i3 = 2, int i4 = 3);

  void render();

  void renderNormal();
  
  void renderWithNormal();

  void updateNormal();
  
  virtual std::vector<int> *getIndexes();


  friend std::ostream& operator<<(std::ostream& os, Quad const& q);
};


  
#endif
