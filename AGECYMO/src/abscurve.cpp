//
//  abscurve.cpp
//  
//  implementation of the class Curves
//

#include "abscurve.hpp"


/**************************************************************
 *
 *  AbsCurve constructor
 *
 *************************************************************/
AbsCurve::AbsCurve()
{
  _pointsVector.clear();
  _redColor = RED_COLOR;
  _greenColor = GREEN_COLOR;
  _blueColor = BLUE_COLOR;
}

/**************************************************************
 *
 *  AbsCurve destructor
 *
 *************************************************************/
AbsCurve::~AbsCurve()
{}

/**************************************************************
 *
 *  return the number of control points
 *  @return the number of control points
 *
 *************************************************************/
int AbsCurve::getNbPoints() const{
  return _pointsVector.size();
}

/**************************************************************
 *
 *  get a point at an index
 *  @param index the index of the point
 *  @return the point at the index
 *
 *************************************************************/
gml::Point3D *AbsCurve::getPoint(int index) const{
  if(((unsigned)index < _pointsVector.size()) || (index >=0)){
    return _pointsVector[index];
  }

  //here a log error
  return NULL;
}

/**************************************************************
 *
 *  define if the curve is empty
 *  @return true if empty, false else
 *
 *************************************************************/
bool AbsCurve::isEmpty()
{
  return _pointsVector.empty();
}

/**************************************************************
 *
 *  define if the curve contain a point
 *  @param point the concerned point
 *  @return true if the curve contains the point, false else
 *
 *************************************************************/
bool AbsCurve::containPoint(gml::Point3D *point)
{
  for(unsigned i = 0; i<_pointsVector.size(); i++){
    if(point == _pointsVector[i]) return true;
  }
  return false;
}


