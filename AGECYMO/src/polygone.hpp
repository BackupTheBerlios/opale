#ifndef CLASS_POLYGONE
#define CLASS_POLYGONE

#include <vector>
#include "qgl.h"
#include "abscurve.hpp"
#include "canvas2d.hpp"

  
//color for figure render
const double RED_CIRCLE = 0.25;
const double GREEN_CIRCLE = 0.25;
const double BLUE_CIRCLE = 0.25;

class Polygone : public AbsCurve 
{
private:

  int _nbPoints;
  Canvas2D *_parent;
  
  //color for figure render
  double _red_circle;
  double _green_circle;
  double _blue_circle;

public:

  Polygone(Canvas2D *parent);

  ~Polygone();
  
  void render();

  std::vector<gml::Point3D> discretize(int nbSegments);

  int addPoint(gml::Point3D *point);

};

#endif
