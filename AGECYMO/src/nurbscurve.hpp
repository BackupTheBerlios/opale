#ifndef CLASS_NURBSCURVE
#define CLASS_NURBSCURVE

#include <vector>
#include "qgl.h"
#include "abscurve.hpp"

//color for figure render
const double RED_NURB = 0.86; /**red component of the nurbs*/
const double GREEN_NURB = 0.78; /**green component of the nurbs*/
const double BLUE_NURB = 0.4; /**blue component of the nurbs*/

/*******************************************************
 * derived class of AbsCurve in order to draw nurbs
 *
 ******************************************************/
class NurbsCurve : public AbsCurve 
{
private:

  int _nbPointsDefine; /**number of defined points*/
  std::vector<float> _HCoordinateVector; /**height vector*/
  
public:
  
  /*******************************************************
   * the default NurbsCurve constructor
   *
   ******************************************************/
  NurbsCurve();

  /*******************************************************
   * the NurbsCurve destructor
   *
   ******************************************************/
  ~NurbsCurve();

  /*******************************************************
   * draw the nurbs in the openGL widget
   *
   ******************************************************/
  void render();

  /*******************************************************
   * discretize the nurbs
   * @param nbSegments the discretization resolution
   * @return the vector of points (the discretized polyline)
   *
   ******************************************************/
  std::vector<gml::Point3D> discretize(int nbSegments);

  /*******************************************************
   * add a point to the nurbs
   * @param point the point to add
   * @return ADDED or NOT_ADDED
   *
   ******************************************************/
  int addPoint(gml::Point3D *point);

};

#endif
