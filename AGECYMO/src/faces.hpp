#ifndef CLASS_FACES_H
#define CLASS_FACES_H

#include <vector>

#include "absface.hpp"
#include "tria.hpp"
#include "point.hpp"

class Faces
{
  private:
  
  int _nbPoints;
  int _nbFaces;

  std::vector<gml::Point3D> *_points; //All points
  std::vector<AbsFace*>      *_faces; // Each face indexes its points
    
  public:
  Faces(std::vector<gml::Point3D> *points,
        std::vector<AbsFace*> *faces);

  ~Faces();
  
  void render() const;


  std::vector<gml::Point3D> const & points();

  std::vector<AbsFace*> const & faces();
  
  

  friend std::ostream& operator<<(std::ostream& os, Faces const& f);  
  
};


#endif
