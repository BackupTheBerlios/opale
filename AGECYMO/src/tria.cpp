#include "tria.hpp"

/**************************************************************
 *
 *  constructor for Tria class
 *  @param points a vector of points used in the quad
 *  @param i1 the first index of the quad
 *  @param i2 the second index of the quad
 *  @param i3 the third index of the quad
 *
 *************************************************************/
Tria::Tria(std::vector<gml::Point3D> *points, int i1, int i2, int i3)
    : AbsFace(points),
      _i1(i1),
      _i2(i2),
      _i3(i3)
{
  updateNormal();
}


/**************************************************************
 *
 *  copy constructor for Tria class
 *  @param t1 another Tria
 *
 *************************************************************/
Tria::Tria(Tria const & t1)
    : AbsFace(t1)
{
  _i1 = t1._i1;
  _i2 = t1._i2;
  _i3 = t1._i3;

  updateNormal();
}

/**************************************************************
 *
 *  draw the triangle in the openGL context
 *
 *************************************************************/
void
Tria::render()
{
  assert(_points != NULL);
  
  std::vector<gml::Point3D>  tpoints = *_points;
  std::vector<gml::Vector3D> & tnormals = *_normals;

  
  glBegin(GL_TRIANGLES);

  glColor3f(0.0, 0.0, 1.0);

  glNormal3f(tnormals[_i1][0], tnormals[_i1][1], tnormals[_i1][2]);

  
  glVertex3d(tpoints[_i1][0],
             tpoints[_i1][1],
             tpoints[_i1][2]);

  glNormal3f(tnormals[_i2][0], tnormals[_i2][1], tnormals[_i2][2]);
  
  glVertex3d(tpoints[_i2][0],
             tpoints[_i2][1],
             tpoints[_i2][2]);
  
  glNormal3f(tnormals[_i3][0], tnormals[_i3][1], tnormals[_i3][2]);
  
  glVertex3d(tpoints[_i3][0],
             tpoints[_i3][1],
             tpoints[_i3][2]);
  
  glEnd();
    
}


/**************************************************************
 *
 *  draw the normals of the triangle
 *
 *************************************************************/
void
Tria::renderNormal()
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

/**************************************************************
 *
 *  draw the triangle in the openGL context with the normals
 *
 *************************************************************/
void
Tria::renderWithNormal()
{
  render();
  renderNormal();
}

/**************************************************************
 *
 *  define the equal operator for Tria
 *
 *************************************************************/
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

/**************************************************************
 *
 *  redefine the display stream operator for debug
 *
 *************************************************************/
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

/**************************************************************
 *
 *  define if the triangle contains a vertex
 *  @param vertexIndex the index of the vertex
 *  @return true if the quad contains the vertex, false else
 *
 *************************************************************/
bool
Tria::containVertex(int vertexIndex) const
{
  if ( (vertexIndex == _i1) ||
       (vertexIndex == _i2) ||
       (vertexIndex == _i3) )
  {
    return true;
  }

  return false;
}

/**************************************************************
 *
 *  returns all the indexes of the triangle
 *  @return a vector of indexes
 *
 *************************************************************/
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

/**************************************************************
 *
 *  update the normals of the triangle
 *
 *************************************************************/
void
Tria::updateNormal()
{
  std::vector<gml::Point3D> tpoints = *_points;

  gml::Vector3D v1 = tpoints[_i2] -  tpoints[_i1];
  gml::Vector3D v2 = tpoints[_i3] -  tpoints[_i1];

  _normal = cross(v1, v2);
  _normal.normalize();

  _center[0] =  (tpoints[_i1][0] +  tpoints[_i2][0] + tpoints[_i3][0]) / 3.0;
  _center[1] =  (tpoints[_i1][1] +  tpoints[_i2][1] + tpoints[_i3][1]) / 3.0;
  _center[2] =  (tpoints[_i1][2] +  tpoints[_i2][2] + tpoints[_i3][2]) / 3.0;
  
  _n1[0] = _normal[0] + _center[0];
  _n1[1] = _normal[1] + _center[1];
  _n1[2] = _normal[2] + _center[2];

}
