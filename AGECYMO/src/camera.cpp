#include "camera.hpp"

using namespace gml;
  
Camera::Camera()
{
  _position[0] = 0; _position[1] = 0; _position[2] = 20;

  _lookat[0] = 0; _lookat[1] = 0; _lookat[2] = 0;

  _up[0] = 0; _up[1] = 1; _up[2] = 0;

  _fovy = 60;
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

