#ifndef CLASS_NURBSCURVE
#define CLASS_NURBSCURVE

#include <vector>
#include "qgl.h"
#include "abscurve.hpp"

//color for figure render
const double RED_NURB = 0.86;
const double GREEN_NURB = 0.78;
const double BLUE_NURB = 0.4;

class NurbsCurve : public AbsCurve 
{
private:

  int _nbPointsDefine;
  std::vector<float> _HCoordinateVector;
  //color for figure render
  double _red_nurb;
  double _green_nurb;
  double _blue_nurb;
  
public:

  NurbsCurve();

  ~NurbsCurve();

  void render();

  std::vector<gml::Point3D> discretize(int nbSegments);

  int addPoint(gml::Point3D *point);

};

#endif
