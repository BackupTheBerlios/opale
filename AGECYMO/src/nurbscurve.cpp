#include "abscurve.hpp"
#include "nurbscurve.hpp"
#include <iostream>
#include <vector>
#include "canvas2d.hpp"
#include <math.h>
#include <qmessagebox.h> 
#include <qinputdialog.h> 
#include "nurbs.h"
#include "hpoint_nd.h"


using namespace std;

NurbsCurve::NurbsCurve(Canvas2D *parent)
  :
  AbsCurve(parent)
{

      _nbPointsDefine = 4;
  
}

NurbsCurve::NurbsCurve(std::vector<gml::Point3D> pointsVector, 
		       bool isClosed,
		       Canvas2D *parent)
  :
  AbsCurve(pointsVector, isClosed, parent)
{}



NurbsCurve::NurbsCurve(const NurbsCurve &source)
  :
  AbsCurve(source)
{
}



void NurbsCurve::render(){

  double increment; 
  increment = Control_point_size / 2.0;
  
  glColor3f(_redComponent, _greenComponent, _blueComponent);

  glBegin(GL_LINE_STRIP);

  for(int i = 0 ; i < int(_pointsVector.size()); i++){
    glVertex2f(_pointsVector[i][0], _pointsVector[i][1]);
  }

  glEnd();

  
   
  // If the number of points it's enough to define the curve
  if (getNbPoints() >= _nbPointsDefine) {
  
    // New table in order to get the points
    Vector_HPoint3Df ctrlpoints(getNbPoints());
  
    // Construction of this new table
    for (int i=0; i < getNbPoints() ;i++) {
      ctrlpoints[i] = PLib::HPoint3Df(_pointsVector[i][0],_pointsVector[i][1] ,0 ,1);
    }
  
    // New color
    glColor3f(0,1,0.5);

    // Knots contruction 
    int nknots = getNbPoints() + _nbPointsDefine;
    PlVector_float knots(nknots);
    for (int i=_nbPointsDefine; i<nknots-_nbPointsDefine; i++) {
      
      knots[i] = (float)i-_nbPointsDefine + 1;
    }

    knots[0] = 0;
    knots[1] = 0;
    knots[2] = 0;
    knots[3] = 0;
    knots[nknots-1] = nknots-2*_nbPointsDefine+1;
    knots[nknots-2] = nknots-2*_nbPointsDefine+1;
    knots[nknots-3] = nknots-2*_nbPointsDefine+1;
    knots[nknots-4] = nknots-2*_nbPointsDefine+1;

    

    PLib::NurbsCurvef curve(ctrlpoints, knots, _nbPointsDefine-1);
    
    glBegin(GL_LINE_STRIP);
    for (float i=0;i<=getNbPoints()-_nbPointsDefine+1;i=i+0.01) {
      PLib::HPoint3Df p = curve(i);  
      glVertex2f(p.x(), p.y());
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


void NurbsCurve::managePressEvent(QMouseEvent* event,
			      unsigned short toolType,
			      unsigned short canvasType)
{
  gml::Point3D position;
  calculateQtToOpenGL(event,&position);
  int index;
      
  /***************** creation mode **********************************/
  if(event->state() == Qt::ControlButton){

      addPoint(position);

      // Management of the homogeneous coordinate
      _HCoordinateVector.push_back(1);

      // Current point selection
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

	  // Management of the weight
	  cout << "coin" << endl;

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





void NurbsCurve::manageMoveEvent(QMouseEvent* event,
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





void NurbsCurve::manageReleaseEvent(QMouseEvent* event,
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




void NurbsCurve::manageDbClickEvent(QMouseEvent* event,
				unsigned short toolType,
				unsigned short canvasType)
{

  gml::Point3D position;
  calculateQtToOpenGL(event,&position);
  int index;

  if((index=isExistingPoint(position)) != NO_EXIST){
    if(!isSelected(index)){
      noSelection();
      select(index);
      
      // Management of the weight
      cout << "coin2" << endl;
      
    }
    _startMovePoint[0] = position[0];
    _startMovePoint[1] = position[1];
    
  }

}

std::vector<gml::Point3D> NurbsCurve::discretize(int nbSegments)
{
  std::vector<gml::Point3D> pointsList;
  gml::Point3D p3D;
  
  // New table in order to get the points
  Vector_HPoint3Df ctrlpoints(getNbPoints());
  
  // Construction of this new table
  for (int i=0; i < getNbPoints() ;i++) {
    ctrlpoints[i] = PLib::HPoint3Df(_pointsVector[i][0],_pointsVector[i][1] ,0 ,1);
  }
  
  // New color
  glColor3f(0,1,0.5);
  
  // Knots contruction 
  int nknots = getNbPoints() + _nbPointsDefine;
  PlVector_float knots(nknots);
  for (int i=_nbPointsDefine; i<nknots-_nbPointsDefine; i++) {
    knots[i] = (float)i-_nbPointsDefine + 1;
  }
  
  knots[0] = 0;
  knots[1] = 0;
  knots[2] = 0;
  knots[3] = 0;
  knots[nknots-1] = nknots-2*_nbPointsDefine+1;
  knots[nknots-2] = nknots-2*_nbPointsDefine+1;
  knots[nknots-3] = nknots-2*_nbPointsDefine+1;
  knots[nknots-4] = nknots-2*_nbPointsDefine+1;
  
  PLib::NurbsCurvef curve(ctrlpoints, knots, _nbPointsDefine-1);
  
  glBegin(GL_LINE_STRIP);
  for (float i=0;i<=getNbPoints()-_nbPointsDefine+1;i=i+0.01) {
    PLib::HPoint3Df p = curve(i);  
    p3D[0] = p.x();
    p3D[0] = p.y();
    p3D[0] = p.z();
    pointsList.push_back(p3D);
  }
  glEnd();
  
  return pointsList;
}



