#ifndef CLASS_CIRCLE
#define CLASS_CIRCLE

#include <vector>
#include "qgl.h"
#include "abscurve.hpp"

/*******************************************************
 * derived class of AbsCurve in order to draw a circle
 *
 ******************************************************/
class Circle : public AbsCurve 
{
private:
  
public:

  /*******************************************************
   * the default Circle constructor
   *
   ******************************************************/
  Circle();
  
  /*******************************************************
   * the Circle destructor
   *
   ******************************************************/
  ~Circle();
  
  /*******************************************************
   * draw the circle in the openGL widget
   *
   ******************************************************/
  void render();

  /*******************************************************
   * discretize the circle
   * @param nbDiscretizedPoints the number of discretized points
   * @return the vector of points (the discretized polyline)
   *
   ******************************************************/
  std::vector<gml::Point3D> discretize(int nbDiscretizedPoints);

  /*******************************************************
   * add a point to the polyline
   * @param point the point to add
   * @return ADDED or NOT_ADDED
   *
   ******************************************************/
  int addPoint(gml::Point3D *point);

  /**************************************************************
   *
   *  get the number of segment of the curve
   *  @return the number of segments
   *
   *************************************************************/
  int getNumberOfSegments();

};

#endif
