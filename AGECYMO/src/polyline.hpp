#ifndef CLASS_POLYLINE
#define CLASS_POLYLINE

#include <vector>
#include "qgl.h"
#include "abscurve.hpp"

/*******************************************************
 * derived class of AbsCurve in order to draw a polyline
 *
 ******************************************************/
class Polyline : public AbsCurve 
{
private:
  
public:

  /*******************************************************
   * the default polyline constructor
   *
   ******************************************************/
  Polyline();

  /*******************************************************
   * the polyline destructor
   *
   ******************************************************/
  ~Polyline();

  /*******************************************************
   * draw the polyline in the openGL widget
   *
   ******************************************************/
  void render();

  /*******************************************************
   * add a point to the polyline
   * @param point the point to add
   * @return ADDED or NOT_ADDED
   *
   ******************************************************/
  int addPoint(gml::Point3D *point);

  /*******************************************************
   * discretize the polyline
   * @param nbSegments the discretization resolution
   * @return the vector of points (the discretized polyline)
   *
   ******************************************************/
  std::vector<gml::Point3D> discretize(int nbSegments);
  
};

#endif
