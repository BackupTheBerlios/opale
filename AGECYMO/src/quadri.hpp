#ifndef CLASS_QUADRI
#define CLASS_QUADRI

#include <vector>
#include "qgl.h"
#include "abscurve.hpp"

class Quadri : public AbsCurve 
{
private:
  
public:

  Quadri(Canvas2D *parent);

  Quadri(std::vector<gml::Point3D> pointsVector, 
	   bool isClosed,
	   Canvas2D *parent);

  Quadri(const Quadri &source);

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
