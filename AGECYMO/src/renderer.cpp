#include "renderer.hpp"



Renderer::Renderer()
    :  _renderMode(WF)
{
  _faces = NULL;

  //all display lists set to 0
  _currentDPL = 0;
  _modelWireFrameDPL = 0;
  _modelFillDPL = 0;
  _modelNormalsDPL = 0;
  _boundingBoxDPL = 0;
}

Renderer::~Renderer()
{
  qDebug("RENDERER : DESTRUCTOR");

  //TODO : delete the DPL ?

  if (_faces != NULL)
  {
    delete _faces;
  }
  
}

void
Renderer::render()
{
  qDebug("\n RENDERER : render\n");
  
  assert(_faces != NULL);
  
  glCallList(_currentDPL);
  
  //_faces->render();
  //_faces->renderBoundingBox();
  
  qDebug("\n RENDERER : EXITING rendering \n");  
}

void
Renderer::renderBoundingBox()
{
  glCallList( _boundingBoxDPL );
}

void
Renderer::renderNormals()
{
  glCallList( _modelNormalsDPL );
}


void
Renderer::initDPL()
{
  
  std::vector<gml::Point3D>* mypoints = new std::vector<gml::Point3D>();

  std::vector<AbsFace*>* myfaces = new std::vector<AbsFace*>();

  //Construct a Basic Model to be displayed when nothing is loaded...
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

void
Renderer::rebuildDPL()
{

  qDebug("\n RENDERER Dans rebuildDPL \n ");
  
  _modelWireFrameDPL = glGenLists(1);

  if (_modelWireFrameDPL == 0)
  {
    qDebug("UNABLE TO BUILD A DISPLAY LIST for the MODEL !!!");
  }

  qDebug("\n DPL For MODEL = %d\n", _modelWireFrameDPL);
  
  glNewList(_modelWireFrameDPL, GL_COMPILE);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  qDebug("about to render faces = %p", _faces);
  _faces->render();
  glEndList();
    
  _modelFillDPL = glGenLists(1);
  qDebug("\n Fill model DPL = %d\n", _modelFillDPL);
  
  glNewList(_modelFillDPL, GL_COMPILE);
  glPolygonMode(GL_FRONT, GL_FILL);
  _faces->render();
  glEndList();
  
  //TODO : normals and bounding box
    
  _modelNormalsDPL = glGenLists(1);
  qDebug("\n Normal model DPL = %d\n", _modelNormalsDPL);
  
  glNewList(_modelNormalsDPL, GL_COMPILE);
  glPolygonMode(GL_FRONT, GL_FILL);
  _faces->renderNormals();
  glEndList();

      
  _boundingBoxDPL = glGenLists(1);
  qDebug("\n bounding box model DPL = %d\n", _boundingBoxDPL);
  
  glNewList(_boundingBoxDPL, GL_COMPILE);
  glPolygonMode(GL_FRONT, GL_FILL);
  _faces->renderBoundingBox();
  glEndList();


  
  
  updateCurrentDPL();  
}

void
Renderer::updateCurrentDPL()
{
 
  qDebug("\n Dans updateCurrentDPL \n");
  
  switch(_renderMode)
  {
    case WF:
    {
      _currentDPL = _modelWireFrameDPL;
      break;
    }

    case FLAT:
    {
      _currentDPL = _modelFillDPL;
      break;
    }

    case GOURAUD:
    {
      _currentDPL = _modelFillDPL;
      break;
    }

    default:
    {
      _currentDPL = _modelWireFrameDPL;
      break;
    }
  }

  qDebug("currentDPL = %d", _currentDPL);
  qDebug("\n Dans Exiting updateCurrentDPL \n");
  
}


void
Renderer::deleteDisplayLists()
{
  
  if ( _currentDPL != 0 )
  {
    qDebug("  deleting current DPL");
    glDeleteLists( _currentDPL, 1 );
  }

  if ( _modelWireFrameDPL != 0 )
  {
    qDebug("  deleting WIRE frame DPL");
    glDeleteLists( _modelWireFrameDPL, 1 );
  }

  if ( _modelFillDPL != 0 )
  {
    qDebug("  deleting FILL  DPL");
    glDeleteLists( _modelFillDPL, 1 );
  }

  if ( _modelNormalsDPL != 0 )
  {
    qDebug("  deleting normals DPL");
    glDeleteLists( _modelNormalsDPL, 1 );   
  }

  if ( _boundingBoxDPL != 0 )
  {
    qDebug("  deleting Bounding Box  DPL");
    glDeleteLists( _boundingBoxDPL, 1 );
  }
    
}


void
Renderer::setModel(Faces & faces)
{
  if (_faces != NULL)
  {
    qDebug("RENDERER : dans setModel deleting list...");

    deleteDisplayLists();

    qDebug("RENDERER : dans setModel deleting Faces object ...");
    
    delete _faces;
  }
  
  _faces = &faces;

  qDebug(" faces = %p", _faces);
  
  rebuildDPL();
}

Faces&
Renderer::model()
{
  return *(_faces);
}

int
Renderer::renderMode() const
{
  return (int) _renderMode;
}


void
Renderer::setRenderMode(RenderMode r)
{
  _renderMode = r;
  updateCurrentDPL();
}
