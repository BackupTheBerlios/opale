
#ifndef CURVES_CLASS
#define CURVES_CLASS

#include <vector>
#include "canvas2d.hpp"
#include "abscurve.hpp"
#include "point.hpp"
#include "polyline.hpp"

const double RED_DEFAULT = 0.58;   /**default red control points color*/
const double GREEN_DEFAULT = 0.58; /**default green control points color*/
const double BLUE_DEFAULT = 0.9;   /**default blue control points color*/

//default color of selected control points
const double RED_DEFAULT_SELECT = 0.94;   
/**red control select points color*/
const double GREEN_DEFAULT_SELECT = 0.55; 
/**green control select points color*/
const double BLUE_DEFAULT_SELECT = 0.55;  
/**red control select points color*/
const double Control_point_size = 0.03; 
/**size of the control point*/

class Canvas2D;

/******************************************************
 *  allow to control many curves in a canvas
 *
 ******************************************************/
class Curves
{
public:

  /**************************************************************
   *
   *  Curves constructor
   *  @param parent the parent canvas
   *
   *************************************************************/
  Curves(Canvas2D *parent);

  /**************************************************************
   *
   *  Curves destructor
   *
   *************************************************************/
  ~Curves();

  //curves management

  /**************************************************************
   *
   *  returns the number of managed curves
   *  @return the number of curves
   *
   *************************************************************/
  int getNbCurves();

  /**************************************************************
   *
   *  delete all the curves
   *
   *************************************************************/
  void deleteAllCurves();

  /**************************************************************
   *
   *  add a curve to the curves list
   *  @param newCurve the newCurve
   *
   *************************************************************/
  void addCurve(AbsCurve *newCurve);

  /**************************************************************
   *
   *  get all the curves
   *  @return a vector of curves
   *
   *************************************************************/
  std::vector<AbsCurve*> getAllCurves();

  /**************************************************************
   *
   *  change the current tool type
   *  @param toolType the new curent tool type
   *
   *************************************************************/
  void setCurrentToolType(unsigned short toolType);

  /**************************************************************
   *
   *  get the current tool type
   *  @return the current toolType
   *
   *************************************************************/
  unsigned short getCurrentToolType();
  
  //control point management


  /**************************************************************
   *
   *  returns the number of control points
   *  @return the number of control points
   *
   *************************************************************/
  int getNbControlPoints();

  /**************************************************************
   *
   *  add a point to control network
   *  @param newPoint the new control point
   *
   *************************************************************/
  void addPoint(gml::Point3D *newPoint);

  /**************************************************************
   *
   *  move a point of the control network
   *  @param index the index of the point in the network
   *  @param newPosition the new position of the point
   *
   *************************************************************/
  void movePoint(int index, gml::Point3D newPosition);

  /**************************************************************
   *
   *  get a point at an index
   *  @param index the index of the point in the network
   *  @return the point at the index or NULL if not exists
   *
   *************************************************************/
  gml::Point3D *getPointAtIndex(unsigned short index);

  /**************************************************************
   *
   *  get all the points of the network (save utility)
   *  @return the vector of all control points
   *
   *************************************************************/
  std::vector<gml::Point3D*> getAllPoints();

  /**************************************************************
   *
   *  define if the control network is closed
   *  @return true if closed, false else
   *
   *************************************************************/
  bool isClosed() const;

  /**************************************************************
   *
   *  close the control network. Rattach the last point of the
   *  last curve to the first point of the first curve
   *
   *************************************************************/
  void close();

  /**************************************************************
   *
   *  define the selected point when the user clicks on the canvas
   *  @param point the position of the click
   *  @return the index of the point, NO_EXIST if not exists
   *
   *************************************************************/
  int isExistingPoint(gml::Point3D point) const;

  //selection management


  /**************************************************************
   *
   *  select a point
   *  @param index the index of the point to be selected
   *
   *************************************************************/
  void select(unsigned short index);

  /**************************************************************
   *
   *  define if a point is selected
   *  @param index the index of the point
   *  @return true if selected, false else
   *
   *************************************************************/
  bool isSelected(int index);

  /**************************************************************
   *
   *  deselect all the points
   *
   *************************************************************/
  void noSelection();

  /**************************************************************
   *
   *  select all the points
   *
   *************************************************************/
  void selectAll();

  /**************************************************************
   *
   *  draw the entiere figure on the canvas (all the curves)
   *
   *************************************************************/
  void render();

  /**************************************************************
   *
   *  translate Qt coordinates into OpenGL coordinates
   *  @param event the event containing qt position
   *  @param point the new OpenGL coordinates
   *
   *************************************************************/
  void calculateQtToOpenGL(QMouseEvent* event, gml::Point3D *point);

  /**************************************************************
   *
   *  discretize the entiere figure (all the curves)
   *  @param nbSegments the number of segments between two control
   *   point of the network
   *  @return the list of points
   *
   *************************************************************/
  std::vector<gml::Point3D> discretize(int nbSegments);

  //colors management


  /**************************************************************
   *
   *  set the control points colors
   *  @param red the red component
   *  @param green the green component
   *  @param blue the blue component
   *
   *************************************************************/
  void setColor(double red, double green, double blue);

  /**************************************************************
   *
   *  set the selected control points colors
   *  @param red the red component
   *  @param green the green component
   *  @param blue the blue component
   *
   *************************************************************/
  void setSelectionColor(double red, double green, double blue);

  /**************************************************************
   *
   *  get the network control points color
   *  @param red the red component
   *  @param green the green component
   *  @param blue the blue component
   *
   *************************************************************/
  gml::Point3D getColor();

  /**************************************************************
   *
   *  get the network control points color when selected
   *  @return a vector point with the RGB colors
   *
   *************************************************************/
  gml::Point3D getSelectionColor();

  //events management

  /**************************************************************
   *
   *  manage the mousePressEvent
   *  @param event the event
   *  @param toolType the canvas toolType in use
   *  @param canvasType the type of the canvas
   *
   *************************************************************/
  void managePressEvent(QMouseEvent* event,
			unsigned short toolType,
			unsigned short canvasType);

  /**************************************************************
   *
   *  manage the mouseMoveEvent
   *  @param event the event
   *  @param toolType the canvas toolType in use
   *  @param canvasType the type of the canvas
   *
   *************************************************************/
  void manageMoveEvent(QMouseEvent* event,
		       unsigned short toolType,
		       unsigned short canvasType);

  /**************************************************************
   *
   *  manage the mouseReleaseEvent
   *  @param event the event
   *  @param toolType the canvas toolType in use
   *  @param canvasType the type of the canvas
   *
   *************************************************************/
  void manageReleaseEvent(QMouseEvent* event,
			  unsigned short toolType,
			  unsigned short canvasType);

  /**************************************************************
 *
 *  manage the doubleClickEvent
 *  @param event the event
 *  @param toolType the canvas toolType in use
 *  @param canvasType the type of the canvas
 *
 *************************************************************/
  void manageDbClickEvent(QMouseEvent* event,
			  unsigned short toolType,
			  unsigned short canvasType);

private:

  Canvas2D *_parent; /**the parent widget*/
  vector <AbsCurve*> _listOfCurves; /**the list of the curves*/
  vector <gml::Point3D*> _listOfControlPoints; /**the list of control points*/
  unsigned short _currentToolType; /**the current tool type*/
  bool _isClosed; /**control if the network is closed*/
  double _redComponent; /**red component of the network*/
  double _greenComponent; /**green component of the network*/
  double _blueComponent; /**blue component of the network*/
  double _redComponentSelect; /**red component of the network selection*/
  double _greenComponentSelect; /**green component of the network selection*/
  double _blueComponentSelect; /**blue component of the network selection*/
  std::vector<int> _isSelected; /**list of selected control points*/
  gml::Point3D _startMovePoint; /**parameter for control points moving*/
};

#endif
