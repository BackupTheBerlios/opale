#include "abscurve.hpp"
#include "quadri.hpp"
#include <iostream>
#include "canvas2d.hpp"
#include <math.h>

using namespace std;

Quadri::Quadri(Canvas2D *parent)
  :
  AbsCurve(parent)
{}

Quadri::Quadri(std::vector<gml::Point3D> pointsVector, 
		   bool isClosed,
		   Canvas2D *parent)
  :
  AbsCurve(pointsVector, isClosed, parent)
{}

Quadri::Quadri(const Quadri &source)
  :
  AbsCurve(source)
{
}

void Quadri::render(){

  double increment; 
  increment = Control_point_size / 2.0;
  
  glColor3f(_redComponent, _greenComponent, _blueComponent);

  glBegin(GL_LINE_STRIP);

  for(int i = 0 ; i < int(_pointsVector.size()); i++){
    glVertex2f(_pointsVector[i][0], _pointsVector[i][1]);
  }

  glEnd();

  // Quadri
  if (getNbPoints() == 2) {
    glBegin(GL_LINE_STRIP);
   
    float diffx = _pointsVector[0][0] - _pointsVector[1][0];
    float diffy = _pointsVector[0][1] - _pointsVector[1][1];

    glVertex2f(_pointsVector[0][0], _pointsVector[0][1]);

    glVertex2f(_pointsVector[1][0], _pointsVector[1][1]);

    glVertex2f(_pointsVector[1][0], _pointsVector[1][1] + 2 * diffy);

    glVertex2f(_pointsVector[1][0] + 2 * diffx, _pointsVector[1][1] + 2 * diffy);

    glVertex2f(_pointsVector[1][0] + 2 * diffx, _pointsVector[1][1]);  

    glVertex2f(_pointsVector[1][0], _pointsVector[1][1]);
    
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


void Quadri::managePressEvent(QMouseEvent* event,
			      unsigned short toolType,
			      unsigned short canvasType)
{
  gml::Point3D position;
  calculateQtToOpenGL(event,&position);
  int index;
      
  /***************** creation mode **********************************/
  if(event->state() == Qt::ControlButton){

    if (getNbPoints() == 0) {

      // First point creation
      cout << "First" << endl;
      addPoint(position);

      // Current point selection
      noSelection();
      select(isExistingPoint(position));
      
      _startMovePoint[0] = position[0];
      _startMovePoint[1] = position[1];
    }
    else {
      if (getNbPoints() == 1) {
	// Last creation
	cout << "Last" << endl;
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





void Quadri::manageMoveEvent(QMouseEvent* event,
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





void Quadri::manageReleaseEvent(QMouseEvent* event,
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




void Quadri::manageDbClickEvent(QMouseEvent* event,
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

std::vector<gml::Point3D> Quadri::discretize()
{
  std::vector<gml::Point3D> pointsList;
  pointsList.clear();

  return pointsList;
}  
