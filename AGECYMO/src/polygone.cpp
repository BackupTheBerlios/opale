#include "abscurve.hpp"
#include "polygone.hpp"
#include <iostream>
#include "canvas2d.hpp"
#include <math.h>
#include <qmessagebox.h> 
#include <qinputdialog.h> 

using namespace std;

Polygone::Polygone(Canvas2D *parent)
  :
  AbsCurve(parent)
{

  bool ok;
  
  
    
  int res = QInputDialog::getInteger("Another Modeler", "Number of points:", 3, 
				     3, 360, 1,
				     &ok, parent);
    if ( ok ) {
      _nbPoints=res;
    } 
    else {
      _nbPoints=3;
    }


}

Polygone::Polygone(std::vector<gml::Point3D> pointsVector, 
		   bool isClosed,
		   Canvas2D *parent)
  :
  AbsCurve(pointsVector, isClosed, parent)
{}

Polygone::Polygone(const Polygone &source)
  :
  AbsCurve(source)
{
}

void Polygone::render(){

  double increment; 
  increment = Control_point_size / 2.0;
  
  glColor3f(_redComponent, _greenComponent, _blueComponent);

  glBegin(GL_LINE_STRIP);

  for(int i = 0 ; i < int(_pointsVector.size()); i++){
    glVertex2f(_pointsVector[i][0], _pointsVector[i][1]);
  }

  glEnd();

  // Polygone
  if (getNbPoints() == 2) {


    // Ray compute
    float x = pow((float)_pointsVector[1][0] - (float)_pointsVector[0][0],2);
    float y = pow((float)_pointsVector[1][1] - (float)_pointsVector[0][1],2);

    float r = sqrt(x + y);

    glBegin(GL_LINE_STRIP);
    for ( int i = 0 ; i < 360 ; i++ ) {
      float angle = (float)i * 3.14159F / ((float)_nbPoints/2.0) ;
      float x = (float) (_pointsVector[0][0] + r*cos(angle)) ;
      float y = (float) (_pointsVector[0][1] + r*sin(angle)) ;
      //float distx = pow(x - (float)_pointsVector[0][0],2);
      //float disty = pow(y - (float)_pointsVector[0][1],2);
      //float distr = sqrt(distx + disty);
      //if (r == distr) {
	glVertex2f(x,y) ;
	//} 
    }
    glEnd();

    
    glColor3f(0.25, 0.25, 0.25);

    glBegin(GL_POLYGON);
    for ( int i = 0 ; i < 360 ; i++ ) {
      float angle = i * 3.14159F / 180.0 ;
      float x = (float) (_pointsVector[0][0] + r*cos(angle)) ;
      float y = (float) (_pointsVector[0][1] + r*sin(angle)) ;
      glVertex2f(x,y); 
    }
    glEnd();
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


void Polygone::managePressEvent(QMouseEvent* event,
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





void Polygone::manageMoveEvent(QMouseEvent* event,
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

	// In case of the first point is selected alone
	if (i==0 && !isSelected(1)){
	  newPos[0] = _pointsVector[1][0] 
	    + (position[0] - _startMovePoint[0]);
	  newPos[1] = _pointsVector[1][1]
	    + (position[1] - _startMovePoint[1]);
	  movePoint(1, newPos);
	}
	  

      }
    }
    _startMovePoint[0] = position[0];
    _startMovePoint[1] = position[1];
  }
}





void Polygone::manageReleaseEvent(QMouseEvent* event,
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




void Polygone::manageDbClickEvent(QMouseEvent* event,
				unsigned short toolType,
				unsigned short canvasType)
{
  
}

std::vector<gml::Point3D> Polygone::discretize(int nbSegments)
{
  std::vector<gml::Point3D> pointsList;

  // Ray compute
  float xRay = pow((float)_pointsVector[1][0] - (float)_pointsVector[0][0],2);
  float yRay = pow((float)_pointsVector[1][1] - (float)_pointsVector[0][1],2);
  
  //cout << "x = " << x << endl;
  
  float r = sqrt(xRay + yRay);

  int step = 360/nbSegments;
  
  for ( int i = 0 ; i < 360 ; i=i+step ) {
    float angle = i * 3.14159F / 180 ;
    float x = (float) (_pointsVector[0][0] + r*cos(angle)) ;
    float y = (float) (_pointsVector[0][1] + r*sin(angle)) ;
    Point3D p;
    p[0] = x;
    p[1] = y;
    p[2] = 0.0;
    pointsList.push_back(p);
  }

  // In order to manage the last point of the revolution
  /*float angle = 360 * 3.14159F / 180 ;
  float xLastPoint = (float)(_pointsVector[0][0] + r*cos(angle)) ;
  float yLastPoint = (float)(_pointsVector[0][1] + r*sin(angle)) ;
  Point3D p;
  p[0] = xLastPoint;
  p[1] = yLastPoint;
  p[2] = 0.0;
  pointsList.push_back(p);*/

  float angle = 0 * 3.14159F / 180 ;
  float xLastPoint = (float)(_pointsVector[0][0] + r*cos(angle)) ;
  float yLastPoint = (float)(_pointsVector[0][1] + r*sin(angle)) ;
  Point3D p;
  p[0] = xLastPoint;
  p[1] = yLastPoint;
  p[2] = 0.0;
  pointsList.push_back(p);
  
  return pointsList;
}  
