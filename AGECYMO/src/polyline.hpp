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

  std::vector<gml::Point3D> discretize();

  void managePressEvent(QMouseEvent* event,
			unsigned short toolType,
			unsigned short canvasType);

  void manageMoveEvent(QMouseEvent* event,
		       unsigned short toolType,
		       unsigned short canvasType);

  void manageReleaseEvent(QMouseEvent* event,
			  unsigned short toolType,
			  unsigned short canvasType);

  void manageDbClickEvent(QMouseEvent* event,
			  unsigned short toolType,
			  unsigned short canvasType);

};

#endif
