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
  
  public:
  Tria(std::vector<gml::Point3D> *points, int i1 = 0, int i2 = 1, int i3= 2);
  Tria(Tria const & t1);
  //virtual int nbPoints();
  //virtual int getIndex(int num);

  void render();

  std::vector<int> *Tria::getIndexes();

  Tria& operator=(Tria const & t1);

  

  friend std::ostream& operator<<(std::ostream& os, Tria const& t);
};


#endif
