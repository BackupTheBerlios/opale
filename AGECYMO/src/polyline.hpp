#ifndef CLASS_POLYLINE
#define CLASS_POLYLINE

#include <vector>
#include "point.hpp"
#include "qgl.h"
#include "abscurve.hpp"

class Polyline : public AbsCurve 
{
private:
  
public:
  Polyline();
  Polyline(std::vector<gml::Point3D> pointsVector, bool isClosed);
  Polyline(const Polyline &source);
  void render();
  std::vector<gml::Point3D> discretize();
};

#endif
