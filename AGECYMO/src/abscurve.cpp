#include "abscurve.hpp"
#include "canvas2d.hpp"

AbsCurve::AbsCurve(Canvas2D *parent)
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
  _parent = parent;
}

AbsCurve::AbsCurve(std::vector <gml::Point3D> pointsVector, 
		   bool isClosed,
		   Canvas2D *parent){
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
  _parent = parent;
}


AbsCurve::AbsCurve(const AbsCurve &source)
{
  for(int i = 0; i<source.getNbPoints(); i++){
    _pointsVector[i] = source.getPoint(i);
  }
  _isClosed = source.isClosed();
  _isSelected = source._isSelected;

  _redComponent = source.getRed();
  _greenComponent = source.getGreen() ;
  _blueComponent = source.getBlue();
  _redComponentSelect = source.getRedSelect();
  _greenComponentSelect = source.getGreenSelect() ;
  _blueComponentSelect = source.getBlueSelect();
  _parent = source._parent;
}


AbsCurve::~AbsCurve()
{
  _pointsVector.clear();
}

//for events management
void AbsCurve::managePressEvent(QMouseEvent* event,
				unsigned short toolType,
				unsigned short canvasType)
{}

void AbsCurve::manageMoveEvent(QMouseEvent* event,
			       unsigned short toolType,
			       unsigned short canvasType)
{}

void AbsCurve::manageReleaseEvent(QMouseEvent* event,
			unsigned short toolType,
			unsigned short canvasType)
{}

void AbsCurve::manageDbClickEvent(QMouseEvent* event,
				  unsigned short toolType,
				  unsigned short canvasType)
{}

void AbsCurve::addPoint(gml::Point3D newPoint){
    _pointsVector.push_back(newPoint);
}

int AbsCurve::getNbPoints() const{
  return _pointsVector.size();
}

gml::Point3D AbsCurve::getPoint(int index) const{
  if(((unsigned)index < _pointsVector.size()) || (index >=0)){
    return _pointsVector[index];
  }
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
    if(((_pointsVector[i])[0] <= point[0] + increment) &&
       ((_pointsVector[i])[0] >= point[0] - increment) &&
       ((_pointsVector[i])[1] <= point[1] + increment) &&
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

bool AbsCurve::isEmpty()
{
  return _pointsVector.empty();
}

void AbsCurve::deleteSelected()
{
  for(unsigned i = 0; i<_isSelected.size(); i++){
    deletePoint(_isSelected[(int)i]);
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

void AbsCurve::noSelection(){
  _isSelected.clear();
}

void AbsCurve::selectAll()
{
  noSelection();
  for(unsigned i = 0; i<_pointsVector.size(); i++){
    select(i);
  }
}

void AbsCurve::select(unsigned short index){
  bool alreadySelected = false;
  for(unsigned i = 0; i<_isSelected.size(); i++){
    if(_isSelected[i] == index){
      alreadySelected = true;
    }
  }
  if((index<_pointsVector.size()) && (!alreadySelected)){ 
    _isSelected.push_back(index);
  }
}

bool AbsCurve::isSelected(int index){
  for(unsigned i = 0; i<_isSelected.size(); i++){
    if(index == _isSelected[i]){
      return true;
    }
  }
  return false;
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

void AbsCurve::calculateQtToOpenGL(QMouseEvent* event, gml::Point3D *point)
{
  //coordinate calcul for qt/openGl traduction
  (*point)[0] =
    -glOrthoParameter + 
    ((double)event->x() * ((glOrthoParameter*2)/(double)_parent->width()));
  (*point)[1] =
    glOrthoParameter - 
    ((double)event->y() * ((glOrthoParameter*2)/(double)_parent->height()));
}
