#ifndef CLASS_FACES_H
#define CLASS_FACES_H

#include <vector>

#include "qgl.h"


#include "absface.hpp"
#include "tria.hpp"
#include "quad.hpp"

#include "point.hpp"
#include "vector.hpp"

class Faces
{
  private:
  
  int _nbPoints;
  int _nbFaces;

  //Information about the model 
  int _nbTriangles;
  int _nbQuads;
  int _nbOthers;
  
  
  std::vector<gml::Point3D> *_points; //All vertices
  std::vector<AbsFace*>      *_faces; // Each face indexes its points

  std::vector<gml::Vector3D> _normals; //All vertices' normal

  
  //Points to define the bounding box
  gml::Point3D              _min;
  gml::Point3D              _max;
    
  public:
  Faces(std::vector<gml::Point3D> *points,
        std::vector<AbsFace*> *faces);

  ~Faces();

  //rendering methods
  void render() const;

  void renderWithNormal() const;

  void renderNormals() const;
  
  void renderBoundingBox() const;

  //accessors
  std::vector<gml::Point3D> const & points();

  std::vector<AbsFace*> const & faces();

  //accessors to obtain specific information
  int numberOfVertex()    const;
  int numberOfTriangles() const;
  int numberOfQuads()     const;
  int numberOfOthers()   const;
  
  

  friend std::ostream& operator<<(std::ostream& os, Faces const& f);  


  private:

  void updateBoundingBox();

  void updateDataInfo();

  //use to compute each vertex normal
  void updateVertexNormals();
  
  gml::Vector3D computeAverageNormal(const std::vector<gml::Vector3D> & normals);
  
  
};


#endif
