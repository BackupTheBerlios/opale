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

  public:
  Quad(std::vector<gml::Point3D> *points,
       int i1 = 0, int i2 =1,
       int i3 = 2, int i4 = 3);

  virtual void render();
  
  virtual std::vector<int> *getIndexes();

//   virtual int nbPoints();
//   virtual int getIndex(int num);
  friend std::ostream& operator<<(std::ostream& os, Quad const& q);
};


  
#endif
