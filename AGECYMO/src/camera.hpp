#ifndef CLASS_CAMERA_H
#define CLASS_CAMERA_H

#include "point.hpp"
#include "vector.hpp"
#include "matrix.hpp"



namespace gml
{
  
  
  const double PI_2 = M_PI / 2.0;
  
  const  double DEFAULT_INCR_THETA = M_PI / 180.0;     //1 degree
  
  const  double DEFAULT_INCR_PSI = M_PI / 180.0;     //1 degree

  const  double DEFAULT_INCR_PHI   = 5 * M_PI / 180.0; //5 degrees

  const  double DEFAULT_INCR_DIST = 0.150;
  
  /******************************************************
   * This is a simple camera which by default looks to 
   * the world origin.
   * Its moves are constrains to maintain its lookat point.
   *
   ******************************************************/
  class Camera
  {

    public:
    
    Point3D _position; /**position of the camera in world coordinates*/
    Point3D _lookat; /**look at the camera in word coordinates*/
    
    Vector3D _up; /**up vector*/

    double _fovy; /**fovy*/

    private:
    Vector3D _x; /**Axis x of the referential of the camera*/
    Vector3D _y; /**Axis y of the referential of the camera*/
    Vector3D _z; /**Axis z of the referential of the camera*/

    double _theta; /** spherical coordinates*/
    double _phi; /**PHI*/
    double _psi; /**PSI*/
    double _rho; /**RHO*/
    double _thetaIncr; /**THETA*/
    double _phiIncr; /**PHI increment*/
    double _rhoIncr; /**RHO increment*/
    double _psiIncr; /**PSI increment*/
    
    
    //Matrices to manage the camera moves
    Matrix3D _matRotIncrY; /**matrix to turn around Y axis, increment*/ 
    Matrix3D _matRotDecrY; /**matrix to turn around Y axis, decrement*/ 
    
    Matrix3D _matRotIncrX; /**matrix to turn around X axis, increment*/ 
    Matrix3D _matRotDecrX; /**matrix to turn around X axis, decrement*/ 
    
    Matrix3D _matRotIncrZ; /**matrix to turn around Z axis, increment*/ 
    Matrix3D _matRotDecrZ; /**matrix to turn around Z axis, decrement*/ 
    
    Matrix3D _matIncrPsi; /**matrix for PSI, increment*/ 
    Matrix3D _matDecrPsi; /**matrix for PSI, decrement*/ 
    
    Matrix3D _matIncrTheta; /**matrix for THETA, increment*/ 
    Matrix3D _matDecrTheta; /**matrix for THETA, decrement*/ 
    
    public:

    /**************************************************************
     *
     *  Camera constructor
     *
     *************************************************************/
    Camera();

    //Sets the position this will update spherical coordinates

    /**************************************************************
     *
     *  set the camera position
     *  
     *  @param new_position the new position
     *
     *************************************************************/
    void setCameraPosition(Point3D const& new_position);

    /**************************************************************
     *
     *  set the camera position
     *  
     *  @param px x coordinate
     *  @param py y coordinate
     *  @param pz z coordinate
     *
     *************************************************************/
    void setCameraPosition(double px, double py, double pz);
  
    /**************************************************************
     *
     *  set the vector up of the camera
     *  
     *  @param upx x coordinate
     *  @param upy y coordinate
     *  @param upz z coordinate
     *
     *************************************************************/
    void setCameraUp(double upx, double upy, double upz);

    /**************************************************************
     *
     *  set the lookAt of the camera
     *  
     *  @param cx x coordinate
     *  @param cy y coordinate
     *  @param cz z coordinate
     *
     *************************************************************/
    void setCameraLookAt(double cx, double cy, double cz);

    /**************************************************************
     *
     *  increment PHI
     *  
     *
     *************************************************************/
    void incrementPhi();

    /**************************************************************
     *
     *  decrement PHI
     *
     *************************************************************/
    void decrementPhi();
    
    /**************************************************************
     *
     *  increment THETA
     *
     *************************************************************/
    void incrementTheta();

    /**************************************************************
     *
     *  decrement THETA
     *
     *************************************************************/
    void decrementTheta();
        
    /**************************************************************
     *
     *  increment PSI
     *
     *************************************************************/
    void incrementPsi();

    /**************************************************************
     *
     *  decrement PSI
     *
     *************************************************************/
    void decrementPsi();

    /**************************************************************
     *
     *  increment distance
     *
     *************************************************************/
    void incrementDistance();

    /**************************************************************
     *
     *  decrement distance
     *
     *************************************************************/
    void decrementDistance();
    
      
    /**************************************************************
     *
     *  redefines the display stream operator for debuging purpose
     *
     *************************************************************/
    friend std::ostream& operator<<(std::ostream& os, Camera const& cam)
    {
      os << "Camera : position = " << cam._position << " up = " << cam._up << std::endl
         << " phi = " << cam._phi
         << " theta = " << cam._theta
         << " rho = " << cam._rho << std::endl;
      
      return os;
    };
    

    private:

    /**************************************************************
     *
     *  update THETA transform matrix
     *
     *************************************************************/
    void updateThetaTransformMatrix();

    /**************************************************************
     *
     *  update PSI transform matrix
     *
     *************************************************************/
    void updatePsiTransformMatrix();
    
    /**************************************************************
     *
     *  update Spherical coordinates
     *
     *************************************************************/
    void updateSphericalCoordinates();

    /**************************************************************
     *
     *  update Cartesian coordinates 
     *
     *************************************************************/
    void updateCartesianCoordinates();
    
    /**************************************************************
     *
     *  update the axis 
     *
     *************************************************************/
    void updateAxis();

    
  };

}


#endif
