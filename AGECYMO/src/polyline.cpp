#include "polyline.hpp"

Polyline::Polyline(){
  _pointsVector.clear();
  _isClosed = false;
  _redComponent = 0.0;
  _greenComponent = 0.0;
  _blueComponent = 1.0;
  _isSelected.clear();
}

Polyline::Polyline(std::vector <gml::Point3D> pointsVector, bool isClosed){
  _pointsVector.clear();
  for(unsigned i=0; i<pointsVector.size(); i++){
    _pointsVector[i] = pointsVector[i];
  }
  _isClosed = isClosed;

  _redComponent = 0.0;
  _greenComponent = 0.0;
  _blueComponent = 1.0;
  _isSelected.clear();
}

Polyline::Polyline(const Polyline &source){
  for(int i = 0; i<source.getNbPoints(); i++){
    _pointsVector[i] = source.getPoint(i);
  }
  _isClosed = source.isClosed();
  _isSelected = source.isSelected();
  
}

void Polyline::addPoint(gml::Point3D newPoint){
  if(!_isClosed){
    if(isExistingPoint(newPoint) == 0){
      _isClosed = true;
    }
    else{
      _pointsVector.push_back(newPoint);
    }
  }
}

void Polyline::addPointAtIndex(gml::Point3D newPoint, int index){
  std::vector<gml::Point3D>::iterator it;
  if(((unsigned)index <= _pointsVector.size()) || (index >= 0)){
    it = _pointsVector.begin();
    it += index;
    _pointsVector.insert(it,newPoint);
  }
}

int Polyline::getNbPoints() const{
  return _pointsVector.size();
}

gml::Point3D Polyline::getPoint(int index) const{
  if(((unsigned)index < _pointsVector.size()) || (index >=0)){
    return _pointsVector[index];
  }
  exit(EXIT_FAILURE);
}

bool Polyline::isClosed() const{
  return _isClosed;
}

void Polyline::movePoint(int index, gml::Point3D newPosition){
  if(((unsigned)index<_pointsVector.size()) || (index >= 0)){ 
    _pointsVector[index] = newPosition;
  }
}

int Polyline::isExistingPoint(gml::Point3D point) const{
  for(unsigned i = 0; i<_pointsVector.size(); i++){
    if(((_pointsVector[i])[0] == point[0]) ||
       ((_pointsVector[i])[1] == point[1])){
      return i;
    }
  }
  return NO_EXIST;
}

void Polyline::deletePoint(int index){
  std::vector<gml::Point3D>::iterator it;
  if(((unsigned)index<_pointsVector.size()) || (index >= 0)){ 
    it =_pointsVector.begin();
    it += index;
    _pointsVector.erase(it);
  }
}

void Polyline::setColor(double red, double green, double blue){
  _redComponent = red;
  _greenComponent = green;
  _blueComponent = blue;
}

void Polyline::render(){

  double increment; 
  increment = Control_point_size / 2.0;
  
  glColor3f(_redComponent, _greenComponent, _blueComponent);

  glBegin(GL_LINE_STRIP);

  for(int i = 0 ; i < int(_pointsVector.size()); i++){
    glVertex2f(_pointsVector[i][0], _pointsVector[i][1]);
  }

  if(_isClosed){
    glVertex2f(_pointsVector[0][0], _pointsVector[0][1]);
  }

  glEnd();

  //we draw the control points
  for(int i = 0 ; i < int(_pointsVector.size()); i++){
    glBegin(GL_POLYGON);
    glVertex2f(_pointsVector[i][0]-increment, _pointsVector[i][1]-increment);
    glVertex2f(_pointsVector[i][0]-increment, _pointsVector[i][1]+increment);
    glVertex2f(_pointsVector[i][0]+increment, _pointsVector[i][1]+increment);
    glVertex2f(_pointsVector[i][0]+increment, _pointsVector[i][1]-increment);
    glEnd();
  }

}


void Polyline::selection(double xUpLeft, 
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

void Polyline::noSelection(){
  _isSelected.clear();
}

std::vector<unsigned short> Polyline::isSelected() const{
  return _isSelected;
}

void Polyline::select(unsigned short index){
  if(index<_pointsVector.size()){ 
    _isSelected.push_back(index);
  }
}

double Polyline::getRed() const{
  return _redComponent;
}

double Polyline::getGreen() const{
  return _greenComponent;
}

double Polyline::getBlue() const{
  return _blueComponent;
}

void Polyline::close(){
  _isClosed = true;
}

void Polyline::open(){
  _isClosed = false;
}
