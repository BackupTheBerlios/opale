#ifndef CLASS_ABSFACE_H
#define CLASS_ABSFACE_H

#include <vector>
#include <iostream>

#include "point.hpp"

class AbsFace
{
  protected:
  
  std::vector<gml::Point3D> *_points;
  //gml::Point3D *_points;
  
  public:

  AbsFace(std::vector<gml::Point3D> *points);
  AbsFace(AbsFace const & f1);
  
  virtual ~AbsFace();

  // void setPoints(gml::Point3D * pts);
  void setPoints(std::vector<gml::Point3D> * pts);
  
  
  virtual void render() = 0;
  
//   {
//     std::cout << "render de absface" << std::endl;
//   }
  

  AbsFace& operator=(AbsFace const& f2);

  friend std::ostream& operator<<(std::ostream& os, AbsFace const& f);

  
};

#endif
