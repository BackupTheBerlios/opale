#ifndef CLASS_CYLINDERGENERATOR_H
#define CLASS_CYLINDERGENERATOR_H


#include <qdatetime.h>


#include "matrix.hpp"
#include "face.hpp"
#include "faces.hpp"
#include "canvas3d.hpp"


class Canvas3D;

using namespace gml;

/**
 *
 * This is the main class which is responsible for the Cylinder's generation
 * 
 **/
class CylinderGenerator
{

  private:
  Canvas3D & _canvas; /** The Canvas attached to this generator
                       * this is useful because we need to set the model
                       * to be displayed once it has been generated */

  std::vector<Point3D >  * _points; /** The generated vertices */
  std::vector<AbsFace *> * _faces; /** The generated faces */

  double _minProfile; /** Minimum ordinate of the profile curve */
  double _maxProfile; /** Maximum ordinate of the profile curve */
  
  int _nbPtWay; /** number of points on the way;*/
  
  bool _isWayClosed; /** Whether or not the way curve is closed */

  bool _torsionEnabled; /** Whether or not the torsion is enabled */
  
  QTime _chronometer; /** is to record generation times */ 
  
  
  public:

  /**
   * 
   * CylinderGenerator Constructor
   * @param acanvas the canvas attached to the generator
   * 
   */
  CylinderGenerator(Canvas3D & acanvas);

  /**
   *
   * CylinderGenerator destructor
   * 
   **/
  ~CylinderGenerator();

  /**
   *
   * Sets whether or not the way curve is closed 
   * @param wayStatus
   * 
   **/
  void setWayClosed(bool wayStatus);

  /**
   *
   * Sets whether or not the torsion is enabled 
   * @param torsion
   * 
   **/
  void setTorsionEnabled(bool torsion);
  

  /**
   * 
   * Generates the cylinder with the given discretized three curves
   * @param wayPts the points defining the way curve
   * @param sectionPts the points defining the section curve
   * @param profilePts the points defining the profile curve
   * @return the elapsed time to generate the cylinder in milliseconds
   * 
   **/
  int  generate(const std::vector<Point3D> & wayPts,
                const std::vector<Point3D> & sectionPts,
                const std::vector<Point3D> & profilePts);

  private:

  /**
   *
   * Computes the new minimal and maximal ordinate values with the
   * given profile curve
   * @param profilePts  the points defining the profile curve
   * 
   **/
  void updateMinMaxProfile( const std::vector<Point3D> & profilePts );

  /**
   *
   * Returns the index of a point on the way curve according to the given
   * index on the profile curve
   * @param profilePts the points defining the profile curve
   * @param the index on the profile curve
   * @return the index on the way curve
   **/
  int profileToWayByIndex( const std::vector<Point3D> & profilePts,
                           int profileIndex);


  /**
   *
   * Computes a linearly interpolated point on the way curved with the given
   * profileIndex. Computes also the previous point and the next point
   * used to computed the linarly interpolated point.
   * Returns true if the computation succeed and false if it falses.
   * 
   * @param wayPts the points defining the way curve
   * @param profilePts the points defining the profile curve
   * @param the index on the profile curve
   * @param the previous point
   * @param the current point
   * @param the next point
   * @return whether or not the computation succeed
   * 
   **/  
  bool profileToWayByPoints( const std::vector<Point3D> & wayPts,
                             const std::vector<Point3D> & profilePts,
                             int profileIndex,
                             Point3D & previous,
                             Point3D & current,
                             Point3D & next);

  /**
   *
   * Generates the vertices of the cylinder according
   * to the three given curves
   * @param wayPts the points defining the way curve
   * @param sectionPts the points defining the section curve
   * @param profilePts the points defining the profile curve
   *
   **/
  void generatePoints(const std::vector<Point3D> & wayPts,
                      const std::vector<Point3D> & sectionPts,
                      const std::vector<Point3D> & profilePts);

  /**
   *
   * Generates the faces according to the number of points
   * on the way and on the section and with the previously computed
   * vertices
   * @param nbPtWay the number of points on the way curve
   * @param nbPtSection the number of points on the section curve
   * 
   **/
  void generateFaces(int nbPtWay, int nbPtSection);


  /**
   *
   * Computes the first Frenet frame on the way curve according to two
   * given points and store it in the given  argument frame
   * @param p1 the first point
   * @param p2 the second point
   * @param frame the computed  Frenet frame 
   * 
   **/
  void initFrenetFrame(const Point3D & p1,
                       const Point3D & p2,
                       Matrix3D & frame);
  
  /**
   *
   * Computes the Frenet frame on the way curve according to three
   * given points and store it in the given argument frame.
   *
   * @param previousFrame The previous Frenet frame
   * @param previous the first point
   * @param current the second point
   * @param next the third point
   * @param newCurrentframe the computed  Frenet frame 
   * 
   **/
  void computeFrenetFrame( const Matrix3D & previousFrame,
                           const Point3D & previous,
                           const Point3D & current,
                           const Point3D & next,
                           Matrix3D & newCurrentframe);
  

  /**
   *
   * Computes the last Frenet frame on the way curve according to two
   * given points and store it in the given  argument frame
   * @param p1 the first point
   * @param p2 the second point
   * @param frame the computed  Frenet frame 
   * 
   **/
  void lastFrenetFrame(const Point3D & p1,
                       const Point3D & p2,
                       Matrix3D & frame);

  /**
   *
   * Computes the points for a given Frenet frame passed through
   * currentFrame argument and for a given dilatationMatrix
   * @param sectionPts   The section points
   * @param currentFrame The current Frenet Frame
   * @param dilatationMatrix The current dilation matrix
   **/
  void computePointsAccordingToFrame( const std::vector<Point3D> & sectionPts,
                                      Matrix3D & currentFrame,
                                      Matrix3D & dilatationMatrix);

  /**
   *
   * Compute the a Matrix to compress or dilate the section
   * according to the position on the profile curve.
   * @param profilePts the profile curve
   * @param indexCurrentPoint the position on the profile curve
   * @param the returned profile Matrix
   * 
   **/
  void computeProfileMatrix( const std::vector<Point3D> & profilePts,
                             int indexCurrentPoint,
                             Matrix3D & profileMatrix);
  
};



#endif
