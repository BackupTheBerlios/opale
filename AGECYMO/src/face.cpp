#include "face.hpp"

/**************************************************************
 *
 *  constructor for Face class
 *  @param indexes the indexes of the face
 *  @param points the points used in the face
 *  @param numberOfPoints the number of points in the face
 *
 *************************************************************/
Face::Face(std::vector<int> *indexes, 
	   std::vector<gml::Point3D> *points, 
	   int numberOfPoints)
  : AbsFace(points),
    _numberOfPts(numberOfPoints)
{
  _indexPts = new int[numberOfPoints];

  for(int i=0; i<numberOfPoints;i++)
  {
    _indexPts[i] = (*indexes)[i];
  }

  updateNormal();
}

/**************************************************************
 *
 *  destructor for Face class
 *
 *************************************************************/
Face::~Face()
{
  delete[] _indexPts;
}

/**************************************************************
 *
 *  draw the face in the openGL context
 *
 *************************************************************/
void
Face::render()
{
  std::vector<gml::Point3D> tpoints = *_points;
  std::vector<gml::Vector3D> & tnormals = *_normals;
  
  glColor3f(1.0, 0.0, 0.0);
  
  glBegin(GL_POLYGON);

  glNormal3f( _normal[0], _normal[1], _normal[2]);
  
  for (int i=0; i< _numberOfPts; i++)
  {
    
    glNormal3f(tnormals[i][0], tnormals[i][1], tnormals[i][2]);

    glVertex3d(tpoints[_indexPts[i]][0],
               tpoints[_indexPts[i]][1],
               tpoints[_indexPts[i]][2]);
  }
  glEnd();
}

/**************************************************************
 *
 *  draw the normals of the face
 *
 *************************************************************/
void
Face::renderNormal()
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
 *  draw the face in the openGL context with the normals
 *
 *************************************************************/
void
Face::renderWithNormal()
{
  render();
  renderNormal();
}

/**************************************************************
 *
 *  define if the face contains a vertex
 *  @param vertexIndex the index of the vertex
 *  @return true if the quad contains the vertex, false else
 *
 *************************************************************/
bool
Face::containVertex(int vertexIndex) const
{
  for (int i=0; i<_numberOfPts; i++)
  {
    if (_indexPts[i] == vertexIndex)
    {
      return true;
    }
  }

  return false;
}

/**************************************************************
 *
 *  returns all the indexes of the face
 *  @return a vector of indexes
 *
 *************************************************************/
std::vector<int>*
Face::getIndexes()
{
  
  std::vector<int> *indices;
  indices = new std::vector<int>;

  for(int i=0; i< _numberOfPts; i++)
  {
    indices->push_back(_indexPts[i]);
  }
  
  return indices;
}

/**************************************************************
 *
 *  redefine the display stream operator for debug
 *
 *************************************************************/
std::ostream&
operator<<(std::ostream& os, Face const& f)
{

  os << "Face [ " ;

  for (int i=0; i<f._numberOfPts; i++)
  {
    os << f._indexPts[i] << ", " ;
  }

  os << " ] " << std::endl;
  return os;
}



// WARNING : this a naive way to compute the normal for a polygon with n
// segments. Here he fully suppose the polygon is planar. Obviously this is not
// the general case.

//TODO: a possible way to compute this normal would be to triangulate the polygon
// and compute the normal for each triangle and take the average normal of thoses
// triangles

/**************************************************************
 *
 *  update the normals of the face
 *
 *************************************************************/
void
Face::updateNormal()
{
  double mx, my, mz;
  
  std::vector<gml::Point3D> tpoints = *_points;

  mx = 0.0;
  my = 0.0;
  mz = 0.0;
  
  for (int i=0; i< _numberOfPts; i++)
  {
    mx += tpoints[i][0];
    my += tpoints[i][1];
    mz += tpoints[i][2];
  }

  mx = mx / _numberOfPts;
  my = my / _numberOfPts;
  mz = mz / _numberOfPts;

  _center[0] = mx; _center[1] = my; _center[2] = mz;

  gml::Vector3D v1 = tpoints[1] -  tpoints[0];
  gml::Vector3D v2 = tpoints[2] -  tpoints[0];

  _normal = cross(v1, v2);
  _normal.normalize();
  
  _n1[0] = _normal[0] + _center[0];
  _n1[1] = _normal[1] + _center[1];
  _n1[2] = _normal[2] + _center[2];


}


