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
				     3, 12, 1,
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
    for ( int i = 0 ; i < 360 ; i++) {
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
  std::vector<gml::Point3D> pointsPoly;


  // Polygone
  if (getNbPoints() == 2) {
    
    
    // Ray compute
    float x = pow((float)(*_pointsVector[1])[0] - (float)(*_pointsVector[0])[0],2);
    float y = pow((float)(*_pointsVector[1])[1] - (float)(*_pointsVector[0])[1],2);
    
    float r = sqrt(x + y);
    

    for ( int i = 0 ; i < 360 ; i ++) {
      float angle = (float)i * 3.14159F / ((float)_nbPoints/2.0) ;
      float x = (float) ((*_pointsVector[0])[0] + r*cos(angle)) ;
      float y = (float) ((*_pointsVector[0])[1] + r*sin(angle)) ;
      Point3D p;
      p[0] = x;
      p[1] = y;
      p[2] = 0.0;
      pointsPoly.push_back(p) ;
    }

    for (int i=0; i<_nbPoints ; i++) {
      pointsList.push_back(pointsPoly[i]);
      float diffx = fabs(pointsPoly[i][0] - pointsPoly[i+1][0]);
      float diffy = fabs(pointsPoly[i][1] - pointsPoly[i+1][1]);
      int nbPointsSegment = nbSegments/_nbPoints;
      for (int j=1; j<nbPointsSegment;j++) {
	if (pointsPoly[i][0] < pointsPoly[i+1][0] && pointsPoly[i][1] < pointsPoly[i+1][1]) {
	   Point3D p;
	   p[0] = pointsPoly[i][0] + (diffx*(j/((float)nbSegments/(float)_nbPoints)));
	   p[1] = pointsPoly[i][1] + (diffy*(j/((float)nbSegments/(float)_nbPoints)));
	   p[2] = 0.0;
	   pointsList.push_back(p);
	}
	else {
	  if (pointsPoly[i][0] > pointsPoly[i+1][0] && pointsPoly[i][1] < pointsPoly[i+1][1]) {
	    Point3D p;
	    p[0] = pointsPoly[i][0] - (diffx*(j/(float)(nbSegments/(float)_nbPoints)));
	    p[1] = pointsPoly[i][1] + (diffy*(j/(float)(nbSegments/(float)_nbPoints)));
	    p[2] = 0.0;
	    pointsList.push_back(p);
	  }
	  else {
	    if (pointsPoly[i][0] > pointsPoly[i+1][0] && pointsPoly[i][1] > pointsPoly[i+1][1]) {
	      Point3D p;
	      p[0] = pointsPoly[i][0] - (diffx*(j/(float)(nbSegments/(float)_nbPoints)));
	      p[1] = pointsPoly[i][1] - (diffy*(j/(float)(nbSegments/(float)_nbPoints)));
	      p[2] = 0.0;
	      pointsList.push_back(p);
	    }
	    else {
	      Point3D p;
	      p[0] = pointsPoly[i][0] + (diffx*(j/(float)(nbSegments/(float)_nbPoints)));
	      p[1] = pointsPoly[i][1] - (diffy*(j/(float)(nbSegments/(float)_nbPoints)));
	      p[2] = 0.0;
	      pointsList.push_back(p);
	    }
	  }
	}
	//cout << "x= " << pointsList[i][0] << " y= " << pointsList[i][1] << endl;
      }
    }

  }

  /*for (int i=0; i<pointsList.size();i++) {
    cout << "x= " << pointsList[i][0] << " y= " << pointsList[i][1] << endl;
    }*/
  
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

