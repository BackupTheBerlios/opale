#ifndef CLASS_FACE_H
#define CLASS_FACE_H

#include <vector>

#include "qgl.h"

#include "absface.hpp"
#include "point.hpp"

class Face : public AbsFace
{
  private:
  int _numberOfPts;
  int* _indexPts;
  
  
  
  public:
  Face( std::vector<int> indexes,
        std::vector<gml::Point3D> *points,
        int numberOfPoints = 5);

  ~Face();

//  void setIndices(std::vector<int> indexes);
  
  
  void render();
  
};



#endif
