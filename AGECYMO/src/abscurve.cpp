#include "abscurve.hpp"

AbsCurve::AbsCurve()
{
  _pointsVector.clear();
  _redColor = RED_COLOR;
  _greenColor = GREEN_COLOR;
  _blueColor = BLUE_COLOR;
}

AbsCurve::~AbsCurve()
{}

int AbsCurve::getNbPoints() const{
  return _pointsVector.size();
}

gml::Point3D *AbsCurve::getPoint(int index) const{
  if(((unsigned)index < _pointsVector.size()) || (index >=0)){
    return _pointsVector[index];
  }
}

bool AbsCurve::isEmpty()
{
  return _pointsVector.empty();
}

bool AbsCurve::containPoint(gml::Point3D *point)
{
  for(unsigned i = 0; i<_pointsVector.size(); i++){
    if(point == _pointsVector[i]) return true;
  }
  return false;
}


