#include "tria.hpp"

Tria::Tria(std::vector<gml::Point3D> *points, int i1, int i2, int i3)
    : AbsFace(points),
      _i1(i1),
      _i2(i2),
      _i3(i3)
{
}

Tria::Tria(Tria const & t1)
    : AbsFace(t1)
{
  _i1 = t1._i1;
  _i2 = t1._i2;
  _i3 = t1._i3;
}

void
Tria::render()
{
  assert(_points != NULL);

//  qDebug("Dans Tria render");

  std::vector<gml::Point3D> tpoints = *_points;
  
  
  glBegin(GL_TRIANGLES);

  glColor3f(0.0, 0.0, 1.0);
  glVertex3d(tpoints[_i1][0],
             tpoints[_i1][1],
             tpoints[_i1][2]);
    
  glVertex3d(tpoints[_i2][0],
             tpoints[_i2][1],
             tpoints[_i2][2]);
  
  glVertex3d(tpoints[_i3][0],
             tpoints[_i3][1],
             tpoints[_i3][2]);
  
  glEnd();
}

Tria&
Tria::operator=(Tria const & t1)
{
  AbsFace::operator=(t1);

  std::cout << "Dans operator = de Tria" << std::endl;
    
//   if ( (void *) this == (void  *) &t1) //assignment to itself ?
//   {
//     return *this;
//   }

//   _points = t1._points;

  _i1 = t1._i1;
  _i2 = t1._i2;
  _i3 = t1._i3;
  
  return *this;
}

std::ostream&
operator<<(std::ostream& os, Tria const& t)
{
  os << "Tria points address is " << t._points;
  
  os << " [ " << t._i1
     << ", "  << t._i2
     << ", " << t._i3
     << " ] " << std::endl;
  
  return os;
}

std::vector<int> *
Tria::getIndexes()
{
  std::vector<int> *indices;
  indices = new std::vector<int>;

  indices->push_back(_i1);
  indices->push_back(_i2);
  indices->push_back(_i3);

  return indices;
}


// int Tria::nbPoints(){
//   return 3;
// }

// int Tria::getIndex(int num){
//   if((num>(nbPoints()-1)) || (index<0)){
//     exit(-1);
//   }
//   else{
//     if(num == 0) return _i1; 
//     if(num == 1) return _i2; 
//     if(num == 2) return _i3; 
//   }
// }
