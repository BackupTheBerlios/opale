#ifndef CLASS_CYLINDERGENERATOR_H
#define CLASS_CYLINDERGENERATOR_H


#include <qdatetime.h>


#include "matrix.hpp"
#include "face.hpp"
#include "faces.hpp"
#include "canvas3d.hpp"


class Canvas3D;

using namespace gml;

const double EPSILON = 0.0000001;


class CylinderGenerator
{

  private:
  Canvas3D & _canvas;

  std::vector<Point3D >  * _points;
  std::vector<AbsFace *> * _faces;

  int _nbPtWay; //number of points on the way;
  
  //Faces* _model; //model cached
  bool _isWayClosed;

  bool _torsionEnabled;
  
  QTime _chronometer;
  
  
  public:
  CylinderGenerator(Canvas3D & acanvas);

  ~CylinderGenerator();
  
  
  void setWayClosed(bool wayStatus);

  void setTorsionEnabled(bool torsion);

  
  //returns the elpased time to generate the cylinder
  int  generate(const std::vector<Point3D> & wayPts,
                const std::vector<Point3D> & sectionPts,
                const std::vector<Point3D> & profilePts);

  private:

  int profileToWayByIndex( const std::vector<Point3D> & profilePts,
                         int profileIndex);
  
  void generatePoints(const std::vector<Point3D> & wayPts,
                      const std::vector<Point3D> & sectionPts,
                      const std::vector<Point3D> & profilePts);

  void generateFaces(int nbPtWay, int nbPtSection);

  
  void initFrenetFrame(const Point3D & p1,
                       const Point3D & p2,
                       Matrix3D & frame);
  
  void computeFrenetFrame( const Matrix3D & previousFrame,
                           const Point3D & previous,
                           const Point3D & current,
                           const Point3D & next,
                           Matrix3D & newCurrentframe);
  

  void lastFrenetFrame(const Point3D & p1,
                       const Point3D & p2,
                       Matrix3D & frame);
  
  void computePointsAccordingToFrame( const std::vector<Point3D> & sectionPts,
                                      Matrix3D & currentFrame);
  
  
  void computeProfileMatrix( const std::vector<Point3D> & profilePts,
                             int indexCurrentPoint,
                             Matrix3D & profileMatrix);
  
};



#endif
