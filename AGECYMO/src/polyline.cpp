#include "abscurve.hpp"
#include "polyline.hpp"
#include <iostream>
#include "canvas2d.hpp"

using namespace std;

/*******************************************************
 * the default polyline constructor
 *
 ******************************************************/
Polyline::Polyline()
{}

/*******************************************************
 * the polyline destructor
 *
 ******************************************************/
Polyline::~Polyline()
{}

/*******************************************************
 * draw the polyline in the openGL widget
 *
 ******************************************************/
void Polyline::render()
{
  glColor3f(_redColor, _greenColor, _blueColor);
  glBegin(GL_LINE_STRIP);
  for(int i = 0 ; i < int(_pointsVector.size()); i++){
    glVertex2f((*_pointsVector[i])[0], (*_pointsVector[i])[1]);
  }
  glEnd();
}

/*******************************************************
 * add a point to the polyline
 * @param point the point to add
 * @return ADDED or NOT_ADDED
 *
 ******************************************************/
std::vector<gml::Point3D> Polyline::discretize(int nbSegments)
{
  std::vector<gml::Point3D> pointsList;
  gml::Point3D vec;
  gml::Point3D point;
  double tmpx, tmpy;
  double increment, coeff;
  
  //the first point
  point[0] = (*_pointsVector[0])[0];
  point[1] = (*_pointsVector[0])[1];
  pointsList.push_back(point);

  nbSegments = nbSegments-1;
  increment = 1.0/(double)nbSegments;
  
  for(unsigned i = 0 ; i<_pointsVector.size()-1; i++){

    //vector construction
    vec[0] = (*_pointsVector[i+1])[0] - (*_pointsVector[i])[0];
    vec[1] = (*_pointsVector[i+1])[1] - (*_pointsVector[i])[1];

    coeff = increment;

    for(int j = 1 ; j<=nbSegments ; j++){
      point[0] = vec[0] * coeff;
      point[1] = vec[1] * coeff;
      point[0] += (*_pointsVector[i])[0];
      point[1] += (*_pointsVector[i])[1];
      pointsList.push_back(point);
      coeff += increment;
    }
  }

  return pointsList;
}


 /*******************************************************
  * discretize the polyline
  * @param nbSegments the discretization resolution
  * @return the vector of points (the discretized polyline)
  *
  ******************************************************/
int Polyline::addPoint(gml::Point3D *point)
{
  cout<<"point ajoute dans addPoint"<<endl;
  _pointsVector.push_back(point);
  return ADDED;
}
