#ifndef CLASS_QUADRI
#define CLASS_QUADRI

#include <vector>
#include "qgl.h"
#include "abscurve.hpp"

class Quadri : public AbsCurve 
{
private:
  
public:

  Quadri();

  ~Quadri();

  void render();

  std::vector<gml::Point3D> discretize(int nbSegments);

  int addPoint(gml::Point3D *point);

};

#endif
