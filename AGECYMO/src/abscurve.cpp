#include "abscurve.hpp"

AbsCurve::AbsCurve()
{
  _pointsVector.clear();
  _isClosed = false;

  //color of the curve
  _redComponent = RED_DEFAULT;
  _greenComponent = GREEN_DEFAULT;
  _blueComponent = BLUE_DEFAULT;

  //color of the selected control points
  _redComponentSelect = RED_DEFAULT_SELECT;
  _greenComponentSelect = GREEN_DEFAULT_SELECT;
  _blueComponentSelect = BLUE_DEFAULT_SELECT;

  //no selection
  _isSelected.clear();
}

AbsCurve::AbsCurve(std::vector <gml::Point3D> pointsVector, bool isClosed){
  _pointsVector.clear();
  for(unsigned i=0; i<pointsVector.size(); i++){
    _pointsVector[i] = pointsVector[i];
  }
  _isClosed = isClosed;

  //color of the curve
  _redComponent = RED_DEFAULT;
  _greenComponent = GREEN_DEFAULT;
  _blueComponent = BLUE_DEFAULT;

  //color of the selected control points
  _redComponentSelect = RED_DEFAULT_SELECT;
  _greenComponentSelect = GREEN_DEFAULT_SELECT;
  _blueComponentSelect = BLUE_DEFAULT_SELECT;

  //no selection
  _isSelected.clear();
}


AbsCurve::AbsCurve(const AbsCurve &source)
{
  for(int i = 0; i<source.getNbPoints(); i++){
    _pointsVector[i] = source.getPoint(i);
  }
  _isClosed = source.isClosed();
  _isSelected = source.isSelected();

  _redComponent = source.getRed();
  _greenComponent = source.getGreen() ;
  _blueComponent = source.getBlue();
  _redComponentSelect = source.getRedSelect();
  _greenComponentSelect = source.getGreenSelect() ;
  _blueComponentSelect = source.getBlueSelect();
}


AbsCurve::~AbsCurve()
{
  _pointsVector.clear();
}

void AbsCurve::addPoint(gml::Point3D newPoint){
    _pointsVector.push_back(newPoint);
}

void AbsCurve::addPointAtIndex(gml::Point3D newPoint, int index){
  std::vector<gml::Point3D>::iterator it;
  if(((unsigned)index <= _pointsVector.size()) || (index >= 0)){
    it = _pointsVector.begin();
    it += index;
    _pointsVector.insert(it,newPoint);
  }
}

int AbsCurve::getNbPoints() const{
  return _pointsVector.size();
}

gml::Point3D AbsCurve::getPoint(int index) const{
  if(((unsigned)index < _pointsVector.size()) || (index >=0)){
    return _pointsVector[index];
  }
  exit(EXIT_FAILURE);
}

bool AbsCurve::isClosed() const{
  return _isClosed;
}

void AbsCurve::movePoint(int index, gml::Point3D newPosition){
  if(((unsigned)index<_pointsVector.size()) || (index >= 0)){ 
    _pointsVector[index] = newPosition;
  }
}

int AbsCurve::isExistingPoint(gml::Point3D point) const{
  double increment; 
  increment = Control_point_size / 2.0;
  for(unsigned i = 0; i<_pointsVector.size(); i++){
    if(((_pointsVector[i])[0] <= point[0] + increment) ||
       ((_pointsVector[i])[0] >= point[0] - increment) ||
       ((_pointsVector[i])[1] <= point[1] + increment) ||
       ((_pointsVector[i])[1] >= point[1] - increment)){
      return i;
    }
  }
  return NO_EXIST;
}

void AbsCurve::deletePoint(int index){
  std::vector<gml::Point3D>::iterator it;
  if(((unsigned)index<_pointsVector.size()) || (index >= 0)){ 
    it =_pointsVector.begin();
    it += index;
    _pointsVector.erase(it);
  }
}

void AbsCurve::setColor(double red, double green, double blue){
  _redComponent = red;
  _greenComponent = green;
  _blueComponent = blue;
}

void AbsCurve::setSelectionColor(double red, double green, double blue){
  _redComponentSelect = red;
  _greenComponentSelect = green;
  _blueComponentSelect = blue;
}

void AbsCurve::render()
{}


std::vector<gml::Point3D> AbsCurve::discretize()
{}

void AbsCurve::selection(double xUpLeft, 
			 double yUpLeft,
			 double xDownRight, 
			 double yDownRight){
  _isSelected.clear();

  //we define the selected points
  for(unsigned int i = 0; i<_pointsVector.size(); i++){
    if((_pointsVector[i][0] >= xUpLeft ) || 
       (_pointsVector[i][0] <= xDownRight ) ||
       (_pointsVector[i][1] <= yUpLeft ) || 
       (_pointsVector[i][1] >= yDownRight )){
      
      //we select the point
      _isSelected.push_back(i);
    }
  }
}

void AbsCurve::noSelection(){
  _isSelected.clear();
}

std::vector<unsigned short> AbsCurve::isSelected() const{
  return _isSelected;
}

void AbsCurve::select(unsigned short index){
  if(index<_pointsVector.size()){ 
    _isSelected.push_back(index);
  }
}

double AbsCurve::getRed() const{
  return _redComponent;
}

double AbsCurve::getGreen() const{
  return _greenComponent;
}

double AbsCurve::getBlue() const{
  return _blueComponent;
}

double AbsCurve::getRedSelect() const{
  return _redComponentSelect;
}

double AbsCurve::getGreenSelect() const{
  return _greenComponentSelect;
}

double AbsCurve::getBlueSelect() const{
  return _blueComponentSelect;
}

void AbsCurve::close(){
  _isClosed = true;
}

void AbsCurve::open(){
  _isClosed = false;
}
