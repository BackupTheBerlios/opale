#include "quad.hpp"

Quad::Quad(std::vector<gml::Point3D> *points, int i1, int i2, int i3, int i4)
    : AbsFace(points),
      _i1(i1),
      _i2(i2),
      _i3(i3),
      _i4(i4)
{
  updateNormal();
}

void
Quad::render()
{
  std::vector<gml::Point3D> tpoints = *_points;
    
//  qDebug("Dans QUAD render");

  
  glBegin(GL_QUADS);
  
  glNormal3f(_normal[0], _normal[1], _normal[2]);

  glColor3f(0.0, 1.0, 0.0);
  glVertex3d(tpoints[_i1][0],
             tpoints[_i1][1],
             tpoints[_i1][2]);
  
  glVertex3d(tpoints[_i2][0],
             tpoints[_i2][1],
             tpoints[_i2][2]);
  
  glVertex3d(tpoints[_i3][0],
             tpoints[_i3][1],
             tpoints[_i3][2]);
  
  glVertex3d(tpoints[_i4][0],
             tpoints[_i4][1],
             tpoints[_i4][2]);
  
  glEnd();
}

void
Quad::renderNormal()
{

  glBegin(GL_LINES);

  glColor3f(1.0, 0.0, 1.0);
  
  glVertex3d(_center[0],
             _center[1],
             _center[2]);
   
  glVertex3d(_n1[0],
             _n1[1],
             _n1[2]);
  
  glEnd();
}


void
Quad::renderWithNormal()
{
  render();
  renderNormal();
}


std::vector<int>*
Quad::getIndexes()
{
  std::vector<int> *indices;
  indices = new std::vector<int>;

  indices->push_back(_i1);
  indices->push_back(_i2);
  indices->push_back(_i3);
  indices->push_back(_i4);
  
  return indices;
}

// int Quad::nbPoints(){
//   return 4;
// }

// int Quad::getIndex(int num){
//   if((num>(nbPoints()-1)) || (index<0)){
//     exit(-1);;
//   }
//   else{
//     if(num == 0) return _i1; 
//     if(num == 1) return _i2; 
//     if(num == 2) return _i3; 
//     if(num == 3) return _i4; 
//   }
// }


void
Quad::updateNormal()
{  
  std::vector<gml::Point3D> tpoints = *_points;

  gml::Vector3D v1 = tpoints[_i2] -  tpoints[_i1];
  gml::Vector3D v2 = tpoints[_i3] -  tpoints[_i1];
  
  gml::Vector3D v3 = tpoints[_i3] -  tpoints[_i2];
  gml::Vector3D v4 = tpoints[_i4] -  tpoints[_i2];

  gml::Vector3D normal1 = cross(v1, v2);
  gml::Vector3D normal2 = cross(v3, v4);

  //TODO: remove it ?
  normal1.normalize();
  normal2.normalize();
  
  _normal = (normal1 + normal2) * 0.5;

  _normal.normalize();
    
  _center[0] =  (tpoints[_i1][0] +
                 tpoints[_i2][0] +
                 tpoints[_i3][0] +
                 tpoints[_i4][0]) / 4.0;
  
  _center[1] =  (tpoints[_i1][1] +
                 tpoints[_i2][1] +
                 tpoints[_i3][1] +
                 tpoints[_i4][1]) / 4.0;

  _center[2] =  (tpoints[_i1][2] +
                 tpoints[_i2][2] +
                 tpoints[_i3][2] +
                 tpoints[_i4][2]) / 4.0;
  
  _n1[0] = _normal[0] + _center[0];
  _n1[1] = _normal[1] + _center[1];
  _n1[2] = _normal[2] + _center[2];

}



std::ostream&
operator<<(std::ostream& os, Quad const& q)
{
  os << "Quad points address is " << q._points << std::endl;
  
  os << " [ " << q._i1
     << ", "  << q._i2
     << ", "  << q._i3
     << ", "  << q._i4
     << " ] " << std::endl;
  
  return os;
}
