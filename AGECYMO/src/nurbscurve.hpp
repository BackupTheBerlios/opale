#ifndef CLASS_NURBSCURVE
#define CLASS_NURBSCURVE

#include <vector>
#include "qgl.h"
#include "abscurve.hpp"

class NurbsCurve : public AbsCurve 
{
private:

  int nbPointsDefine;
  
public:

  NurbsCurve(Canvas2D *parent);

  NurbsCurve(std::vector<gml::Point3D> pointsVector, 
	   bool isClosed,
	   Canvas2D *parent);

  NurbsCurve(const NurbsCurve &source);

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
