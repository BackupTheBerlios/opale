#ifndef CLASS_CIRCLE
#define CLASS_CIRCLE

#include <vector>
#include "qgl.h"
#include "abscurve.hpp"

class Circle : public AbsCurve 
{
private:
  
public:

  Circle(Canvas2D *parent);

  Circle(std::vector<gml::Point3D> pointsVector, 
	   bool isClosed,
	   Canvas2D *parent);

  Circle(const Circle &source);

  void render();

  std::vector<gml::Point3D> discretize(int nbSegments);

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
