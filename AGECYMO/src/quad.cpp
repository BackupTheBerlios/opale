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
