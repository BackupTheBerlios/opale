#include "faces.hpp"
#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <qmessagebox.h> 

using namespace std;

#define TOLERANCE 0.0

/**************************************************************
 *
 *  constructor for Faces class
 *  @param points the points used in the faces
 *  @param faces the vector of faces
 *
 *************************************************************/
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

/**************************************************************
 *
 *  destructor for Faces class
 *
 *************************************************************/
Faces::~Faces()
{
  qDebug("Faces : DESTRUCTOR");
  
  delete _faces;
  delete _points;

  qDebug("END of destructor ");
}

/**************************************************************
 *
 *  draw the faces in the openGL context
 *
 *************************************************************/
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

/**************************************************************
 *
 *  draw the face in the openGL context with the normals
 *
 *************************************************************/
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


/**************************************************************
 *
 *  draw the normals of the faces
 *
 *************************************************************/
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

/**************************************************************
 *
 *  draw the bounding box of the entiere object
 *
 *************************************************************/
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


/**************************************************************
 *
 *  get all the points
 *  @return a vector of points
 *
 *************************************************************/
std::vector<gml::Point3D> const &
Faces::points()
{
  return *_points;
}

/**************************************************************
 *
 *  get all the faces
 *  @return a vector of AbsFace
 *
 *************************************************************/
std::vector<AbsFace*> const &
Faces::faces()
{
  return *_faces;
}

/**************************************************************
 *
 *  get the number of vertices
 *  @return the number of vertices
 *
 *************************************************************/
int
Faces::numberOfVertex() const
{
  return _nbPoints;
}

/**************************************************************
 *
 *  get the number of triangles
 *  @return the number of triangles
 *
 *************************************************************/
int
Faces::numberOfTriangles() const
{
  return _nbTriangles;
}

/**************************************************************
 *
 *  get the number of quads
 *  @return the number of quads
 *
 *************************************************************/
int
Faces::numberOfQuads() const
{
  return _nbQuads;
}

/**************************************************************
 *
 *  get the numbers of the others faces types
 *  @return the numbers of the others faces types
 *
 *************************************************************/
int
Faces::numberOfOthers() const
{
  return _nbOthers;
}



int
Faces::numberOfFaces() const
{
  return _faces->size();
}



/**************************************************************
 *
 *  redefine the display stream operator for debug
 *
 *************************************************************/
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

  
/**************************************************************
 *
 *  update the bounding box
 *
 *************************************************************/
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

/**************************************************************
 *
 *  update data infos about faces
 *
 *************************************************************/
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

/**************************************************************
 *
 *  update all the normals
 *
 *************************************************************/
void
Faces::updateVertexNormals()
{
  qDebug("FACES : BEGINNING  updateVertexNormal ");

  std::vector<gml::Vector3D> currentNormals;

  std::vector<AbsFace*> lesfaces  = *_faces;

  _normals.reserve( _points->size() );
  
  
  for (unsigned int i=0; i < _points->size(); i++)
  {
    
    for (unsigned int j=0; j<_faces->size(); j++)
    {
      
      if ( (lesfaces[j])->containVertex(i) )
      {
        currentNormals.push_back( lesfaces[j]->normal() );
      }
    }
    
    _normals[i] = computeAverageNormal( currentNormals );

    currentNormals.clear();

  }

  
  for (unsigned int j=0; j < _faces->size(); j++)
  {
    lesfaces[j]->setNormals( &_normals);
  }
  
  qDebug("FACES : end of updateVertexNormal ");
}

/**************************************************************
 *
 *  compute the average of normals
 *  @param normals the vactor of the normals
 *  @return the average of the normals
 *
 *************************************************************/
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


void
Faces::validModel() const{
  
  std::vector< std::vector<gml::Point3D> > edges; 
  int nbEdges;

  int nbVerif = 0;
  int nbValid = 0;
  int nbNotValid = 0;

  ostringstream oss1;
  ostringstream oss2;
  ostringstream oss3;

  // Verification if there is not edges intersection
  for (int i=0 ; i<(int)(*_faces).size() ; i++) {
    for (int j=0 ; j<(int)(*(*_faces)[i]->getIndexes()).size() ; j++) {

      std::vector <gml::Point3D> temp;
      temp.push_back((*_points)[(*(*_faces)[i]->getIndexes())[j]]);

      if (j+1 == (int)(*(*_faces)[i]->getIndexes()).size()) {
	temp.push_back((*_points)[(*(*_faces)[i]->getIndexes())[0]]);
      }
      else {
	temp.push_back((*_points)[(*(*_faces)[i]->getIndexes())[j+1]]);
      }
      edges.push_back(temp);
    }
  }

  for (int i=0 ; i<(int)edges.size() ; i++) {
    for (int j=i+1 ; j<(int)edges.size() ; j++) {
      std::vector <gml::Point3D> temp;
      temp.push_back(edges[i][1]);
      temp.push_back(edges[j][0]);
      temp.push_back(edges[j][1]);
      nbVerif++;
      double t1, t2;
      int value = edges[i][0].inter(temp, &t1, &t2, TOLERANCE);
      if (value == 1) {
	if (((t1 > -TOLERANCE && t1 < TOLERANCE) || (t1 > 1.0-TOLERANCE && t1 < 1.0+TOLERANCE)) && ((t2 > -TOLERANCE && t2 < TOLERANCE) || (t2 > 1.0-TOLERANCE && t2 < 1.0+TOLERANCE))) {
	  nbValid ++;
	}
	else {
	  nbNotValid++;
	}
      }
      else {
	nbValid++;
      }
    }
  }

  
  oss1 << "Number of edges : " << edges.size() << endl << "Number of verifications : " << nbVerif << endl << "Number of valid intersections : " << nbValid << endl << "Number of not valid intersections : " << nbNotValid << endl;
  
  QMessageBox::information(0, "Validation 1 :", oss1.str());

  nbVerif = 0;
  nbValid = 0;
  nbNotValid = 0;
	

  // Verification if each faces are in the same plane
  for (int i=0 ; i<(int)(*_faces).size() ; i++) {

    nbVerif++;

    gml::Point3D firstPoint = (*_points)[(*(*_faces)[i]->getIndexes())[0]];

    // The verification is necessary only if the face owns more of three points
    if ((int)(*(*_faces)[i]->getIndexes()).size() > 3) {
      
      std::vector <gml::Point3D> temp;

      for (int j=1 ; j<(int)(*(*_faces)[i]->getIndexes()).size() ; j++) {
	temp.push_back((*_points)[(*(*_faces)[i]->getIndexes())[j]]);
      }
      
      if (!firstPoint.onPlane(temp, TOLERANCE)) {
	nbNotValid++;
      }
      else {
	nbValid++;
      }
      
    }
    else {
      nbValid++;
    }
  }

  
  
  oss2 << "Number of faces : " << (*_faces).size() << endl << "Number of verifications : " << nbVerif << endl << "Number of valid faces : " << nbValid << endl << "Number of not valid faces : " << nbNotValid << endl;

  QMessageBox::information(0, "Validation 2 :", oss2.str());


  nbVerif = 0;
  nbValid = 0;
  nbNotValid = 0;




  // Verification if each edge doesn't cut a face
  for (int i=0 ; i<(int)edges.size() ; i++) {
    for (int j=0 ; j<(int)(*_faces).size() ; j++) {
      std::vector <gml::Point3D> temp;
      nbVerif++;
      for (int k=0 ; k<(int)(*(*_faces)[j]->getIndexes()).size() ; k++) {
	temp.push_back((*_points)[(*(*_faces)[j]->getIndexes())[k]]);
      }
      double t;
      

      if (edges[i][0].interPlan(edges[i][1], temp, &t, TOLERANCE)) {
	if (((t > -TOLERANCE && t < TOLERANCE) || (t > 1.0-TOLERANCE && t < 1.0+TOLERANCE))) {
	  nbValid ++;
	}
	else {
	  nbNotValid++;
	}
      }
      else {
	nbValid++;
      }
    }
  }

  oss3 << "Number of faces : " << (*_faces).size() << endl << "Number of edges : " << edges.size() << endl << "Number of verifications : " << nbVerif << endl << "Number of valid faces : " << nbValid << endl << "Number of not valid faces : " << nbNotValid << endl;

   QMessageBox::information(0, "Validation 3 :", oss3.str());
  
}
