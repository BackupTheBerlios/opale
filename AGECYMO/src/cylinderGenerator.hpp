#ifndef CLASS_CYLINDERGENERATOR_H
#define CLASS_CYLINDERGENERATOR_H


#include <qdatetime.h>


#include "matrix.hpp"
#include "face.hpp"
#include "faces.hpp"
#include "canvas3d.hpp"


class Canvas3D;

using namespace gml;




class CylinderGenerator
{

  private:
  Canvas3D & _canvas;

  std::vector<Point3D >  * _points;
  std::vector<AbsFace *> * _faces;

  double _minProfile;
  double _maxProfile;
  
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

  void updateMinMaxProfile( const std::vector<Point3D> & profilePts );
  
  int profileToWayByIndex( const std::vector<Point3D> & profilePts,
                         int profileIndex);

  void profileToWayByPoints( const std::vector<Point3D> & wayPts,
                             const std::vector<Point3D> & profilePts,
                             int profileIndex,
                             Point3D & previous,
                             Point3D & current,
                             Point3D & next);
  
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
                                      Matrix3D & currentFrame,
                                      Matrix3D & dilatationMatrix);
  
//   void computePointsAccordingToFrame( const std::vector<Point3D> & sectionPts,
//                                       Matrix3D & currentFrame);
  
  
  
  void computeProfileMatrix( const std::vector<Point3D> & profilePts,
                             int indexCurrentPoint,
                             Matrix3D & profileMatrix);
  
};



#endif
