#include "abscurve.hpp"
#include "polygone.hpp"
#include <iostream>
#include "canvas2d.hpp"
#include <math.h>
#include <qmessagebox.h> 
#include <qinputdialog.h> 

using namespace std;

Polygone::Polygone(Canvas2D *parent) {

  bool ok;

  _parent = parent;
  
  int res = QInputDialog::getInteger("Another Modeler", "Number of points:", 3, 
				     3, 360, 1,
				     &ok, _parent);
  if ( ok ) {
    _nbPoints=res;
  } 
  else {
    _nbPoints=3;
  }

  _red_circle = RED_CIRCLE;
  _green_circle = GREEN_CIRCLE;
  _blue_circle = BLUE_CIRCLE;

}

Polygone::~Polygone() {
} 
 
 
void Polygone::render(){

  double increment; 
  increment = Control_point_size / 2.0;
  
  glColor3f(_redColor, _greenColor, _blueColor);

  glBegin(GL_LINE_STRIP);

  for(int i = 0 ; i < int(_pointsVector.size()); i++){
    glVertex2f((*_pointsVector[i])[0], (*_pointsVector[i])[1]);
  }

  glEnd();

  // Polygone
  if (getNbPoints() == 2) {


    // Ray compute
    float x = pow((float)(*_pointsVector[1])[0] - (float)(*_pointsVector[0])[0],2);
    float y = pow((float)(*_pointsVector[1])[1] - (float)(*_pointsVector[0])[1],2);

    float r = sqrt(x + y);
    
    glBegin(GL_LINE_STRIP);
    for ( int i = 0 ; i < 360 ; i++ ) {
      float angle = (float)i * 3.14159F / ((float)_nbPoints/2.0) ;
      float x = (float) ((*_pointsVector[0])[0] + r*cos(angle)) ;
      float y = (float) ((*_pointsVector[0])[1] + r*sin(angle)) ;
      glVertex2f(x,y) ;
    }
    glEnd();
    
    
    glColor3f(_red_circle, _green_circle, _blue_circle);
    
    glBegin(GL_POLYGON);
    for ( int i = 0 ; i < 360 ; i++ ) {
      float angle = i * 3.14159F / 180.0 ;
      float x = (float) ((*_pointsVector[0])[0] + r*cos(angle)) ;
      float y = (float) ((*_pointsVector[0])[1] + r*sin(angle)) ;
      glVertex2f(x,y); 
    }
    glEnd();
  }
}

  
std::vector<gml::Point3D> Polygone::discretize(int nbSegments)
{
  std::vector<gml::Point3D> pointsList;

  /*// Ray compute
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
  float angle = 360 * 3.14159F / 180 ;
  float xLastPoint = (float)(_pointsVector[0][0] + r*cos(angle)) ;
  float yLastPoint = (float)(_pointsVector[0][1] + r*sin(angle)) ;
  Point3D p;
  p[0] = xLastPoint;
  p[1] = yLastPoint;
  p[2] = 0.0;
  pointsList.push_back(p);

  float angle = 0 * 3.14159F / 180 ;
  float xLastPoint = (float)(_pointsVector[0][0] + r*cos(angle)) ;
  float yLastPoint = (float)(_pointsVector[0][1] + r*sin(angle)) ;
  Point3D p;
  p[0] = xLastPoint;
  p[1] = yLastPoint;
  p[2] = 0.0;
  pointsList.push_back(p);
  */
  return pointsList;
}

 int Polygone::addPoint(gml::Point3D *point)
{

  if (_pointsVector.size() <= 1) {
    _pointsVector.push_back(point);
    return ADDED;
  }
  else {
    return NOT_ADDED;
  }
}

