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
  //set square number to default
  _squareNumber = SQUARE_NUMBER_DEFAULT; 

  //define canvas2D type
  QString type(name);
  if((type.compare(sectionS))==0){
    _canvasType = SECTION_CANVAS;
  }
  else if((type.compare(cheminS))==0){
        _canvasType = CHEMIN_CANVAS;
  }
  else if((type.compare(profilS))==0){
        _canvasType = PROFIL_CANVAS;
  }
  else{
    _canvasType = W3D_CANVAS;
  }

  //popup menu building (differs from canvas type)
  _fileMenu = new QPopupMenu(this);

  if((_canvasType == SECTION_CANVAS) || 
     (_canvasType == CHEMIN_CANVAS)) {
    _fileMenu->insertItem( "Polyline",  this, SLOT(setPolyMode()) );
    _fileMenu->insertItem( "Circle",  this, SLOT(setCircleMode()) );
    _fileMenu->insertItem( "Rectangle",  this, SLOT(setRecMode()) );
    _fileMenu->insertItem( "Nurbs", this, SLOT(setNurbsMode()) );

    _fileMenu->insertSeparator();
    _fileMenu->insertItem( "delete selected", this, SLOT(deleteSelectedPoints()) );
    _fileMenu->insertItem( "delete all points", this, SLOT(deleteAllPoints()) );
  }
  else{
    _fileMenu->insertItem( "Polyline",  this, SLOT(setPolyMode()) );
    _fileMenu->insertItem( "Nurbs", this, SLOT(setNurbsMode()) );
    _fileMenu->insertSeparator();
    _fileMenu->insertItem( "delete selected", this, SLOT(deleteSelectedPoints()) );
    _fileMenu->insertItem( "delete all points", this, SLOT(deleteAllPoints()) );
  }
  
  //polyline default tool
  _toolMode = POLY_MODE;
  //no figure at start
  _figure = NULL;
}

void
Canvas2D::buildAxesDPL()
{
  _axesIndexDPL = glGenLists(1);
  double increment ;
  double xposition ;
  double yposition ;

  increment = (glOrthoParameter*2)/double(squareNumber);
  xposition = -glOrthoParameter + increment;
  yposition = -glOrthoParameter + increment;


  qDebug("index DPL axes 2D = %d\n", _axesIndexDPL);

  if (_axesIndexDPL != 0)
  {
    glNewList(_axesIndexDPL, GL_COMPILE);
    
    glColor3f(0.6, 0.6, 0.6);

    glBegin(GL_LINES);

    //if it's the profil canvas, we adapt the grid
    if(_canvasType == PROFIL_CANVAS){

      xposition += glOrthoParameter;

      //we draw vertical axes
      for(int i = 0; i<squareNumber/2; i++){
	glVertex2f(xposition , glOrthoParameter);
	glVertex2f(xposition , -glOrthoParameter);
	xposition += increment;
      }
      
      //we draw vertical axes
      for(int i = 0; i<squareNumber; i++){
	glVertex2f(glOrthoParameter , yposition);
	glVertex2f(0.0, yposition);
	yposition += increment;
      }

      glColor3f(0.2, 0.2, 0.2);

      //we draw the repere axes
      glVertex2f(0.0,0.0);
      glVertex2f(glOrthoParameter,0.0);
      glVertex2f(0.0,glOrthoParameter);
      glVertex2f(0.0,-glOrthoParameter);
    }
    else{
      
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
    
    }
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
  
  //we draw the figure
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

//mouse press management
void
Canvas2D::mousePressEvent(QMouseEvent* event)
{
  //display toolMenu popup with right button
  if(event->button() == Qt::RightButton){
    _fileMenu->exec(mapToGlobal(QPoint(event->x(),event->y())));
  }
  else{
    if((_canvasType != PROFIL_CANVAS) || (event->x() > width()/2.0)){
       
      if(event->state() == Qt::ControlButton){
	
	//if figure not exists
	if(_figure == NULL){
	  if(_toolMode == POLY_MODE){
	    cout<<"creation polyline !!!!"<<endl;
	    _figure = new Polyline(this);
	  }
	  if(_toolMode == CIRCLE_MODE){
	    cout<<"creation dun cercle !!!!"<<endl;
	  }
	  if(_toolMode == REC_MODE){
	    cout<<"creation rectangle !!!!"<<endl;
	  }
	  if(_toolMode == NURBS_MODE){
	    cout<<"creation nurbs !!!!"<<endl;
	  }
	}
      }
      
      if(_figure != NULL){
	_figure->manageEvent(event,_toolMode,_canvasType);
	updateGL();
      }
      else{
	cout<<"figure not exists"<<endl;
      }
    }
  }
}

//move mouse management
void
Canvas2D::mouseMoveEvent(QMouseEvent* event)
{
  if(_figure != NULL){
    _figure->manageEvent(event,_toolMode,_canvasType);
    updateGL();
  }
}

//realease mouse management
void
Canvas2D::mouseReleaseEvent(QMouseEvent* event)
{
  if(_figure != NULL){
    _figure->manageEvent(event,_toolMode,_canvasType);
    updateGL();
  }
}


//double click management
void
Canvas2D::mouseDoubleClickEvent(QMouseEvent* event)
{
  //display toolMenu popup with right button
  if(event->button() == Qt::RightButton){
    _fileMenu->exec(mapToGlobal(QPoint(event->x(),event->y())));
  }
  else{

    //avoid point out of profil canvas
    //creation only with control button
    if(((_canvasType != PROFIL_CANVAS) || (event->x() > width()/2.0)) &&
       (event->state() == Qt::ControlButton)){

      //if figure not exists
      if(_figure == NULL){
	if(_toolMode == POLY_MODE){
	  //here a polyline creation
	  _figure = new Polyline(this);
	}
	if(_toolMode == CIRCLE_MODE){
	  //here a circle creation
	}
	if(_toolMode == REC_MODE){
	  //here a rectangle creation
	}
	if(_toolMode == NURBS_MODE){
	  //here a nurb creation
	}
      }
      
      //if a figure has been created
      if(_figure != NULL){
	_figure->manageEvent(event,_toolMode,_canvasType);
	updateGL();
      }
    }
  }
}

void Canvas2D::keyPressEvent (QKeyEvent *event)
{
  if(_figure!=NULL){
    _figure->manageKeyEvent(event,_toolMode,_canvasType);
    updateGL();
  }
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
  _toolMode = POLY_MODE;
}

void Canvas2D::setCircleMode()
{
  _toolMode = CIRCLE_MODE;
}

void Canvas2D::setRecMode()
{
  _toolMode = REC_MODE;
}

void Canvas2D::setNurbsMode()
{
  _toolMode = NURBS_MODE;
}

void Canvas2D::deleteAllPoints()
{
  //delete the entire figure
  if(_figure!=NULL){
    delete(_figure);
    _figure = NULL;
  }
}

void Canvas2D::deleteSelectedPoints()
{
  //delete selected points and figure if no points
  if(_figure!=NULL){
    _figure->deleteSelected();
    _figure->noSelection();
    if(_figure->isEmpty()){
      delete(_figure);
      _figure = NULL;
    }
  }
}
