#ifndef CLASS_FACES_H
#define CLASS_FACES_H

#include <vector>
#include "qgl.h"
#include "absface.hpp"
#include "tria.hpp"
#include "quad.hpp"
#include "point.hpp"
#include "vector.hpp"

/**************************************************************
 *
 *  stocks all the faces 
 *
 *************************************************************/
class Faces
{
  private:
  
  int _nbPoints; /**the number of points*/
  int _nbFaces;  /**the number of faces*/
  //Information about the model 
  int _nbTriangles; /**the number of triangles*/
  int _nbQuads;     /**the number of quads*/
  int _nbOthers;    /**the number of other face types*/
  std::vector<gml::Point3D> *_points; /**all vertices*/
  std::vector<AbsFace*>      *_faces; /**Each face indexes its points*/
  std::vector<gml::Vector3D> _normals; /**All vertices' normal*/
  gml::Point3D              _min; /**min for bounding box*/
  gml::Point3D              _max; /**max for bounding box*/
    
  public:


  /**************************************************************
   *
   *  constructor for Faces class
   *  @param points the points used in the faces
   *  @param faces the vector of faces
   *
   *************************************************************/
  Faces(std::vector<gml::Point3D> *points,
        std::vector<AbsFace*> *faces);

  /**************************************************************
   *
   *  destructor for Faces class
   *
   *************************************************************/
  ~Faces();

  /**************************************************************
   *
   *  draw the faces in the openGL context
   *
   *************************************************************/
  void render() const;

  /**************************************************************
   *
   *  draw the face in the openGL context with the normals
   *
   *************************************************************/
  void renderWithNormal() const;

  /**************************************************************
   *
   *  draw the normals of the faces
   *
   *************************************************************/
  void renderNormals() const;
  
  /**************************************************************
   *
   *  draw the bounding box of the entiere object
   *
   *************************************************************/
  void renderBoundingBox() const;


//  void validModel() const;

  //accessors


  /**************************************************************
   *
   *  get all the points
   *  @return a vector of points
   *
   *************************************************************/
  std::vector<gml::Point3D> const & points();

  /**************************************************************
   *
   *  get all the faces
   *  @return a vector of AbsFace
   *
   *************************************************************/
  std::vector<AbsFace*> const & faces();

  //accessors to obtain specific information

  /**************************************************************
   *
   *  get the number of vertices
   *  @return the number of vertices
   *
   *************************************************************/
  int numberOfVertex()    const;
  
  /**************************************************************
   *
   *  get the number of triangles
   *  @return the number of triangles
   *
   *************************************************************/
  int numberOfTriangles() const;

  /**************************************************************
   *
   *  get the number of quads
   *  @return the number of quads
   *
   *************************************************************/
  int numberOfQuads()     const;

  /**************************************************************
   *
   *  get the numbers of the others faces types
   *  @return the numbers of the others faces types
   *
   *************************************************************/
  int numberOfOthers()   const;

  int numberOfFaces()    const;
  
  /**************************************************************
   *
   *  redefine the display stream operator for debug
   *
   *************************************************************/
  friend std::ostream& operator<<(std::ostream& os, Faces const& f);  


  private:

  /**************************************************************
   *
   *  update the bounding box
   *
   *************************************************************/
  void updateBoundingBox();

  /**************************************************************
   *
   *  update data infos about faces
   *
   *************************************************************/
  void updateDataInfo();

  /**************************************************************
   *
   *  update all the normals
   *
   *************************************************************/
  void updateVertexNormals();
  
  /**************************************************************
   *
   *  compute the average of normals
   *  @param normals the vactor of the normals
   *  @return the average of the normals
   *
   *************************************************************/
  gml::Vector3D computeAverageNormal(const std::vector<gml::Vector3D> & normals);
  
  
};


#endif
