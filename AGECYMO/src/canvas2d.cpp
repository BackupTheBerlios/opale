#include "canvas2d.hpp"
#include "abscurve.hpp"
#include "polyline.hpp"
#include <qaction.h>

//a mettre dans les attributs de classe
//a modifier pour une gestion par l'interface
#define SELECTION_MODE 0
#define CREATION_MODE 1
gml::Point3D savePoint;
int mode = CREATION_MODE;



Canvas2D::Canvas2D(QWidget* parent, const char* name)
    : AbsCanvas(parent, name)
{
    
  _toolMenuBar = new QMenuBar(this,"the Tools");
  _fileMenu = new QPopupMenu(this);

  _toolMenuBar->insertItem( "Tools", _fileMenu );

  _fileMenu->insertItem( "Polyline",  this, SLOT(setPolyMode()) );
  _fileMenu->insertItem( "Circle",  this, SLOT(setCircleMode()) );
  _fileMenu->insertItem( "Rectangle",  this, SLOT(setRecMode()) );
  _fileMenu->insertItem( "Nurbs", this, SLOT(setNurbsMode()) );


  _squareNumber = SQUARE_NUMBER_DEFAULT; 

  if((caption().compare(sectionS))==0){
    _canvasType = SECTION_CANVAS;
  }
  else if((caption().compare(cheminS))==0){
        _canvasType = CHEMIN_CANVAS;
  }
  else if((caption().compare(profilS))==0){
        _canvasType = PROFIL_CANVAS;
  }
  else{
    _canvasType = W3D_CANVAS;
  }

  _toolMode = POLY_MODE;
  _figure = NULL;
}

void
Canvas2D::buildAxesDPL()
{
  _axesIndexDPL = glGenLists(1);
  double increment = (glOrthoParameter*2)/double(squareNumber);
  double xposition = -glOrthoParameter + increment;
  double yposition = -glOrthoParameter + increment;
    

  qDebug("index DPL axes 2D = %d\n", _axesIndexDPL);

  if (_axesIndexDPL != 0)
  {
    glNewList(_axesIndexDPL, GL_COMPILE);
    
    glColor3f(0.6, 0.6, 0.6);

    glBegin(GL_LINES);

    //we draw vertical axes
    for(int i = 0; i<squareNumber; i++){
      glVertex2f(xposition , glOrthoParameter);
      glVertex2f(xposition , -glOrthoParameter);
      xposition += increment;
    }

    //we draw vertical axes
    for(int i = 0; i<squareNumber; i++){
      glVertex2f(glOrthoParameter , yposition);
      glVertex2f(-glOrthoParameter, yposition);
      yposition += increment;
    }

    glColor3f(0.2, 0.2, 0.2);

    //we draw the repere axes
    glVertex2f(0.0,glOrthoParameter);
    glVertex2f(0.0,-glOrthoParameter);
    glVertex2f(glOrthoParameter,0.0);
    glVertex2f(-glOrthoParameter,0.0);
    
    glEnd();
    glEndList();
    
  }
  else
  {
    qDebug("Erreur a la creation de la Display liste pour les AXES 2D \n");
  }
  
}


void
Canvas2D::drawAxes()
{      
  glCallList(_axesIndexDPL);
}

void
Canvas2D::initializeGL()
{
  glClearColor (0.5, 0.5, 0.5, 0);
  glClearDepth(1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPolygonMode(GL_FRONT, GL_LINE);
  buildAxesDPL();
}

void
Canvas2D::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode (GL_MODELVIEW);   
  glLoadIdentity();

  drawAxes();
  
  //we draw the polyline
  if(_figure != NULL){
    _figure->render();
  }

  //updating buffers
  swapBuffers();
}


void
Canvas2D::resizeGL(int width, int height)
{
  double w2 = width / 2.0;
  double h2 = height / 2.0;
  
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluOrtho2D(-glOrthoParameter, 
	     glOrthoParameter, 
	     -glOrthoParameter, 
	     glOrthoParameter);
}

int cpt = 3;

void
Canvas2D::mousePressEvent(QMouseEvent* event)
{
  if(_figure == NULL){
    if(_toolMode == POLY_MODE){
      _figure = new Polyline(this);
    }
    if(_toolMode == CIRCLE_MODE){
      cout<<"creation dun cercle !!!!"<<endl;
    }
    if(_toolMode == REC_MODE){

    }
    if(_toolMode == NURBS_MODE){
      
    }
  }
    
  _figure->manageEvent(event,_toolMode,_canvasType);
  updateGL();
}


void
Canvas2D::mouseMoveEvent(QMouseEvent* event)
{
  if(_figure != NULL){
    _figure->manageEvent(event,_toolMode,_canvasType);
    updateGL();
  }
}

void
Canvas2D::mouseReleaseEvent(QMouseEvent* event)
{
  if(_figure != NULL){
    _figure->manageEvent(event,_toolMode,_canvasType);
    updateGL();
  }
}

void
Canvas2D::mouseDoubleClickEvent(QMouseEvent* event)
{
  if(_figure == NULL){
    if(_toolMode == POLY_MODE)
      _figure = new Polyline(this);
  }

  if(_toolMode == CIRCLE_MODE){
    cout<<"creation dun cercle !!!!"<<endl;
  }
  if(_toolMode == REC_MODE){
    
  }
  if(_toolMode == NURBS_MODE){
    
  }
    
  _figure->manageEvent(event,_toolMode,_canvasType);
  updateGL();

}

int Canvas2D::getSquareNumber()
{
  return _squareNumber;
}

void Canvas2D::setSquareNumber(int newValue)
{
  _squareNumber = newValue;
}


//SLOTS

void Canvas2D::setPolyMode()
{
  cout<<"hourra"<<endl;
  _toolMode = POLY_MODE;
}

void Canvas2D::setCircleMode()
{
  cout<<"hourra"<<endl;
  _toolMode = CIRCLE_MODE;
}

void Canvas2D::setRecMode()
{
  cout<<"hourra"<<endl;
  _toolMode = REC_MODE;
}

void Canvas2D::setNurbsMode()
{
  cout<<"hourra"<<endl;
  _toolMode = NURBS_MODE;
}


