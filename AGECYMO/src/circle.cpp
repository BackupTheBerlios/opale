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
 * @param nbDiscretizedPoints the number of discretized points.
 * @return the vector of points (the discretized polyline)
 *
 ******************************************************/
std::vector<gml::Point3D> Circle::discretize(int nbDiscretizedPoints)
{
  std::vector<gml::Point3D> pointsList;

  gml::Vector3D ray = *(_pointsVector[1]) - *(_pointsVector[0]);

  const double rayon = ray.norm();
  const double TWO_PI = 2 * M_PI;
  
  double deltaT = 1.0 / nbDiscretizedPoints;

  std::cout << deltaT << std::endl;
  
  for (double t=0.0; t < (1-gml::EPSILON); t += deltaT)
  {
    Point3D p;
    p[0] = rayon * cos( TWO_PI * t);
    p[1] = rayon * sin( TWO_PI * t);
    p[2] = 0;
    std::cout << "Discretization Circle Point p = " << p << std::endl;
    p.stabilize();
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

/**************************************************************
 *
 *  get the number of segment of the curve
 *  @return the number of segments
 *
 *************************************************************/
int Circle::getNumberOfSegments()
{
  return 1;
}
