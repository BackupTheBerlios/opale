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

    if(isSelected(i)){
       glColor3f(_redComponentSelect,
		 _greenComponentSelect, 
		 _blueComponentSelect);
    }
    else{
      glColor3f(_redComponent, 
		_greenComponent, 
		_blueComponent);
    }

    glBegin(GL_POLYGON);
    glVertex2f(_pointsVector[i][0]-increment, _pointsVector[i][1]-increment);
    glVertex2f(_pointsVector[i][0]-increment, _pointsVector[i][1]+increment);
    glVertex2f(_pointsVector[i][0]+increment, _pointsVector[i][1]+increment);
    glVertex2f(_pointsVector[i][0]+increment, _pointsVector[i][1]-increment);
    glEnd();
  }
}


void Polyline::managePressEvent(QMouseEvent* event,
				unsigned short toolType,
				unsigned short canvasType)
{
  gml::Point3D position;
  calculateQtToOpenGL(event,&position);
  int index;
    
  /***************** creation mode **********************************/
  if(event->state() == Qt::ControlButton){
    addPoint(position);
    noSelection();
    select(isExistingPoint(position));
    _startMovePoint[0] = position[0];
    _startMovePoint[1] = position[1];
    }
  else{
    /***************** selection mode **********************************/
    //add to selection group with shift
    if(event->state() == Qt::ShiftButton){
      if(!isSelected(index)){
	  if((index=isExistingPoint(position)) != NO_EXIST){
	    select(index);
	  }
      }
      _startMovePoint[0] = position[0];
      _startMovePoint[1] = position[1];
    }
    
      else if(event->state() == Qt::Keypad){
	if((index=isExistingPoint(position)) != NO_EXIST){
	  deletePoint(index);
	}
      }
    
    //deselect and add without shift
    else{
      if((index=isExistingPoint(position)) != NO_EXIST){
	if(!isSelected(index)){
	  noSelection();
	    select(index);
	}
	_startMovePoint[0] = position[0];
	_startMovePoint[1] = position[1];
	
      }
	else{
	  noSelection();
	}
    }
  }
}





void Polyline::manageMoveEvent(QMouseEvent* event,
			       unsigned short toolType,
			       unsigned short canvasType)
{
  gml::Point3D position;
  calculateQtToOpenGL(event,&position);

  /***************** creation mode **********************************/
  if(event->state() == Qt::ControlButton){
  }
  /***************** selection mode **********************************/
  else{
    gml::Point3D newPos;
    for(unsigned i = 0; i<_pointsVector.size(); i++){
      if(isSelected((int)i)){
	newPos[0] = _pointsVector[i][0] 
	  + (position[0] - _startMovePoint[0]);
	newPos[1] = _pointsVector[i][1]
	  + (position[1] - _startMovePoint[1]);
	movePoint((int)i, newPos);
      }
    }
    _startMovePoint[0] = position[0];
    _startMovePoint[1] = position[1];
  }
}





void Polyline::manageReleaseEvent(QMouseEvent* event,
				  unsigned short toolType,
				  unsigned short canvasType)
{
  gml::Point3D position;
  calculateQtToOpenGL(event,&position);

  if(event->type() == QEvent::MouseButtonRelease){
    /***************** creation mode **********************************/
    if(event->state() == Qt::ControlButton){
      
    }
    /***************** selection mode **********************************/
    else{
      
    }
  } 
}




void Polyline::manageDbClickEvent(QMouseEvent* event,
				  unsigned short toolType,
				  unsigned short canvasType)
{
  gml::Point3D position;
  calculateQtToOpenGL(event,&position);

  /***************** creation mode **********************************/
  if(event->state() == Qt::ControlButton){
    addPoint(position);
    close();
    _startMovePoint[0] = position[0];
    _startMovePoint[1] = position[1];
  }
  /***************** selection mode **********************************/
  else{
    
  }
}

std::vector<gml::Point3D> Polyline::discretize()
{
  std::vector<gml::Point3D> pointsList;
  pointsList.clear();

  return pointsList;
}  
