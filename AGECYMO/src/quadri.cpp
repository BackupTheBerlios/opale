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
  std::vector<gml::Point3D> fourPoints;

  float diffx = fabs((*_pointsVector[0])[0] - (*_pointsVector[1])[0]);
  float diffy = fabs((*_pointsVector[0])[1] - (*_pointsVector[1])[1]);

  fourPoints.push_back((*_pointsVector[1]));
  listPoints.push_back(fourPoints[0]);

  float perim = 8 * diffx + 8 * diffy;
  
  Point3D p;

  for (double i=perim/(float)nbSegments; i<2*diffy ; i += perim/(float)nbSegments) {
    p[0] = fourPoints[0][0];
    p[1] = fourPoints[0][1] + i;
    p[2] = 0.0;
    listPoints.push_back(p);
  }

  p[0] = fourPoints[0][0];
  p[1] = fourPoints[0][1] + 2*diffy;
  p[2] = 0.0;
  fourPoints.push_back(p);
  listPoints.push_back(fourPoints[1]);

  for (double i=perim/(float)nbSegments; i<2*diffx ; i += perim/(float)nbSegments) {
    p[0] = fourPoints[1][0] - i;
    p[1] = fourPoints[1][1];
    p[2] = 0.0;
    listPoints.push_back(p);
  }

  p[0] = fourPoints[1][0] - 2*diffx;
  p[1] = fourPoints[1][1];
  p[2] = 0.0;
  fourPoints.push_back(p);
  listPoints.push_back(fourPoints[2]);

  for (double i=perim/(float)nbSegments; i<2*diffy ; i += perim/(float)nbSegments) {
    p[0] = fourPoints[2][0];
    p[1] = fourPoints[2][1] - i;
    p[2] = 0.0;
    listPoints.push_back(p);
  }

  p[0] = fourPoints[2][0];
  p[1] = fourPoints[2][1] - 2*diffy;
  p[2] = 0.0;
  fourPoints.push_back(p);
  listPoints.push_back(fourPoints[3]);

  for (double i=perim/(float)nbSegments; i<2*diffx ; i += perim/(float)nbSegments) {
    p[0] = fourPoints[3][0] + i;
    p[1] = fourPoints[3][1];
    p[2] = 0.0;
    listPoints.push_back(p);
  }

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


