#ifndef CLASS_POLYLINE
#define CLASS_POLYLINE

#include <vector>
#include "qgl.h"
#include "abscurve.hpp"

class Polyline : public AbsCurve 
{
private:
  
public:
  Polyline();
  ~Polyline();
  void render();
  int addPoint(gml::Point3D *point);
  std::vector<gml::Point3D> discretize(int nbSegments);
  
};

#endif
