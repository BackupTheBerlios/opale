#include "renderer.hpp"


Renderer::Renderer()
    :  _renderMode(WF)
{
  _faces = NULL;
  
  std::vector<gml::Point3D>* mypoints = new std::vector<gml::Point3D>();

  std::vector<AbsFace*>* myfaces = new std::vector<AbsFace*>();

  gml::Point3D p1, p2, p3, p4, p5;
  p1[0] = 1;  p1[1] = 0.0; p1[2] = 0.0;
  p2[0] = 0.0;  p2[1] = 1; p2[2] = 0.0;
  p3[0] = -1; p3[1] = 0.0; p3[2] = 0.0;
  p4[0] = -1; p4[1] = 0.0; p4[2] = 1;
  p5[0] = 1; p5[1] = 0.0; p5[2] = 1;
  
  mypoints->push_back(p1);
  mypoints->push_back(p2);
  mypoints->push_back(p3);
  mypoints->push_back(p4);
  mypoints->push_back(p5);
  
  myfaces->push_back( new Tria(mypoints) );
  myfaces->push_back( new Quad(mypoints, 0, 2, 3, 4) );
  
  Faces* thefaces = new Faces(mypoints, myfaces);

  setModel(*thefaces);  
}

Renderer::~Renderer()
{
  //TODO: should we delete the faces????
  delete _faces;
}

void
Renderer::render()
{
  
  assert(_faces != NULL);



  
  
  switch(_renderMode)
  {
    case WF:
    {
      glPolygonMode(GL_FRONT, GL_LINE);
      break;
    }

    case FLAT:
    {
      glPolygonMode(GL_FRONT, GL_FILL);
      break;
    }
    
    default:
    {
      glPolygonMode(GL_FRONT, GL_FILL);
      break;
    }
  }
    
  _faces->render();
    
}

void
Renderer::setModel(Faces & faces)
{
  if (_faces != NULL)
  {
    delete _faces;
  }
  _faces = &faces;
}

Faces&
Renderer::model()
{
  return *(_faces);
}


void
Renderer::setRenderMode(RenderMode r)
{
  _renderMode = r;
}
