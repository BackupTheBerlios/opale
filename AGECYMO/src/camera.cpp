#include "camera.hpp"

using namespace gml;
  
Camera::Camera()
    : _thetaIncr(DEFAULT_INCR_THETA),
      _phiIncr(DEFAULT_INCR_PHI),
      _rhoIncr(DEFAULT_INCR_DIST),
      _theta(M_PI/2.0),
      _phi(0.0),
      _rho(2.0)

{  
  //matrices to manage the camera
  _matRotIncrY = Matrix3D::rotationY(   _phiIncr);
  _matRotDecrY = Matrix3D::rotationY( - _phiIncr);

  
  _matRotIncrX = Matrix3D::rotationX(   _thetaIncr);
  _matRotDecrX = Matrix3D::rotationX( - _thetaIncr);
    
  updateThetaTransformMatrix();
  
  
  //camera parameters according to phi, theta and rho 
  _position[0] = 0; _position[1] = 0; _position[2] = 2;

  _lookat[0] = 0; _lookat[1] = 0; _lookat[2] = 0;

  _up[0] = 0; _up[1] = 1; _up[2] = 0;

  _fovy = 120;
}


void
Camera::incrementPhi()
{
  Point3D newPosition;

  _phi +=  _phiIncr;
  
  newPosition = _matRotIncrY * _position;

  _position = newPosition;
  
  updateThetaTransformMatrix();
}

void
Camera::decrementPhi()
{
  Point3D newPosition;

  _phi -=  _phiIncr;
  
  newPosition = _matRotDecrY * _position;

  _position = newPosition;

  updateThetaTransformMatrix();
}

    
void
Camera::incrementTheta()
{
  Point3D newPosition;

  _theta += _thetaIncr;
    
  newPosition = _matIncrTheta * _position;
  
  _position = newPosition;
    
}

void
Camera::decrementTheta()
{
  Point3D newPosition;

  _theta -= _thetaIncr;
 
  newPosition = _matDecrTheta * _position;
  
  _position = newPosition;
}

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

void
Camera::setCameraPosition(gml::Point3D const& new_position)
{
  _position = new_position;
  updateSphericalCoordinates();
}


void
Camera::setCameraPosition(double px, double py, double pz)
{
  _position[0] = px;
  _position[1] = py;
  _position[2] = pz;

  updateSphericalCoordinates();
}

void
Camera::setCameraUp(double upx, double upy, double upz)
{
  _up[0] = upx;
  _up[1] = upy;
  _up[2] = upz;

  updateAxis();
}

void
Camera::setCameraLookAt(double cx, double cy, double cz)
{
  _lookat[0] = cx;
  _lookat[1] = cy;
  _lookat[2] = cz;

  updateAxis();
}

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

void
Camera::updateSphericalCoordinates()
{
  double x2y2 =  _position[0] * _position[0] +_position[1] * _position[1];
  
  _rho = sqrt ( x2y2 + _position[2] * _position[2]);

  _phi =  M_PI + atan2( _position[1], _position[0] ) ;

  _theta =   M_PI/2.0 + atan( sqrt(x2y2) / _position[2] );
}

void
Camera::updateCartesianCoordinates()
{
  double sint =  sin(_theta);
    
  _position[0] = _rho * cos(_phi) * sint;
  _position[1] = _rho * sin(_phi) * sint ;
  _position[2] = _rho * cos(_theta);
}


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
