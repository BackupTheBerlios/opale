#ifndef CLASS_ABSCURVE
#define CLASS_ABSCURVE

#include <vector>
#include "point.hpp"
#include "qgl.h"

class Canvas2D;

//color of the polylines
const double RED_DEFAULT = 0.0;
const double GREEN_DEFAULT = 0.0;
const double BLUE_DEFAULT = 1.0;

//color of the control points
const double RED_DEFAULT_SELECT = 1.0;
const double GREEN_DEFAULT_SELECT = 0.0;
const double BLUE_DEFAULT_SELECT = 0.0;

//various cosntant values
const int NO_EXIST = -1;
const int NO_SELECTION = -1;

//size of control points
const double Control_point_size = 0.10;

class AbsCurve
{

  //Public Members/Attributes
  public:
  
  //Protected Members/Attributes
  protected:

  Canvas2D *_parent;

  //control points
  std::vector <gml::Point3D> _pointsVector;

  //if the curve is closed
  bool _isClosed;

  //color component for curve render
  double _redComponent, _greenComponent, _blueComponent;

  //color for control point selection
  double _redComponentSelect, _greenComponentSelect, _blueComponentSelect;

  //selected points
  std::vector<int> _isSelected;

  //public methods
  public:

  AbsCurve(Canvas2D *parent);
  AbsCurve(std::vector<gml::Point3D> pointsVector, 
           bool isClosed,
           Canvas2D *parent);
  AbsCurve::AbsCurve(const AbsCurve &source);
  virtual ~AbsCurve();
  
  //draw the curve
  virtual void render() = 0;

  //for events management
  virtual void manageEvent(QMouseEvent* event,
                           unsigned short toolType,
                           unsigned short canvasType);

  //add a point to the curve
  virtual void addPoint(gml::Point3D newPoint);

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
  std::vector<int> isSelected() const;

  //selection of a point
  void select(unsigned short index);

  //selection of few points
  void selection(double xUpLeft, double yUpLeft,
                 double xDownRight, double yDownRight);

  void noSelection();

  //define colors of the curve
  void setColor(double red, double green, double blue);

  //define colors of selected control points
  void setSelectionColor(double red, double green, double blue);

  //get color values of the curve
  double getRed() const;
  double getGreen() const;
  double getBlue() const;

  //get color values of control points
  double getRedSelect() const;
  double getGreenSelect() const;
  double getBlueSelect() const;

  //Protected Methods
  protected:

  void calculateQtToOpenGL(QMouseEvent* event, gml::Point3D *point);

};

#endif
