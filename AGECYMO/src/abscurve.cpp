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
 *  return the number of points of the object
 *  @return the number of point of the object
 *
 *************************************************************/
int AbsCurve::getNbPoints() const{
  return _pointsVector.size();
}

/**************************************************************
 *
 *  get the point at an index
 *  @param index the index of the point
 *  @return the point at index or NULL if not exists
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
 *  define if the object is empty (contains no points)
 *  @return true if empty, false else
 *
 *************************************************************/
bool AbsCurve::isEmpty()
{
  return _pointsVector.empty();
}

/**************************************************************
 *
 *  define if a point is contained by the object
 *  @param point the point to be tested
 *  @return true if the object contains the point, false else
 *
 *************************************************************/
bool AbsCurve::containPoint(gml::Point3D *point)
{
  for(unsigned i = 0; i<_pointsVector.size(); i++){
    if(point == _pointsVector[i]) return true;
  }
  return false;
}


