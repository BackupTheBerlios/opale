#include "faces.hpp"
#include <exception>
#include <iostream>
#include <cstdlib>

Faces::Faces(std::vector<gml::Point3D> *points,
             std::vector<AbsFace*> *faces)
    : _nbPoints(points->size()),
      _nbFaces((*faces).size()),
      _nbTriangles(0),
      _nbQuads(0),
      _nbOthers(0),
      _points(points),
      _faces(faces)
  
{
  updateBoundingBox();
  updateDataInfo();
  updateVertexNormals();
}


Faces::~Faces()
{
  qDebug("Faces : DESTRUCTOR");
  
  delete _faces;
  delete _points;
}


void
Faces::render() const
{
  std::vector<AbsFace*> faces = *_faces;
  std::vector<AbsFace*>::iterator i;  

  for(i = faces.begin(); i != faces.end(); i++)
  {
    (*i)->render();
  }  
}


void
Faces::renderWithNormal() const
{
  std::vector<AbsFace*> faces = *_faces;
  std::vector<AbsFace*>::iterator i;  

  for(i = faces.begin(); i != faces.end(); i++)
  {
    (*i)->renderWithNormal();
  }  
}

void
Faces::renderNormals() const
{
  std::vector<AbsFace*> faces = *_faces;
  std::vector<AbsFace*>::iterator i;  

  for(i = faces.begin(); i != faces.end(); i++)
  {
    (*i)->renderNormal();
  }  
}

void
Faces::renderBoundingBox() const
{

  glColor3f(0.4, 0.4, 0.4);
  
  glBegin(GL_LINE_LOOP);
  glVertex3f ( _min[0], _min[1], _min[2] );
  glVertex3f ( _min[0], _min[1], _max[2] );
  glVertex3f ( _max[0], _min[1], _max[2] );
  glVertex3f ( _max[0], _min[1], _min[2] );
  glEnd();
  
  glBegin(GL_LINE_LOOP);
  glVertex3f ( _min[0], _max[1], _min[2] );
  glVertex3f ( _min[0], _max[1], _max[2] );
  glVertex3f ( _max[0], _max[1], _max[2] );
  glVertex3f ( _max[0], _max[1], _min[2] );
  glEnd();
  
  glBegin(GL_LINES);
  glVertex3f ( _min[0], _min[1], _min[2] );
  glVertex3f ( _min[0], _max[1], _min[2] );
  glEnd();
   
  glBegin(GL_LINES);
  glVertex3f ( _min[0], _min[1], _max[2] );
  glVertex3f ( _min[0], _max[1], _max[2] );
  glEnd();
   
  glBegin(GL_LINES);
  glVertex3f ( _max[0], _min[1], _max[2] );
  glVertex3f ( _max[0], _max[1], _max[2] );
  glEnd();
   
  glBegin(GL_LINES);
  glVertex3f ( _max[0], _min[1], _min[2] );
  glVertex3f ( _max[0], _max[1], _min[2] );
  glEnd();
  
}



std::vector<gml::Point3D> const &
Faces::points()
{
  return *_points;
}

std::vector<AbsFace*> const &
Faces::faces()
{
  return *_faces;
}


int
Faces::numberOfVertex() const
{
  return _nbPoints;
}

int
Faces::numberOfTriangles() const
{
  return _nbTriangles;
}

int
Faces::numberOfQuads() const
{
  return _nbQuads;
}

int
Faces::numberOfOthers() const
{
  return _nbOthers;
}


std::ostream&
operator<<(std::ostream& os, Faces const& f)
{
  os << "Model contains [ " << f._nbPoints << " points; " 
     << f._nbFaces << " faces ] " << std::endl
     << "Faces address : " << &f << std::endl
     << "Points : " << std::endl;
  
  
  std::vector<gml::Point3D> lespoints = *(f._points);

  //TODO: Change this and use iterators
  for (unsigned int i=0; i<f._points->size(); i++)
  {
    os << lespoints[i];
  }

  os << std::endl << "Faces : " << std::endl;
  
  std::vector<AbsFace*> lesfaces = *(f._faces);

  //TODO: Change this and use iterators
  for (unsigned int i=0; i<f._faces->size(); i++)
  {
    os << "Face " << i << " address : " << &lesfaces[i] << std::endl;
    os << *(lesfaces[i]);
  }
  
  return os;
    
}

  

void
Faces::updateBoundingBox()
{
  qDebug("\n DANS Faces updateBOundingBox \n");
  
  double currentX, currentY, currentZ;
  
  std::vector<gml::Point3D> lespoints = * (_points);
  
  double minX, minY, minZ;
  double maxX, maxY, maxZ;

  maxX = minX = lespoints[0][0];
  maxY = minY = lespoints[0][1];
  maxZ = minZ = lespoints[0][2];
  
  //TODO: Change this and use iterators
  for (unsigned int i=1; i< lespoints.size(); i++)
  {
    currentX = lespoints[i][0];
    currentY = lespoints[i][1];
    currentZ = lespoints[i][2];

    minX = (currentX < minX) ? (currentX) : (minX) ;
    maxX = (currentX > maxX) ? (currentX) : (maxX) ;
    
    minY = (currentY < minY) ? (currentY) : (minY) ;
    maxY = (currentY > maxY) ? (currentY) : (maxY) ;
    
    minZ = (currentZ < minZ) ? (currentZ) : (minZ) ;
    maxZ = (currentZ > maxZ) ? (currentZ) : (maxX) ;
  }

  _min[0] = minX;
  _min[1] = minY;
  _min[2] = minZ;

  _max[0] = maxX;
  _max[1] = maxY;
  _max[2] = maxZ;
    
}

void
Faces::updateDataInfo()
{  
  std::vector<AbsFace*> lesfaces = *(_faces);

  //TODO: Change this and use iterators
  for (unsigned int i=0; i<_faces->size(); i++)
  {

//     std::string type = typeid(*lesfaces[i]).name();
//     std::cout << type << std::endl;
//     qDebug("Type = %s \n", type.c_str());


    Tria* t = dynamic_cast<Tria *>(lesfaces[i]);

    if (t)
    {
      _nbTriangles++;
    }
    else
    {
      Quad* q = dynamic_cast<Quad *>(lesfaces[i]);
      if (q)
      {
        _nbQuads++;
      }
      else
      {
        _nbOthers++;
      }
    }
  }

  qDebug("Found %d triangles \n", _nbTriangles);
  qDebug("Found %d quads \n", _nbQuads);
  qDebug("Found %d other polygons \n", _nbOthers);
  
}

void
Faces::updateVertexNormals()
{
  qDebug("FACES : BEGINNING  updateVertexNormal ");

  std::vector<gml::Vector3D> currentNormals;

  std::vector<AbsFace*> lesfaces  = *_faces;

  _normals.reserve( _points->size() );
  
  
  for (unsigned int i=0; i < _points->size(); i++)
  {
    qDebug(" i  = %d", i);
    
    for (unsigned int j=0; j<_faces->size(); j++)
    {
      qDebug(" j  = %d", j);
      
      if ( (lesfaces[j])->containVertex(i) )
      {
        currentNormals.push_back( lesfaces[j]->normal() );
      }
    }
    
    _normals[i] = computeAverageNormal( currentNormals );

    currentNormals.clear();

  }

  qDebug("fin premiere bouvcle");
  
  
  for (unsigned int j=0; j < _faces->size(); j++)
  {
    lesfaces[j]->setNormals( &_normals);
  }

  qDebug("normals address is %p", &_normals);
  
  qDebug("FACES : end of updateVertexNormal ");
}

gml::Vector3D
Faces::computeAverageNormal(const std::vector<gml::Vector3D> & normals)
{
  gml::Vector3D result;

  double mx = 0.0;
  double my = 0.0;
  double mz = 0.0;

  for (unsigned int i=0; i<normals.size(); i++)
  {
    mx += normals[i][0];
    my += normals[i][1];
    mz += normals[i][2];
  }

  mx = mx / normals.size();
  my = my / normals.size();
  mz = mz / normals.size();

  result[0] = mx;
  result[1] = my;
  result[2] = mz;

  return result;
}
