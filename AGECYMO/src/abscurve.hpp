//
//  abscurves.hpp
//  
//  allow to a generic curve
//


#ifndef CLASS_ABSCURVE
#define CLASS_ABSCURVE

#include <vector>
#include "point.hpp"
#include "qgl.h"

//color for figure render
const double RED_COLOR = 0.66;
const double GREEN_COLOR = 0.9;
const double BLUE_COLOR = 0.58;

//various cosntant values
const int NO_EXIST = -1;
const int NO_SELECTION = -1;
const int NOT_ADDED = -1;
const int ADDED = 0;

//size of control points
const double Control_point_size = 0.03;

class AbsCurve
{
  //Protected Members/Attributes
protected:
  std::vector <gml::Point3D*> _pointsVector;

  //public methods
public:

  AbsCurve();
  virtual ~AbsCurve();

  //virtual methods (must be redefined)
  virtual void render() = 0;
  virtual int addPoint(gml::Point3D *newPoint) = 0;
  virtual std::vector<gml::Point3D> discretize(int nbSegments) = 0;

  //non virtual methods
  int getNbPoints() const;
  gml::Point3D *getPoint(int index) const;
  bool isEmpty();
  bool containPoint(gml::Point3D *point);
  double _redColor, _greenColor, _blueColor;
};

#endif
