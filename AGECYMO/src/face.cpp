#include "face.hpp"


Face::Face(std::vector<int> indexes,
           std::vector<gml::Point3D> *points,
           int numberOfPoints)
    : AbsFace(points),
      _numberOfPts(numberOfPoints)
{
  _indexPts = new int[numberOfPoints];

  for (int i=0; i<numberOfPoints; i++)
  {
    _indexPts[i] = indexes[i];
  }

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
