#include "abscurve.hpp"
#include "nurbscurve.hpp"
#include <iostream>
#include "canvas2d.hpp"
#include <math.h>
#include <qmessagebox.h> 
#include <qinputdialog.h> 

using namespace std;

NurbsCurve::NurbsCurve(Canvas2D *parent)
  :
  AbsCurve(parent)
{

  bool ok;
  int res = QInputDialog::getInteger("General cylinder", 
				     "Enter the number of points you want to use in order to define the curve :",
				     4, 3, 10, 1,
				     &ok, parent );
  if ( ok ) {
  
    nbPointsDefine = res;
  
  } 

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
  if (getNbPoints() >= nbPointsDefine) {
  
    // New table in order to get the points
    GLfloat ctrlpoints[getNbPoints()][4];
  
    // Construction of this new table
    for (int i=0; i < getNbPoints() ;i++) {
      ctrlpoints[i][0] = _pointsVector[i][0];
      ctrlpoints[i][1] = _pointsVector[i][1];
      ctrlpoints[i][2] = 0.0;
      ctrlpoints[i][3] = 1.0;
    }
  
    //glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, nbPointsDefine, &ctrlpoints[0][0]);
    //glEnable(GL_MAP1_VERTEX_3);
    /*glBegin(GL_LINE_STRIP);
    for(int i = 0 ; i <= 30 ; i++ ) {
      
      glEvalCoord1f((GLfloat) i/30.0);
    }
    glEnd() ;*/

    // New color
    glColor3f(0,1,1);

    // Nurb object construction
    GLUnurbsObj* nobj = gluNewNurbsRenderer();

    // Knots contruction 
    int nknots = getNbPoints() + nbPointsDefine;
    GLfloat knots[nknots];
    for (int i=0; i<nknots; i++) {
      knots[i] = (float)i;
    }

    gluBeginCurve(nobj);
    //gluNurbsCurve(nobj, nknots, knots, 3, &ctrlpoints[0][0], nbPointsDefine, GL_MAP1_TEXTURE_COORD_2);
    //gluNurbsCurve(nobj, nknots, knots, 3, &ctrlpoints[0][0], nbPointsDefine, GL_MAP1_NORMAL);
    gluNurbsCurve(nobj, nknots, knots, 4, &ctrlpoints[0][0], nbPointsDefine, GL_MAP1_VERTEX_4);
    gluEndCurve(nobj);
    
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

std::vector<gml::Point3D> NurbsCurve::discretize(int nbSegments)
{
  std::vector<gml::Point3D> pointsList;
  pointsList.clear();

  return pointsList;
}  
