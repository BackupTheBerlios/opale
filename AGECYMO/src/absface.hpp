#ifndef CLASS_ABSFACE_H
#define CLASS_ABSFACE_H

#include <vector>
#include <iostream>
#include "point.hpp"

/**************************************************************
 *
 *  generic class for all types of faces
 *
 *************************************************************/
class AbsFace
{
  protected:
  
  std::vector<gml::Point3D> *_points; /**pointer to the point coordinates*/  
  std::vector<gml::Vector3D> *_normals; /**pointer to the normal  coordinates*/
  
  gml::Vector3D _normal; /**normal of the face NOT the vertex normal*/
  gml::Point3D _n1; /**n1 - center = normalized normal of the triangle*/
  gml::Point3D _center; /**center*/
  
  public:

  /**************************************************************
   *
   *  constructor for AbsFace class
   *  @param points a vector of points used in the face
   *
   *************************************************************/
  AbsFace(std::vector<gml::Point3D> *points);

  /**************************************************************
   *
   *  copy constructor for AbsFace class
   *  @param t1 another Tria
   *
   *************************************************************/
  AbsFace(AbsFace const & f1);
  
  /**************************************************************
   *
   *  destructor for AbsFace 
   *
   *************************************************************/
  virtual ~AbsFace();

  /**************************************************************
   *
   *  set points of the face
   *  @param pts a vector of points
   *
   *************************************************************/
  void setPoints(std::vector<gml::Point3D> * pts);
  
  /**************************************************************
   *
   *  draw the face in an openGL context
   *
   *************************************************************/
  virtual void render() = 0;

  /**************************************************************
   *
   *  draw the face in an openGL context with normals
   *
   *************************************************************/
  virtual void renderWithNormal() = 0;

  /**************************************************************
   *
   *  draw the normals in an opneGL context
   *
   *************************************************************/
  virtual void renderNormal() = 0;
  
  /**************************************************************
   *
   *  get the indexex of the face
   *  @return a vector of indexes
   *
   *************************************************************/
  virtual std::vector<int> *getIndexes()=0;

  /**************************************************************
   *
   *  define if the face contains a vertex
   *  @param vertexIndex the index of the vertex
   *  @return true if the face contains the vertex, false else
   *
   *************************************************************/
  virtual bool containVertex(int vertexIndex) const = 0;  

  /**************************************************************
   *
   *  get the normal
   *  @return the normal of the face
   *
   *************************************************************/
  gml::Vector3D normal() const;

  /**************************************************************
   *
   *  set the normal of the face per vertex
   *  @param the vector of normals
   *
   *************************************************************/
  void setNormals(std::vector<gml::Vector3D> * anormals);
  
  /**************************************************************
   *
   *  define the equal operator
   *
   *************************************************************/
  AbsFace& operator=(AbsFace const& f2);

  /**************************************************************
   *
   *  define the display operator
   *
   *************************************************************/
  friend std::ostream& operator<<(std::ostream& os, AbsFace const& f);
    
};

#endif
