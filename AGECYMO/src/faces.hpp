#ifndef CLASS_FACES_H
#define CLASS_FACES_H

#include <vector>

#include "qgl.h"

#include "absface.hpp"
#include "tria.hpp"
#include "quad.hpp"

#include "point.hpp"

class Faces
{
  private:
  
  int _nbPoints;
  int _nbFaces;

  //Information about the model 
  int _nbTriangles;
  int _nbQuads;
  int _nbOthers;
  
  
  std::vector<gml::Point3D> *_points; //All points
  std::vector<AbsFace*>      *_faces; // Each face indexes its points

  //Points to define the bounding box
  gml::Point3D              _min;
  gml::Point3D              _max;
    
  public:
  Faces(std::vector<gml::Point3D> *points,
        std::vector<AbsFace*> *faces);

  ~Faces();
  
  void render() const;

  void renderWithNormal() const;

  void renderNormals() const;
  
  
  void renderBoundingBox() const;

  
  std::vector<gml::Point3D> const & points();

  std::vector<AbsFace*> const & faces();
  
  

  friend std::ostream& operator<<(std::ostream& os, Faces const& f);  


  private:

  void updateBoundingBox();

  void updateDataInfo();
  
  
};


#endif
