#include "abscurve.hpp"
#include "quadri.hpp"
#include <iostream>
#include "canvas2d.hpp"
#include <math.h>

using namespace std;

Quadri::Quadri() {
}

Quadri::~Quadri() {
}

void Quadri::render(){

  double increment; 
  increment = Control_point_size / 2.0;
  
  glColor3f(_redColor, _greenColor, _blueColor);

  glBegin(GL_LINE_STRIP);

  for(int i = 0 ; i < int(_pointsVector.size()); i++){
    glVertex2f((*_pointsVector[i])[0], (*_pointsVector[i])[1]);
  }

  glEnd();

  // Quadri
  if (getNbPoints() == 2) {
    glBegin(GL_LINE_STRIP);
   
    float diffx = (*_pointsVector[0])[0] - (*_pointsVector[1])[0];
    float diffy = (*_pointsVector[0])[1] - (*_pointsVector[1])[1];

    glVertex2f((*_pointsVector[0])[0], (*_pointsVector[0])[1]);

    glVertex2f((*_pointsVector[1])[0], (*_pointsVector[1])[1]);

    glVertex2f((*_pointsVector[1])[0], (*_pointsVector[1])[1] + 2 * diffy);

    glVertex2f((*_pointsVector[1])[0] + 2 * diffx, (*_pointsVector[1])[1] + 2 * diffy);

    glVertex2f((*_pointsVector[1])[0] + 2 * diffx, (*_pointsVector[1])[1]);  

    glVertex2f((*_pointsVector[1])[0], (*_pointsVector[1])[1]);
    
    glEnd() ;
  }
}

std::vector<gml::Point3D> Quadri::discretize(int nbSegments)
{
  std::vector<gml::Point3D> listPoints;

  float diffx = (*_pointsVector[0])[0] - (*_pointsVector[1])[0];
  float diffy = (*_pointsVector[0])[1] - (*_pointsVector[1])[1];

  listPoints.push_back((*_pointsVector[1]));
  
  Point3D p;
  
  p[0] = (*_pointsVector[1])[0];
  p[1] = (*_pointsVector[1])[1]+ 2 * diffy;
  p[2] = 0.0;

  listPoints.push_back(p);

  p[0] = (*_pointsVector[1])[0] + 2 * diffx;
  p[1] = (*_pointsVector[1])[1] + 2 * diffy;
  p[2] = 0.0;

  listPoints.push_back(p);

  p[0] = (*_pointsVector[1])[0] + 2 * diffx;
  p[1] = (*_pointsVector[1])[1];
  p[2] = 0.0;

  listPoints.push_back(p);

  return listPoints;
}  

int Quadri::addPoint(gml::Point3D *point)
{

  if (_pointsVector.size() <= 1) {
    _pointsVector.push_back(point);
    return ADDED;
  }
  else {
    return NOT_ADDED;
  }
}


