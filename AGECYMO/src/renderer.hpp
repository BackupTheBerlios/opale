#ifndef  CLASS_RENDERER_H
#define CLASS_RENDERER_H

#include <vector>
#include "qgl.h"
#include "tria.hpp"
#include "quad.hpp"
#include "faces.hpp"


/**************************************************************
 *
 *  in order to render the model
 *
 *************************************************************/
class Renderer
{
  /**the type of rendering*/
  public:
  enum RenderMode
  {
    WF, /**wireframe rendering*/
    FLAT, /**falt rendering*/
    GOURAUD, /**gouraud rendering*/
    WF_HDLR, /**Wireframe with hidden line removal*/
  };
  
  private:

  Faces * _faces; /**the faces to be rendered*/
  RenderMode _renderMode; /**the render mode*/
  GLint _currentDPL; /**the current DPL*/
  GLint _modelWireFrameDPL; /**model display list withOUT normals being displayed*/
  
  GLint _modelFillDPL; /**model display list with fill mode*/

  GLint _modelNormalsDPL; /**model's normals.*/
  

  GLint _boundingBoxDPL; /**bounding box of the model Display List*/

  
  public:

  /**************************************************************
   *
   *  constructor for Renderer class
   *
   *************************************************************/
  Renderer();

  /**************************************************************
   *
   *  destructor for Renderer class
   *
   *************************************************************/
  ~Renderer();

  /**************************************************************
   *
   *  initiliaze the display lists ID
   *
   *************************************************************/
  void initDPL();
  
  /**************************************************************
   *
   *  rebuild the display lists this is needed when the model 
   *  to be rendered is changed.
   *
   *************************************************************/
  void rebuildDPL(); 
                      
  /**************************************************************
   *
   *  set the model
   *  @param faces the faces
   *
   *************************************************************/
  void setModel(Faces & faces);

  /**************************************************************
   *
   *  get the model
   *  @return the faces
   *
   *************************************************************/
  Faces& model();

  //Rendering methods

  /**************************************************************
   *
   *  render the model
   *
   *************************************************************/
  void render();

  /**************************************************************
   *
   *  render the bounding box
   *
   *************************************************************/
  void renderBoundingBox();

  /**************************************************************
   *
   *  render the normals
   *
   *************************************************************/
  void renderNormals();
  
  /**************************************************************
   *
   *  set the rendering mode
   *  @param r the rendering mode
   *
   *************************************************************/
  void setRenderMode(RenderMode r);

  /**************************************************************
   *
   *  get the rendering mode 
   *  @return the rendering mode
   *
   *************************************************************/
  int renderMode() const;
  
  private:

  /**************************************************************
   *
   *  update the cureent DPL (displayList)
   *
   *************************************************************/
  void updateCurrentDPL();

  /**************************************************************
   *
   *  delete the display lists
   *
   *************************************************************/
  void deleteDisplayLists();
  
};



#endif
