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

  //the prent widget
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
  //start point for move action
  gml::Point3D _startMovePoint;

  //public methods
  public:

  AbsCurve(Canvas2D *parent);
  AbsCurve(std::vector<gml::Point3D> pointsVector, 
           bool isClosed,
           Canvas2D *parent);
  AbsCurve::AbsCurve(const AbsCurve &source);
  virtual ~AbsCurve();
  

  virtual void render() = 0;
  virtual void manageEvent(QMouseEvent* event,
                           unsigned short toolType,
                           unsigned short canvasType);
  virtual void manageKeyEvent(QKeyEvent* event,
			      unsigned short toolType,
			      unsigned short canvasType);

  //virtual methods (can be redefined)
  virtual void addPoint(gml::Point3D newPoint);
  virtual void deletePoint(int index);
  virtual void deleteSelected();
  virtual void movePoint(int index, gml::Point3D newPosition);

  //non virtual methods
  int getNbPoints() const;
  gml::Point3D getPoint(int index) const;
  bool isClosed() const;
  void close();
  void open();
  int isExistingPoint(gml::Point3D point) const;
  bool isEmpty();
  void select(unsigned short index);
  bool isSelected(int index);
  void noSelection();
  void setColor(double red, double green, double blue);
  void setSelectionColor(double red, double green, double blue);
  double getRed() const;
  double getGreen() const;
  double getBlue() const;
  double getRedSelect() const;
  double getGreenSelect() const;
  double getBlueSelect() const;

  //Protected Methods
  protected:

  void calculateQtToOpenGL(QMouseEvent* event, gml::Point3D *point);

};

#endif
