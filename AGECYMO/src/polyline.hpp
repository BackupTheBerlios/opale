#ifndef CLASS_POLYLINE
#define CLASS_POLYLINE

#include <vector>
#include "qgl.h"
#include "abscurve.hpp"

class Polyline : public AbsCurve 
{
private:
  
public:
  Polyline(Canvas2D *parent);
  Polyline(std::vector<gml::Point3D> pointsVector, 
	   bool isClosed,
	   Canvas2D *parent);
  Polyline(const Polyline &source);
  void render();
  void manageEvent(QMouseEvent* event,
		   unsigned short toolType,
		   unsigned short canvasType);
  std::vector<gml::Point3D> discretize();
  void calculateQtToOpenGL(QMouseEvent* event, gml::Point3D *point);
};

#endif
