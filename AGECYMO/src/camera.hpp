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
  
  
  /**
   * This is a simple camera which by default looks to the world origin
   * Its moves are constrains to maintain its lookat point.
   */
  class Camera
  {

    public:
    
    Point3D _position; //position of the camera in world coordinates
    Point3D _lookat; //look at the camera in word coordinates
    
    Vector3D _up;

    double _fovy; //fovy

    private:
    Vector3D _x; //Axis of the referential of the camera
    Vector3D _y;
    Vector3D _z;

    double _theta; // spherical coordinates
    double _phi;   
    double _psi;
    double _rho;
        
    double _thetaIncr;
    double _phiIncr;
    double _rhoIncr;
    double _psiIncr;
    
    
    //Matrices to manage the camera moves
    Matrix3D _matRotIncrY; //matric to turn around Y axis 
    Matrix3D _matRotDecrY;
    
    Matrix3D _matRotIncrX; //matric to turn around X axis 
    Matrix3D _matRotDecrX;
    
    Matrix3D _matRotIncrZ; //matric to turn around Z axis 
    Matrix3D _matRotDecrZ;
    
    Matrix3D _matIncrPsi;
    Matrix3D _matDecrPsi;
    
    Matrix3D _matIncrTheta;
    Matrix3D _matDecrTheta;
    
    public:

    Camera();

    //Sets the position this will update spherical coordinates
    void setCameraPosition(Point3D const& new_position);
    void setCameraPosition(double px, double py, double pz);
  
    void setCameraUp(double upx, double upy, double upz);
    void setCameraLookAt(double cx, double cy, double cz);

    
    
    void incrementPhi();
    void decrementPhi();
    
    void incrementTheta();
    void decrementTheta();
        
    void incrementPsi();
    void decrementPsi();

    void incrementDistance();
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

    void updateThetaTransformMatrix();
    void updatePsiTransformMatrix();
    
    void updateSphericalCoordinates();
    void updateCartesianCoordinates();
    
    
    void updateAxis();

    
  };

}


#endif
