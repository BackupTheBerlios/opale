#ifndef CLASS_FACE_H
#define CLASS_FACE_H

#include <iostream>
#include "qgl.h"
#include "absface.hpp"
#include "point.hpp"

/**************************************************************
 *
 *  derived class from AbsFace in order to stock a face
 *
 *************************************************************/
class Face : public AbsFace
{
  private:

  int _numberOfPts; /**the number of points in the face*/
  int* _indexPts;   /**the index points of the face*/  
  
  public:

  /**************************************************************
   *
   *  constructor for Face class
   *  @param indexes the indexes of the face
   *  @param points the points used in the face
   *  @param numberOfPoints the number of points in the face
   *
   *************************************************************/
  Face(std::vector<int> *indexes,
       std::vector<gml::Point3D> *points,
       int numberOfPoints = 5);

  /**************************************************************
   *
   *  destructor for Face class
   *
   *************************************************************/
  ~Face();

  /**************************************************************
   *
   *  define if the face contains a vertex
   *  @param vertexIndex the index of the vertex
   *  @return true if the quad contains the vertex, false else
   *
   *************************************************************/
  bool containVertex(int vertexIndex) const;
  
  /**************************************************************
   *
   *  returns all the indexes of the face
   *  @return a vector of indexes
   *
   *************************************************************/
  virtual std::vector<int> *getIndexes();

  /**************************************************************
   *
   *  draw the face in the openGL context
   *
   *************************************************************/
  void render();

  /**************************************************************
   *
   *  draw the normals of the face
   *
   *************************************************************/
  void renderNormal();
  
  /**************************************************************
   *
   *  draw the face in the openGL context with the normals
   *
   *************************************************************/
  void renderWithNormal();

  /**************************************************************
   *
   *  update the normals of the face
   *
   *************************************************************/
  void updateNormal();
    
  /**************************************************************
   *
   *  redefine the display stream operator for debug
   *
   *************************************************************/
  friend std::ostream& operator<<(std::ostream& os, Face const& f);
};



#endif
