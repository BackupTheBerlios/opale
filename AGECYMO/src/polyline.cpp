#include "abscurve.hpp"
#include "polyline.hpp"
#include <iostream>
#include "canvas2d.hpp"

using namespace std;

Polyline::Polyline(Canvas2D *parent)
  :
  AbsCurve(parent)
{}

Polyline::Polyline(std::vector<gml::Point3D> pointsVector, 
		   bool isClosed,
		   Canvas2D *parent)
  :
  AbsCurve(pointsVector, isClosed, parent)
{}

Polyline::Polyline(const Polyline &source)
  :
  AbsCurve(source)
{
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

  glColor3f(_redComponent, _greenComponent, _blueComponent);
  bool selected;
  //we draw the control points
  for(int i = 0 ; i < int(_pointsVector.size()); i++){
    
    selected = false;
    for(int j = 0; j<int(_isSelected.size()); j++){
      if(i == _isSelected[j]){
	std::cout<<"est selectionne : "<<_isSelected[j]<<std::endl;
	selected = true;
      }
    }

    if(selected){
      glColor3f(1.0, 0.0, 0.0);
    }
    else{
      glColor3f(_redComponent, _greenComponent, _blueComponent);
    }
    glBegin(GL_POLYGON);
    glVertex2f(_pointsVector[i][0]-increment, _pointsVector[i][1]-increment);
    glVertex2f(_pointsVector[i][0]-increment, _pointsVector[i][1]+increment);
    glVertex2f(_pointsVector[i][0]+increment, _pointsVector[i][1]+increment);
    glVertex2f(_pointsVector[i][0]+increment, _pointsVector[i][1]-increment);
    glEnd();
  }
}

std::vector<gml::Point3D> Polyline::discretize()
{
  std::vector<gml::Point3D> pointsList;
  pointsList.clear();

  return pointsList;
}

void Polyline::manageEvent(QMouseEvent* event,
			   unsigned short toolType,
			   unsigned short canvasType)
{
  gml::Point3D position;
  AbsCurve::calculateQtToOpenGL(event,&position);

  //mouse buttons management
  if(event->type() == QEvent::MouseButtonPress){
    
    if(event->button() == Qt::RightButton){

    }
    if(event->button() == Qt::LeftButton){
      addPoint(position);
    }
  }

  if(event->type() == QEvent::MouseButtonRelease){
    
  }
  
  if(event->type() == QEvent::MouseMove){

  }

  if(event->type() == QEvent::MouseButtonDblClick){
    close();
  }

  

}


