#ifndef CLASS_ABSCURVE
#define CLASS_ABSCURVE

#include <vector>
#include "point.hpp"
#include "qgl.h"

const double RED_DEFAULT = 0.0;
const double GREEN_DEFAULT = 0.0;
const double BLUE_DEFAULT = 1.0;

const double RED_DEFAULT_SELECT = 1.0;
const double GREEN_DEFAULT_SELECT = 0.0;
const double BLUE_DEFAULT_SELECT = 0.0;
const int NO_EXIST = -1;
const int NO_SELECTION = -1;
const double Control_point_size = 0.10;


class AbsCurve
{

  //Public Members/Attributes
public:

  
  //Protected Members/Attributes
protected:

  //control points
  std::vector <gml::Point3D> _pointsVector;
  //if the curve is closed
  bool _isClosed;
  //color component for curve render
  double _redComponent, _greenComponent, _blueComponent;
  //color for control point selection
  double _redComponentSelect, _greenComponentSelect, _blueComponentSelect;

  std::vector<unsigned short> _isSelected;

  //public methods
public:

  AbsCurve();
  AbsCurve(std::vector<gml::Point3D> pointsVector, bool isClosed);
  AbsCurve::AbsCurve(const AbsCurve &source);
  virtual ~AbsCurve();
  
  //draw the curve
  virtual void render() = 0;
  //discretize the curve
  virtual std::vector<gml::Point3D> discretize() = 0;
  //add a point to the curve
  void addPoint(gml::Point3D newPoint);
  //add a point at index
  void addPointAtIndex(gml::Point3D newPoint, int index);
  //return the number of control points of the curves
  int getNbPoints() const;
  //return the point at index
  gml::Point3D getPoint(int index) const;
  //true if the curve is closed
  bool isClosed() const;
  //close the curve
  void close();
  //open the curve
  void open();
  //move the index point at newPosition
  void movePoint(int index, gml::Point3D newPosition);
  //return the index of the point if defined, -1 else
  int isExistingPoint(gml::Point3D point) const;
  //delete the index point
  void deletePoint(int index);
  //define if a point is selected
  std::vector<unsigned short> isSelected() const;
  //selection of a point
  void select(unsigned short index);
  //selection of few points
  void selection(double xUpLeft, double yUpLeft,
		 double xDownRight, double yDownRight);
  void noSelection();
  //define the color of the curve
  void setColor(double red, double green, double blue);
  //define the color of selected control points of the curve
  void setSelectionColor(double red, double green, double blue);
  //get the color values of the curve
  double getRed() const;
  double getGreen() const;
  double getBlue() const;
  //get the color values of the control points of the curve
  double getRedSelect() const;
  double getGreenSelect() const;
  double getBlueSelect() const;

  //Protected Methods
protected:

};

#endif
