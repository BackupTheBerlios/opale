#ifndef CLASS_CIRCLE
#define CLASS_CIRCLE

#include <vector>
#include "qgl.h"
#include "abscurve.hpp"

class Circle : public AbsCurve 
{
private:
  
public:

  Circle();

  ~Circle();
  void render();
  std::vector<gml::Point3D> discretize(int nbSegments);
  int addPoint(gml::Point3D *point);

};

#endif
