#include "abscurve.hpp"
#include "circle.hpp"
#include <iostream>
#include "canvas2d.hpp"
#include <math.h>

using namespace std;

Circle::Circle(Canvas2D *parent)
  :
  AbsCurve(parent)
{}

Circle::Circle(std::vector<gml::Point3D> pointsVector, 
		   bool isClosed,
		   Canvas2D *parent)
  :
  AbsCurve(pointsVector, isClosed, parent)
{}

Circle::Circle(const Circle &source)
  :
  AbsCurve(source)
{
}

void Circle::render(){

  double increment; 
  increment = Control_point_size / 2.0;
  
  glColor3f(_redComponent, _greenComponent, _blueComponent);

  glBegin(GL_LINE_STRIP);

  for(int i = 0 ; i < int(_pointsVector.size()); i++){
    glVertex2f(_pointsVector[i][0], _pointsVector[i][1]);
  }

  glEnd();

  // Circle
  if (getNbPoints() == 2) {
    glBegin(GL_LINE_LOOP);
   
    // Ray compute
    float x = pow((float)_pointsVector[1][0] - (float)_pointsVector[0][0],2);
    float y = pow((float)_pointsVector[1][1] - (float)_pointsVector[0][1],2);

    //cout << "x = " << x << endl;

    float r = sqrt(x + y);

    for ( int i = 0 ; i < 360 ; i++ ) {
      float angle = i * 3.14159F / 180 ;
      float x = (float) (_pointsVector[0][0] + r*cos(angle)) ;
      float y = (float) (_pointsVector[0][1] + r*sin(angle)) ;
      glVertex2f(x,y) ; 
    }
    
    glEnd() ;
  }

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


void Circle::managePressEvent(QMouseEvent* event,
			      unsigned short toolType,
			      unsigned short canvasType)
{
  gml::Point3D position;
  calculateQtToOpenGL(event,&position);
  int index;
      
  /***************** creation mode **********************************/
  if(event->state() == Qt::ControlButton){

    if (getNbPoints() == 0) {

      // Center creation
      cout << "Creation centre" << endl;
      addPoint(position);

      // Current point selection
      noSelection();
      select(isExistingPoint(position));
      
      _startMovePoint[0] = position[0];
      _startMovePoint[1] = position[1];
    }
    else {
      if (getNbPoints() == 1) {
	// Center creation
	cout << "Creation rayon" << endl;
	addPoint(position);
	
	// Current point selection
	noSelection();
	select(isExistingPoint(position));
	
	_startMovePoint[0] = position[0];
	_startMovePoint[1] = position[1];
	
      }
    }
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





void Circle::manageMoveEvent(QMouseEvent* event,
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





void Circle::manageReleaseEvent(QMouseEvent* event,
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




void Circle::manageDbClickEvent(QMouseEvent* event,
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

std::vector<gml::Point3D> Circle::discretize()
{
  std::vector<gml::Point3D> pointsList;
  pointsList.clear();

  return pointsList;
}  
