#ifndef CLASS_CAMERA_H
#define CLASS_CAMERA_H

#include "point.hpp"
#include "vector.hpp"

namespace gml
{
  
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

    public:

    Camera();
    
    void updateAxis();

        
  };
}


#endif
