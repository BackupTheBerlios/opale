#ifndef  CLASS_RENDERER_H
#define CLASS_RENDERER_H

#include <vector>

#include "qgl.h"

#include "tria.hpp"
#include "quad.hpp"
#include "faces.hpp"


class Renderer
{
  private:
  Faces * _faces;
  
  public:
  enum RenderMode {WF, GOURAUD};
  
  Renderer();
  ~Renderer();

  void setModel(Faces & faces);

  Faces& model();
  
  void render();
  
};



#endif
