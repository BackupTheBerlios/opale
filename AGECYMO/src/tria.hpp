#ifndef CLASS_TRIA_H
#define CLASS_TRIA_H

#include "qgl.h"

#include "absface.hpp"

/**************************************************************
 *
 *  derived class from AbsFace in order to stock a triangle
 *
 *************************************************************/
class Tria : public AbsFace
{
  private:
  int _i1; /**indexe 1*/
  int _i2; /**indexe 2*/
  int _i3; /**indexe 3*/  
  
  public:

  /**************************************************************
   *
   *  constructor for Tria class
   *  @param points a vector of points used in the quad
   *  @param i1 the first index of the quad
   *  @param i2 the second index of the quad
   *  @param i3 the third index of the quad
   *
   *************************************************************/
  Tria(std::vector<gml::Point3D> *points, int i1 = 0, int i2 = 1, int i3= 2);

  /**************************************************************
   *
   *  copy constructor for Tria class
   *  @param t1 another Tria
   *
   *************************************************************/
  Tria(Tria const & t1);

  /**************************************************************
   *
   *  draw the triangle in the openGL context
   *
   *************************************************************/
  void render();

  /**************************************************************
   *
   *  draw the normals of the triangle
   *
   *************************************************************/
  void renderNormal();

  /**************************************************************
   *
   *  draw the triangle in the openGL context with the normals
   *
   *************************************************************/
  void renderWithNormal();
  
  /**************************************************************
   *
   *  define if the triangle contains a vertex
   *  @param vertexIndex the index of the vertex
   *  @return true if the quad contains the vertex, false else
   *
   *************************************************************/
  bool containVertex(int vertexIndex) const;
  
  /**************************************************************
   *
   *  returns all the indexes of the triangle
   *  @return a vector of indexes
   *
   *************************************************************/
  std::vector<int> *Tria::getIndexes();

  /**************************************************************
   *
   *  define the equal operator for Tria
   *
   *************************************************************/
  Tria& operator=(Tria const & t1);

  /**************************************************************
   *
   *  update the normals of the triangle
   *
   *************************************************************/
  void updateNormal();
  
  
  /**************************************************************
   *
   *  redefine the display stream operator for debug
   *
   *************************************************************/
  friend std::ostream& operator<<(std::ostream& os, Tria const& t);
};


#endif
