//
//  curves.hpp
//  
//  allow to control fewers curves in canvas
//

#ifndef CURVES_CLASS
#define CURVES_CLASS

#include <vector>
#include "canvas2d.hpp"
#include "abscurve.hpp"
#include "point.hpp"
#include "polyline.hpp"


//default color of control points
const double RED_DEFAULT = 0.0;
const double GREEN_DEFAULT = 0.0;
const double BLUE_DEFAULT = 1.0;

//default color of selected control points
const double RED_DEFAULT_SELECT = 1.0;
const double GREEN_DEFAULT_SELECT = 0.0;
const double BLUE_DEFAULT_SELECT = 0.0;

class Canvas2D;

class Curves
{
public:

  Curves(Canvas2D *parent);
  ~Curves();

  int getNbCurves();
  void deleteAllCurves();

  //control point management
  int getNbControlPoints();
  void addPoint(gml::Point3D *newPoint);
  void movePoint(int index, gml::Point3D newPosition);
  bool isClosed() const;
  void close();
  int isExistingPoint(gml::Point3D point) const;

  //selection management
  void select(unsigned short index);
  bool isSelected(int index);
  void noSelection();
  void selectAll();

  //render and discretize all curves
  void render();
  std::vector<gml::Point3D> discretize(int nbSegments);
  void calculateQtToOpenGL(QMouseEvent* event, gml::Point3D *point);

  //colors management
  void setColor(double red, double green, double blue);
  void setSelectionColor(double red, double green, double blue);

  //events management
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

private:

  //parent canvas
  Canvas2D *_parent;
  
  //the list of curves
  vector <AbsCurve*> _listOfCurves;

  //the list of control points
  vector <gml::Point3D*> _listOfControlPoints;

  //the current toolType in use in the current curve
  unsigned short _currentToolType;

  //if the control network is closed
  bool _isClosed;
  
  //color of control points
  double _redComponent, _greenComponent, _blueComponent;

  //color of selected control points
  double _redComponentSelect, _greenComponentSelect, _blueComponentSelect;

  //the list of selected points
  std::vector<int> _isSelected;

  //start move position for control point management
  gml::Point3D _startMovePoint;
};

#endif
