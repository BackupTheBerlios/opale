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

/*******************************************************
 * derived class of AbsCurve in order to draw a polygone
 *
 ******************************************************/
class Polygone : public AbsCurve 
{
private:

  int _nbPoints; /**number of vertices*/
  double _redCircle;
  double _greenCircle;
  double _blueCircle;

public:

  /*******************************************************
   * the default Polygone constructor
   *
   ******************************************************/
  Polygone(Canvas2D *parent);

  /*******************************************************
   * the Polygonee destructor
   *
   ******************************************************/
  ~Polygone();
  
  /*******************************************************
   * draw the polygone in the openGL widget
   *
   ******************************************************/
  void render();

  /*******************************************************
   * discretize the polygone
   * @param nbSegments the discretization resolution
   * @return the vector of points (the discretized polyline)
   *
   ******************************************************/
  std::vector<gml::Point3D> discretize(int nbSegments);

  /*******************************************************
   * add a point to the polygone
   * @param point the point to add
   * @return ADDED or NOT_ADDED
   *
   ******************************************************/
  int addPoint(gml::Point3D *point);

};

#endif
