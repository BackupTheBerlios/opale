#include "face.hpp"


Face::Face(std::vector<gml::Point3D> *points, int numberOfPoints)
    : AbsFace(points),
      _numberOfPts(numberOfPoints)
{
  _indexPts = new int[numberOfPoints];
  
}

Face::~Face()
{
  delete[] _indexPts;
}

void
Face::render()
{
  std::vector<gml::Point3D> tpoints = *_points;

  glBegin(GL_POLYGON);

  for (int i=0; i< _numberOfPts; i++)
  {
    glVertex3d(tpoints[_indexPts[i]][0],
               tpoints[_indexPts[i]][1],
               tpoints[_indexPts[i]][2]);
  }
  glEnd();
  

}



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



