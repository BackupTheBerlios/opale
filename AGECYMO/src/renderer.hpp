#ifndef  CLASS_RENDERER_H
#define CLASS_RENDERER_H

#include <vector>

#include "qgl.h"

#include "tria.hpp"
#include "quad.hpp"
#include "faces.hpp"


class Renderer
{
  
  public:
  enum RenderMode
  {
    WF, //wireframe
    FLAT, //no shading
    GOURAUD, //gouraud shading
    WF_HDLR, //Wireframe with hidden line removal
  };
  
  private:
  Faces * _faces;

  RenderMode _renderMode;
  
  public:
  Renderer();
  ~Renderer();

  void setModel(Faces & faces);

  Faces& model();
  
  void render();

  void setRenderMode(RenderMode r);
  
  
};



#endif
