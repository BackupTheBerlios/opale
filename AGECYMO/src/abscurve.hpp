#ifndef CLASS_ABSCURVE
#define CLASS_ABSCURVE

#include <vector>
#include "point.hpp"
#include "qgl.h"

//color for figure render
const double RED_COLOR = 0.66;  /**red color for figure render*/
const double GREEN_COLOR = 0.9; /**green color for figure render*/
const double BLUE_COLOR = 0.58; /**blue color for figure render*/

const int NO_EXIST = -1;        /**point not exists*/
const int NO_SELECTION = -1;    /**no selection*/
const int NOT_ADDED = -1;       /**point not added*/
const int ADDED = 0;            /**point added*/


/**************************************************************
 *
 *  generic class in order to define objects (like polylines...)
 *
 *************************************************************/
class AbsCurve
{
protected:
  
  std::vector <gml::Point3D*> _pointsVector; /**the list of points*/

public:

  /**************************************************************
   *
   *  AbsCurve default constructor
   *
   *************************************************************/
  AbsCurve();

  /**************************************************************
   *
   *  AbsCurve destructor
   *
   *************************************************************/
  virtual ~AbsCurve();

  //virtual methods (must be redefined)

  /**************************************************************
   *
   *  fonction in order to draw in the object into the opengl 
   *  widget.
   *
   *************************************************************/
  virtual void render() = 0;

  /**************************************************************
   *
   *  add a point to the object
   *  @param newPoint the new point to bo added
   *  @return ADDED or NOT_ADDED
   *
   *************************************************************/
  virtual int addPoint(gml::Point3D *newPoint) = 0;

  /**************************************************************
   *
   *  discretize the object
   *  @param nbDiscretizedPoints the number of discretized points 
   *  between two points of a segment of the curve.
   *  @return the vector of the discretized object
   *
   *************************************************************/
  virtual std::vector<gml::Point3D> discretize(int nbDiscretizedPoints) = 0;

  /**************************************************************
   *
   *  get the number of segment of the curve
   *  @return the number of segments
   *
   *************************************************************/
  virtual int getNumberOfSegments() = 0;

  //non virtual methods

  /**************************************************************
   *
   *  return the number of points of the object
   *  @return the number of point of the object
   *
   *************************************************************/
  int getNbPoints() const;

  /**************************************************************
   *
   *  get the point at a given index
   *  @param index the index of the point
   *  @return the point at index or NULL if not exists
   *
   *************************************************************/
  gml::Point3D *getPoint(int index) const;

  /**************************************************************
   *  
   *  returns whether or not the object is empty (contains no points)
   *  @return true if empty, false else
   *
   *************************************************************/
  bool isEmpty();

  /**************************************************************
   *  
   *  returns whether or not a point is contained by the object
   *  @param point the point to be tested
   *  @return true if the object contains the point, false else
   *
   *************************************************************/
  bool containPoint(gml::Point3D *point);

  /**************************************************************
   *  
   *  set the curve render color
   *  @param red the red component
   *  @param green the green component
   *  @param blue the blue component
   *
   *************************************************************/
  void setColor(double red, double green, double blue);

protected:

  double _redColor;   /**red render color of the object*/
  double _greenColor; /**green render color of the object*/
  double _blueColor;  /**blue render color of the object*/
};

#endif
