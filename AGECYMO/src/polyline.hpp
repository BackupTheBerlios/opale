#ifndef CLASS_POLYLINE
#define CLASS_POLYLINE

#include <vector>
#include "point.hpp"
#include "qgl.h"

#define NO_EXIST -1;
#define NO_SELECTION -1;
const double Control_point_size = 0.10;

class Polyline
{
private:
  std::vector <gml::Point3D> _pointsVector;
  bool _isClosed;
  double _redComponent, _greenComponent, _blueComponent;
  std::vector<unsigned short> _isSelected;

public:
  Polyline();
  Polyline(std::vector<gml::Point3D> pointsVector, bool isClosed);
  Polyline(const Polyline &source);

  //add a point to the polyline
  void addPoint(gml::Point3D newPoint);
  //add a point at index
  void addPointAtIndex(gml::Point3D newPoint, int index);
  //return the number of points in the polyline
  int getNbPoints() const;
  //return the point at index
  gml::Point3D getPoint(int index) const;
  //true if the polyline is closed
  bool isClosed() const;
  //close the polyline
  void close();
  //open the polyline
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
  //define the color of the polyline
  void setColor(double red, double green, double blue);
  //draw the polyline
  void render();
  //get the color values
  double getRed() const;
  double getGreen() const;
  double getBlue() const;
  
};

#endif
