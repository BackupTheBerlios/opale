#include "polyline.hpp"

Polyline::Polyline(){
  _pointsVector.clear();
  _isClosed = false;
  _redComponent = 1.0;
  _greenComponent = 0.0;
  _blueComponent = 0.0;
  _isSelected = NO_SELECTION;
}

Polyline::Polyline(std::vector <gml::Point3D> pointsVector, bool isClosed){
  _pointsVector.clear();
  for(unsigned i=0; i<pointsVector.size(); i++){
    _pointsVector[i] = pointsVector[i];
  }
  _isClosed = isClosed;

  _redComponent = 1.0;
  _greenComponent = 0.0;
  _blueComponent = 0.0;
  _isSelected = NO_SELECTION;
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
  
  glColor3f(_redComponent, _greenComponent, _blueComponent);

  for(int i = 0 ; i < int(_pointsVector.size()-1); i++){
    std::cout<<"Dx"<<_pointsVector[i][0]<<std::endl;
    std::cout<<"Dy"<<_pointsVector[i][1]<<std::endl;
    
    std::cout<<"Fx"<<_pointsVector[i+1][0]<<std::endl;
    std::cout<<"Fy"<<_pointsVector[i+1][1]<<std::endl;

    glBegin(GL_LINES);
        glVertex2f(_pointsVector[i][0], _pointsVector[i][1]);
        glVertex2f(_pointsVector[i+1][0], _pointsVector[i+1][1]);
    glEnd();
  }

}

int Polyline::isSelected() const{
  return _isSelected;
}

void Polyline::select(int index){
  if(((unsigned)index<_pointsVector.size()) || (index >= 0)){ 
    _isSelected = index;
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
