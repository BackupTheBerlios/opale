#include "abscurve.hpp"
#include "polygone.hpp"
#include <iostream>
#include "canvas2d.hpp"
#include <math.h>
#include <qmessagebox.h> 
#include <qinputdialog.h> 

using namespace std;

/*******************************************************
 * the default Polygone constructor
 *
 ******************************************************/
Polygone::Polygone(Canvas2D *parent)
{

  bool ok;
  int res = QInputDialog::getInteger(
				     "Another cylinder", "Number of vertices:", 
				     3, 3, 12, 1,
				     &ok, parent );
  if ( ok ) {
    _nbPoints = res;
  }
  
  _redCircle = RED_CIRCLE;
  _greenCircle = GREEN_CIRCLE;
  _blueCircle = BLUE_CIRCLE;

}

/*******************************************************
 * the Polygonee destructor
 *
 ******************************************************/
Polygone::~Polygone() {
} 
 
/*******************************************************
 * draw the polygone in the openGL widget
 *
 ******************************************************/
void Polygone::render(){

  double increment; 
  increment = Control_point_size / 2.0;
  
  glColor3f(_redColor, _greenColor, _blueColor);

  glBegin(GL_LINE_STRIP);
  for(int i = 0 ; i < int(_pointsVector.size()); i++){
    glVertex2f((*_pointsVector[i])[0], (*_pointsVector[i])[1]);
  }
  glEnd();

  if (getNbPoints() == 2) {

    // Ray compute
    float x = pow((float)(*_pointsVector[1])[0] - 
		  (float)(*_pointsVector[0])[0],2);
    float y = pow((float)(*_pointsVector[1])[1] - 
		  (float)(*_pointsVector[0])[1],2);

    float r = sqrt(x + y);
    
    glBegin(GL_LINE_STRIP);
    for ( int i = 0 ; i < 360 ; i++) {
      float angle = (float)i * 3.14159F / ((float)_nbPoints/2.0) ;
      float x = (float) ((*_pointsVector[0])[0] + r*cos(angle)) ;
      float y = (float) ((*_pointsVector[0])[1] + r*sin(angle)) ;
      glVertex2f(x,y) ;
    }
    glEnd();

    glColor3f(_redCircle, _greenCircle, _blueCircle);
    
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

/*******************************************************
 * discretize the polygone
 * @param nbDiscretizedPoints the number of points discretized 
 * between two points of a segment of the polygon.
 * @return the vector of points (the discretized polyline)
 *
 ******************************************************/
std::vector<gml::Point3D> Polygone::discretize(int nbDiscretizedPoints)
{
  std::vector<gml::Point3D> pointsList;
  std::vector<gml::Point3D> pointsPoly;

  if (getNbPoints() == 2) {
       
    // Ray compute
    float x = pow((float)(*_pointsVector[1])[0] - 
		  (float)(*_pointsVector[0])[0],2);
    float y = pow((float)(*_pointsVector[1])[1] - 
		  (float)(*_pointsVector[0])[1],2);
    
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
      int nbPointsSegment = nbDiscretizedPoints/_nbPoints;
      for (int j=1; j<nbPointsSegment;j++) {
	if (pointsPoly[i][0] < pointsPoly[i+1][0] && 
	    pointsPoly[i][1] < pointsPoly[i+1][1]) {
	  Point3D p;
	  p[0] = pointsPoly[i][0] + 
	    (diffx*(j/((float)nbDiscretizedPoints/(float)_nbPoints)));
	  p[1] = pointsPoly[i][1] + 
	    (diffy*(j/((float)nbDiscretizedPoints/(float)_nbPoints)));
	  p[2] = 0.0;
	  pointsList.push_back(p);
	}
	else {
	  if (pointsPoly[i][0] > pointsPoly[i+1][0] && 
	      pointsPoly[i][1] < pointsPoly[i+1][1]) {
	    Point3D p;
	    p[0] = pointsPoly[i][0] - 
	      (diffx*(j/(float)(nbDiscretizedPoints/(float)_nbPoints)));
	    p[1] = pointsPoly[i][1] + 
	      (diffy*(j/(float)(nbDiscretizedPoints/(float)_nbPoints)));
	    p[2] = 0.0;
	    pointsList.push_back(p);
	  }
	  else {
	    if (pointsPoly[i][0] > pointsPoly[i+1][0] && 
		pointsPoly[i][1] > pointsPoly[i+1][1]) {
	      Point3D p;
	      p[0] = pointsPoly[i][0] - 
		(diffx*(j/(float)(nbDiscretizedPoints/(float)_nbPoints)));
	      p[1] = pointsPoly[i][1] - 
		(diffy*(j/(float)(nbDiscretizedPoints/(float)_nbPoints)));
	      p[2] = 0.0;
	      pointsList.push_back(p);
	    }
	    else {
	      Point3D p;
	      p[0] = pointsPoly[i][0] + 
		(diffx*(j/(float)(nbDiscretizedPoints/(float)_nbPoints)));
	      p[1] = pointsPoly[i][1] - 
		(diffy*(j/(float)(nbDiscretizedPoints/(float)_nbPoints)));
	      p[2] = 0.0;
	      pointsList.push_back(p);
	    }
	  }
	}
      }
    }

  }

  /*for (int i=0; i<pointsList.size();i++) {
    cout << "x= " << pointsList[i][0] << " y= " << pointsList[i][1] << endl;
    }*/
  
  return pointsList;
}

/*******************************************************
 * add a point to the polygone
 * @param point the point to add
 * @return ADDED or NOT_ADDED
 *
 ******************************************************/
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

/**************************************************************
 *
 *  get the number of segment of the curve
 *  @return the number of segments
 *
 *************************************************************/
int Polygone::getNumberOfSegments()
{
  return _nbPoints;
}
