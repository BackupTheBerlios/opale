#ifndef CLASS_QUAD_H
#define CLASS_QUAD_H

#include "qgl.h"
#include "absface.hpp"

/**************************************************************
 *
 *  derived class from AbsFace in order to stock a quad
 *
 *************************************************************/
class Quad : public AbsFace
{
  private:
  int _i1; /**indexe 1*/
  int _i2; /**indexe 2*/
  int _i3; /**indexe 3*/
  int _i4; /**indexe 4*/

  public:

  /**************************************************************
   *
   *  constructor for Quad class
   *  @param points a vector of points used in the quad
   *  @param i1 the first index of the quad
   *  @param i2 the second index of the quad
   *  @param i3 the third index of the quad
   *  @param i4 the fourth index of the quad
   *
   *************************************************************/
  Quad(std::vector<gml::Point3D> *points,
       int i1 = 0, int i2 =1,
       int i3 = 2, int i4 = 3);

  /**************************************************************
   *
   *  draw the quad in the openGL context
   *
   *************************************************************/
  void render();

  /**************************************************************
   *
   *  draw the normals of the quad
   *
   *************************************************************/
  void renderNormal();
  
  /**************************************************************
   *
   *  draw the quad in the openGL context with the normals
   *
   *************************************************************/
  void renderWithNormal();

  /**************************************************************
   *
   *  update the normals of the quad
   *
   *************************************************************/
  void updateNormal();

  /**************************************************************
   *
   *  define if the quad contains a vertex
   *  @param vertexIndex the index of the vertex
   *  @return true if the quad contains the vertex, false else
   *
   *************************************************************/
  bool containVertex(int vertexIndex) const;
  
  /**************************************************************
   *
   *  returns all the indexes of the quad
   *  @return a vector of indexes
   *
   *************************************************************/
  virtual std::vector<int> *getIndexes();
  
  /**************************************************************
   *
   *  redefine the display stream operator for debug
   *
   *************************************************************/
  friend std::ostream& operator<<(std::ostream& os, Quad const& q);
};

#endif
