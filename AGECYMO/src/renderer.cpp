#include "renderer.hpp"


Renderer::Renderer()
{
  _faces = NULL;

  //setFaces(thefaces);
}

Renderer::~Renderer()
{
  //TODO: should we delete the faces????
}

void
Renderer::render()
{
  
  std::vector<gml::Point3D> mypoints;
  std::vector<AbsFace*> myfaces;

  gml::Point3D p1, p2, p3, p4, p5;
  p1[0] = 0.10;  p1[1] = 0.0; p1[2] = 0.0;
  p2[0] = 0.0;  p2[1] = 0.10; p2[2] = 0.0;
  p3[0] = -0.10; p3[1] = 0.0; p3[2] = 0.0;
  p4[0] = -0.10; p4[1] = 0.0; p4[2] = 0.10;
  p5[0] = 0.10; p5[1] = 0.0; p5[2] = 0.10;
  
  mypoints.push_back(p1);
  mypoints.push_back(p2);
  mypoints.push_back(p3);
  mypoints.push_back(p4);
  mypoints.push_back(p5);
  
  myfaces.push_back( new Tria(&mypoints) );
  myfaces.push_back( new Quad(&mypoints, 0, 2, 3, 4) );
  
  Faces thefaces(mypoints, &myfaces);

  setModel(thefaces);
    
  assert(_faces != NULL);
    
  glPolygonMode(GL_FRONT, GL_FILL);
  
  _faces->render();
  //thefaces.render();
  
  
}

void
Renderer::setModel(Faces & faces)
{
  _faces = &faces;
}

Faces&
Renderer::model()
{
  return *(_faces);
}
