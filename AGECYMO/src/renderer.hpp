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
  
  GLint _currentDPL;
  
  GLint _modelWireFrameDPL; //model display list withOUT normals being displayed
  
  GLint _modelFillDPL; //model display list with fill mode

  GLint _modelNormalsDPL; // model's normals.
  

  GLint _boundingBoxDPL; //bounding box of the model Display List

  
  public:
  Renderer();
  ~Renderer();


  void initDPL(); //initiliaze the display lists ID

  //maybe private
  void rebuildDPL(); // rebuild the display lists this is needed when
                     // the model to be rendered is changed.
  
  
  void setModel(Faces & faces);

  Faces& model();

  //Rendering methods
  void render();
  void renderBoundingBox();
  void renderNormals();
  
  
  void setRenderMode(RenderMode r);

  int renderMode() const;
  
  private:

  void updateCurrentDPL();

  void deleteDisplayLists();
  
};



#endif
