#ifndef CLASS_QUADRI
#define CLASS_QUADRI

#include <vector>
#include "qgl.h"
#include "abscurve.hpp"

/*******************************************************
 * derived class of AbsCurve in order to draw a rectangle
 *
 ******************************************************/
class Quadri : public AbsCurve 
{
private:
  
public:

  /*******************************************************
   * the default Quadri constructor
   *
   ******************************************************/
  Quadri();

  /*******************************************************
   * the Quadri destructor
   *
   ******************************************************/
  ~Quadri();

  /*******************************************************
   * draw the quadri in the openGL widget
   *
   ******************************************************/
  void render();

  /*******************************************************
   * discretize the quadri
   * @param nbSegments the discretization resolution
   * @return the vector of points (the discretized polyline)
   *
   ******************************************************/
  std::vector<gml::Point3D> discretize(int nbSegments);

  /*******************************************************
   * add a point to the quadri
   * @param point the point to add
   * @return ADDED or NOT_ADDED
   *
   ******************************************************/
  int addPoint(gml::Point3D *point);

};

#endif
