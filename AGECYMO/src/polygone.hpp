#ifndef CLASS_POLYGONE
#define CLASS_POLYGONE

#include <vector>
#include "qgl.h"
#include "abscurve.hpp"

class Polygone : public AbsCurve 
{
private:

  int _nbPoints;
  
public:
  Polygone(Canvas2D *parent);
  Polygone(std::vector<gml::Point3D> pointsVector, 
	   bool isClosed,
	   Canvas2D *parent);
  Polygone(const Polygone &source);
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
