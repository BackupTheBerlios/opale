#include "camera.hpp"

using namespace gml;
  

/**************************************************************
 *
 *  Camera constructor
 *
 *************************************************************/
Camera::Camera()
    :_theta(M_PI/2.0),
     _phi(0.0),
     _psi(0.0),
     _rho(2.0),
     _thetaIncr(DEFAULT_INCR_THETA),
     _phiIncr(DEFAULT_INCR_PHI),
     _rhoIncr(DEFAULT_INCR_DIST),
     _psiIncr(DEFAULT_INCR_PSI)
{  
  //matrices to manage the camera
  _matRotIncrY = Matrix3D::rotationY(   _phiIncr);
  _matRotDecrY = Matrix3D::rotationY( - _phiIncr);
  
  _matRotIncrX = Matrix3D::rotationX(   _thetaIncr);
  _matRotDecrX = Matrix3D::rotationX( - _thetaIncr);

  updateThetaTransformMatrix();
  
  _matRotIncrZ = Matrix3D::rotationZ(   _psiIncr);
  _matRotDecrZ = Matrix3D::rotationZ( - _psiIncr);

  updatePsiTransformMatrix();
  
  //camera parameters according to phi, theta and rho 
  _position[0] = 0; _position[1] = 0; _position[2] = 2;

  _lookat[0] = 0; _lookat[1] = 0; _lookat[2] = 0;

  _up[0] = 0; _up[1] = 1; _up[2] = 0;

  _fovy = 120;
}

/**************************************************************
 *
 *  increment PHI
 *  
 *
 *************************************************************/
void
Camera::incrementPhi()
{
  _phi +=  _phiIncr;
  
  Point3D newPosition;
  newPosition = _matRotIncrY * _position;
  _position = newPosition;
  
  updateThetaTransformMatrix();
  updatePsiTransformMatrix();
}

/**************************************************************
 *
 *  decrement PHI
 *
 *************************************************************/
void
Camera::decrementPhi()
{
  _phi -=  _phiIncr;

  Point3D newPosition;
  newPosition = _matRotDecrY * _position;
  _position = newPosition;

  updateThetaTransformMatrix();
  updatePsiTransformMatrix();
}

/**************************************************************
 *
 *  increment PSI
 *
 *************************************************************/
void
Camera::incrementPsi()
{
  _psi += _psiIncr;

  Vector3D newUp;
  newUp = _matIncrPsi * _up;
  _up = newUp;
}


void
Camera::decrementPsi()
{
  _psi -= _psiIncr;

  Vector3D newUp;
  newUp = _matDecrPsi * _up;
  _up = newUp;
}

/**************************************************************
 *
 *  decrement PSI
 *
 *************************************************************/
void
Camera::incrementTheta()
{
  _theta += _thetaIncr;
  
//   if ( _theta < gml::EPSILON )
//   {
//     _theta = 0;
//     return;
//   }

//   if ( _theta > 3.14)
//   {
//     _theta = M_PI;
//     return;
//   }
  
  std::cout << "theta = " << _theta << std::endl;
  
  Point3D newPosition;
  newPosition = _matIncrTheta * _position;
  _position = newPosition;
  
  //Vector3D newUp;
  //newUp = _matIncrTheta * _up;
  //_up = newUp;
  
  updatePsiTransformMatrix();
}

/**************************************************************
 *
 *  decrement THETA
 *
 *************************************************************/
void
Camera::decrementTheta()
{
  _theta -= _thetaIncr;
  
//   if ( _theta < gml::EPSILON )
//   {
//     _theta = 0;
//     return;
//   }

//   if ( _theta > M_PI)
//   {
//     _theta = M_PI;
//     return;
//   }

  std::cout << "theta = " << _theta << std::endl;
  
  // Vector3D newUp;
  //newUp = _matDecrTheta * _up;
  //_up = newUp;

  Point3D newPosition;
  newPosition = _matDecrTheta * _position;
  _position = newPosition;
    
  updatePsiTransformMatrix();
}


/**************************************************************
 *
 *  increment distance
 *
 *************************************************************/
void
Camera::incrementDistance()
{
  std::cout << "increment Distance" << std::endl;
  
  Vector3D tr;

  tr[0] = _position[0];
  tr[1] = _position[1];
  tr[2] = _position[2];
  
  tr.normalize();

  tr = tr * _rhoIncr;
    
  _position[0] = _position[0] + tr[0];
  _position[1] = _position[1] + tr[1];
  _position[2] = _position[2] + tr[2];

  _rho +=  _rhoIncr;
}

/**************************************************************
 *
 *  decrement distance
 *
 *************************************************************/
void
Camera::decrementDistance()
{
  std::cout << "DECREMENT Distance" << std::endl;
  
  Vector3D tr;

  tr[0] = _position[0];
  tr[1] = _position[1];
  tr[2] = _position[2];
  
  tr.normalize();

  tr = tr *  (- _rhoIncr);
    
  _position[0] = _position[0] + tr[0];
  _position[1] = _position[1] + tr[1];
  _position[2] = _position[2] + tr[2];

  _rho -=  _rhoIncr;
}

/**************************************************************
 *
 *  set the camera position
 *  
 *  @param new_position the new position
 *
 *************************************************************/
void
Camera::setCameraPosition(gml::Point3D const& new_position)
{
  _position = new_position;
  updateSphericalCoordinates();
}

/**************************************************************
 *
 *  set the camera position
 *  
 *  @param px x coordinate
 *  @param py y coordinate
 *  @param pz z coordinate
 *
 *************************************************************/
void
Camera::setCameraPosition(double px, double py, double pz)
{
  _position[0] = px;
  _position[1] = py;
  _position[2] = pz;

  updateSphericalCoordinates();
}

/**************************************************************
 *
 *  set the vector up of the camera
 *  
 *  @param upx x coordinate
 *  @param upy y coordinate
 *  @param upz z coordinate
 *
 *************************************************************/
void
Camera::setCameraUp(double upx, double upy, double upz)
{
  _up[0] = upx;
  _up[1] = upy;
  _up[2] = upz;

  updateAxis();
}

/**************************************************************
 *
 *  set the lookAt of the camera
 *  
 *  @param cx x coordinate
 *  @param cy y coordinate
 *  @param cz z coordinate
 *
 *************************************************************/
void
Camera::setCameraLookAt(double cx, double cy, double cz)
{
  _lookat[0] = cx;
  _lookat[1] = cy;
  _lookat[2] = cz;

  updateAxis();
}

/**************************************************************
 *
 *  update THETA transform matrix
 *
 *************************************************************/
void
Camera::updateThetaTransformMatrix()
{

  _matIncrTheta = Matrix3D::rotationY( - _phi);
  _matIncrTheta = _matRotIncrX *  _matIncrTheta;
  _matIncrTheta =  Matrix3D::rotationY( + _phi) *  _matIncrTheta;
  
  _matDecrTheta = Matrix3D::rotationY( - _phi);
  _matDecrTheta = _matRotDecrX *  _matDecrTheta;
  _matDecrTheta = Matrix3D::rotationY( + _phi) *  _matDecrTheta;


}

/**************************************************************
 *
 *  update PSI transform matrix
 *
 *************************************************************/
void
Camera::updatePsiTransformMatrix()
{
  _matIncrPsi = Matrix3D::rotationY( - _phi);
  _matIncrPsi = Matrix3D::rotationX( PI_2 - _theta) * _matIncrPsi;
  _matIncrPsi = _matRotIncrZ * _matIncrPsi;
  _matIncrPsi = Matrix3D::rotationX( _theta - PI_2 ) * _matIncrPsi;
  _matIncrPsi = Matrix3D::rotationY( + _phi) * _matIncrPsi;

  _matDecrPsi = Matrix3D::rotationY( - _phi);
  _matDecrPsi = Matrix3D::rotationX( PI_2 - _theta) * _matDecrPsi;
  _matDecrPsi = _matRotDecrZ * _matDecrPsi;
  _matDecrPsi = Matrix3D::rotationX( _theta - PI_2 ) * _matDecrPsi;
  _matDecrPsi = Matrix3D::rotationY( + _phi) * _matDecrPsi;
}

/**************************************************************
 *
 *  update Spherical coordinates
 *
 *************************************************************/
void
Camera::updateSphericalCoordinates()
{
  double x2y2 =  _position[0] * _position[0] +_position[1] * _position[1];
  
  _rho = sqrt ( x2y2 + _position[2] * _position[2]);

//  _phi =  M_PI + atan2( _position[1], _position[0] ) ;
  _phi =  atan2( _position[1], _position[0] ) ;

  std::cout << "dans updateSpherical coordinates phi = " << _phi << std::endl;
  
  _theta =   M_PI/2.0 + atan( sqrt(x2y2) / _position[2] );
}

/**************************************************************
 *
 *  update Cartesian coordinates 
 *
 *************************************************************/
void
Camera::updateCartesianCoordinates()
{
  double sint =  sin(_theta);
    
  _position[0] = _rho * cos(_phi) * sint;
  _position[1] = _rho * sin(_phi) * sint ;
  _position[2] = _rho * cos(_theta);
}

/**************************************************************
 *
 *  update the axis 
 *
 *************************************************************/
void
Camera::updateAxis()
{
  _z = _lookat - _position;
  _z.normalize();

  _x = cross(_z, _up);
  _x.normalize();
  
  _y = cross(_x, _z);
  _y.normalize();
}

    
