#include "quad.hpp"

Quad::Quad(std::vector<gml::Point3D> *points, int i1, int i2, int i3, int i4)
    : AbsFace(points),
      _i1(i1),
      _i2(i2),
      _i3(i3),
      _i4(i4)
{
}

void
Quad::render()
{
  std::vector<gml::Point3D> tpoints = *_points;
    
  std::cout << "Dans QUAD render" << std::endl;



  std::cout << tpoints[_i1]
            << tpoints[_i2]
            << tpoints[_i3]
            << tpoints[_i4] << std::endl;
  
  glBegin(GL_QUADS);

  glColor3f(1.0, 0.0, 0.0);
  glVertex3d(tpoints[_i1][0],
             tpoints[_i1][1],
             tpoints[_i1][2]);
    
  glColor3f(0.0, 1.0, 0.0);
  
  glVertex3d(tpoints[_i2][0],
             tpoints[_i2][1],
             tpoints[_i2][2]);
    
  glColor3f(0.0, 0.0, 1.0);
  
  glVertex3d(tpoints[_i3][0],
             tpoints[_i3][1],
             tpoints[_i3][2]);
  
  glColor3f(1.0, 0.0, 1.0);
  
  glVertex3d(tpoints[_i4][0],
             tpoints[_i4][1],
             tpoints[_i4][2]);
  
  glEnd();
}
