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
  
  
  
  public:
  Face(std::vector<int> *indexes, std::vector<gml::Point3D> *points, int numberOfPoints = 5);

  virtual std::vector<int> *getIndexes();

//   virtual int nbPoints();
//   virtual int getIndex(int num);

  ~Face();

  void render();
  
  friend std::ostream& operator<<(std::ostream& os, Face const& f);
};



#endif
