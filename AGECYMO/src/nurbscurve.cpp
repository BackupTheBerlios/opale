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

NurbsCurve::NurbsCurve() {

  _nbPointsDefine = 4;

  _red_nurb = RED_NURB;
  _green_nurb = GREEN_NURB;
  _blue_nurb = BLUE_NURB;
}
 
NurbsCurve::~NurbsCurve() {
}

void NurbsCurve::render(){

  double increment; 
  increment = Control_point_size / 2.0;
  
  glColor3f(_redColor, _greenColor, _blueColor);

  glBegin(GL_LINE_STRIP);

  for(int i = 0 ; i < int(_pointsVector.size()); i++){
    glVertex2f((*_pointsVector[i])[0], (*_pointsVector[i])[1]);
  }

  glEnd();

  
   
  // If the number of points it's enough to define the curve
  if (getNbPoints() >= _nbPointsDefine) {
  
    // New table in order to get the points
    Vector_HPoint3Df ctrlpoints(getNbPoints());
  
    // Construction of this new table
    for (int i=0; i < getNbPoints() ;i++) {
      ctrlpoints[i] = PLib::HPoint3Df((*_pointsVector[i])[0],(*_pointsVector[i])[1] ,0 ,_HCoordinateVector[i]);
    }
  
    // New color
    glColor3f(_red_nurb, _green_nurb, _blue_nurb);

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
      float ponderateX;
      float ponderateY;
      if (p.x() >= 0) {
	ponderateX = p.x()*p.w();
      }
      else {
	ponderateX = p.x()/p.w();
      }
      if (p.x() >= 0) {
	ponderateY = p.y()*p.w();
      }
      else {
	ponderateY = p.y()/p.w();
      }
      glVertex2f(ponderateX, ponderateY);
    }
    glEnd();

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
    ctrlpoints[i] = PLib::HPoint3Df((*_pointsVector[i])[0],(*_pointsVector[i])[1] ,0 ,1);
  }
  
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
    p3D[0] = p.x() / p.w();
    p3D[1] = p.y() / p.w();
    p3D[2] = p.z() / p.w();
    pointsList.push_back(p3D);
  }
  glEnd();
  
  return pointsList;
}

int NurbsCurve::addPoint(gml::Point3D *point)
{
  _pointsVector.push_back(point);
  _HCoordinateVector.push_back(1.0);
  return ADDED;
}

