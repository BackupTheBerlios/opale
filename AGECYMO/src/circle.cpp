#include "abscurve.hpp"
#include "circle.hpp"
#include <iostream>
#include "canvas2d.hpp"
#include <math.h>

using namespace std;

/*******************************************************
 * the default Circle constructor
 *
 ******************************************************/
Circle::Circle() {
}

/*******************************************************
 * the Circle destructor
 *
 ******************************************************/
Circle::~Circle() {
}

/*******************************************************
 * draw the circle in the openGL widget
 *
 ******************************************************/
void Circle::render(){

  double increment; 
  increment = Control_point_size / 2.0;
  
  glColor3f(_redColor, _greenColor, _blueColor);

  glBegin(GL_LINE_STRIP);
  for(int i = 0 ; i < int(_pointsVector.size()); i++){
    glVertex2f((float)(*_pointsVector[i])[0], (float)(*_pointsVector[i])[1]);
  }
  glEnd();

  if (getNbPoints() == 2) {
    glBegin(GL_LINE_LOOP);
   
    // Ray compute
    float x = pow((float)(*_pointsVector[1])[0] - 
		  (float)(*_pointsVector[0])[0],2);
    float y = pow((float)(*_pointsVector[1])[1] - 
		  (float)(*_pointsVector[0])[1],2);

    float r = sqrt(x + y);

    for ( int i = 0 ; i < 360 ; i++ ) {
      float angle = i * 3.14159F / 180 ;
      float x = (float) ((*_pointsVector[0])[0] + r*cos(angle)) ;
      float y = (float) ((*_pointsVector[0])[1] + r*sin(angle)) ;
      glVertex2f(x,y) ; 
    }
    
    glEnd() ;
  }

  glColor3f(_redColor, _greenColor, _blueColor);
  
}


/*******************************************************
 * discretize the circle
 * @param nbSegments the discretization resolution
 * @return the vector of points (the discretized polyline)
 *
 ******************************************************/
std::vector<gml::Point3D> Circle::discretize(int nbSegments)
{
  std::vector<gml::Point3D> pointsList;

  // Ray compute
  float xRay = pow((float)(*_pointsVector[1])[0] - 
		   (float)(*_pointsVector[0])[0],2);
  float yRay = pow((float)(*_pointsVector[1])[1] - 
		   (float)(*_pointsVector[0])[1],2);
  
  float r = sqrt(xRay + yRay);

  int step = 360/nbSegments;
  
  for ( int i = 0 ; i < 360 ; i=i+step ) {
    float angle = i * 3.14159F / 180 ;
    float x = (float) ((*_pointsVector[0])[0] + r*cos(angle)) ;
    float y = (float) ((*_pointsVector[0])[1] + r*sin(angle)) ;
    Point3D p;
    p[0] = x;
    p[1] = y;
    p[2] = 0.0;
    pointsList.push_back(p);
  }

  return pointsList;
}  

/*******************************************************
 * add a point to the polyline
 * @param point the point to add
 * @return ADDED or NOT_ADDED
 *
 ******************************************************/
int Circle::addPoint(gml::Point3D *point)
{
  if (_pointsVector.size() <= 1) {
    _pointsVector.push_back(point);
    return ADDED;
  }
  else {
    return NOT_ADDED;
  }
}
