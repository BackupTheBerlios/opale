#include "canvas2d.hpp"
#include "abscurve.hpp"
#include "polyline.hpp"
#include "curves.hpp"
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

  _fileMenu->insertItem( "Polyline",  this, SLOT(setPolyMode()),0,0 );
  _fileMenu->insertItem( "Nurbs", this, SLOT(setNurbsMode()),0,1 );
  _fileMenu->insertItem( "Circle",  this, SLOT(setCircleMode()),0,2 );
  _fileMenu->insertItem( "Rectangle",  this, SLOT(setRecMode()),0,3 );

  if(_canvasType == PROFIL_CANVAS){
    
    getPopupMenu()->setItemEnabled(0,false);
    getPopupMenu()->setItemEnabled(1,false);
    
  }

  _fileMenu->insertSeparator();
  _fileMenu->insertItem( "select all", 
			 this, SLOT(selectAllPoints()) );
  _fileMenu->insertItem( "deselect all", 
			 this, SLOT(deselectAllPoints()) );

  _fileMenu->insertSeparator();
  _fileMenu->insertItem( "delete all", 
			 this, SLOT(deleteAllPoints()) );
  
  //polyline default tool
  _toolMode = POLY_MODE;
  
  //creation of the curves class
  _figure = new Curves(this);;
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
	_figure->managePressEvent(event,_toolMode,_canvasType);
	updateGL();
      }
      
    }
  }
}

//move mouse management
void
Canvas2D::mouseMoveEvent(QMouseEvent* event)
{
    _figure->manageMoveEvent(event,_toolMode,_canvasType);
    updateGL();
}

//realease mouse management
void
Canvas2D::mouseReleaseEvent(QMouseEvent* event)
{
  _figure->manageReleaseEvent(event,_toolMode,_canvasType);
  updateGL();
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
    if(((_canvasType != PROFIL_CANVAS) || (event->x() > width()/2.0))) {

      if (event->state() == Qt::ControlButton){
      _figure->manageDbClickEvent(event,
				  _toolMode,
				  _canvasType);
      }
    }
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


Curves *Canvas2D::getFigure()
{
  return _figure;
}

unsigned short Canvas2D::getToolMode()
{
  return _toolMode;
}
unsigned short Canvas2D::getCanvasType()
{
  return _canvasType;
}

void Canvas2D::setFigure(Curves *figure)
{
  if(_figure!=NULL){
    delete(_figure);
  }
  _figure = figure;
  updateGL();
}

QPopupMenu *Canvas2D::getPopupMenu()
{
  return _fileMenu;
}

//SLOTS
void Canvas2D::setPolyMode()
{
  _toolMode = POLY_MODE;
}

void Canvas2D::setPolygMode()
{
  _toolMode = POLYG_MODE;
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
  _figure->deleteAllCurves();
  //polyline default tool
  _toolMode = POLY_MODE;
}

void Canvas2D::selectAllPoints()
{
  _figure->selectAll();
  std::vector <gml::Point3D> points;
  points = _figure->discretize(2);
  for(unsigned i = 0; i<points.size(); i++){
    cout<<"x = "<<points[i][0]<<" y = "<<points[i][1]<<endl;
  }
}

void Canvas2D::deselectAllPoints()
{
  _figure->noSelection();
}


