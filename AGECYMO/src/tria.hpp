#ifndef CLASS_TRIA_H
#define CLASS_TRIA_H

#include "qgl.h"

#include "absface.hpp"


class Tria : public AbsFace
{
  private:
  int _i1; //indexes
  int _i2;
  int _i3;

//   gml::Vector3D _normal;
//   gml::Point3D _n1; //n1 - center = normalized normal of the triangle 
//   gml::Point3D _center;
  
  
  public:
  Tria(std::vector<gml::Point3D> *points, int i1 = 0, int i2 = 1, int i3= 2);
  Tria(Tria const & t1);

  
  void render();

  void renderNormal();

  void renderWithNormal();
  
  bool containVertex(int vertexIndex) const;
  
  std::vector<int> *Tria::getIndexes();

  Tria& operator=(Tria const & t1);


  void updateNormal(); //this update the normal of the triangle
                       //not the normal for each edges
  
  

  friend std::ostream& operator<<(std::ostream& os, Tria const& t);
};


#endif
