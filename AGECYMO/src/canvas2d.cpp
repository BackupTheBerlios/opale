#include "canvas2d.hpp"
#include "abscurve.hpp"
#include "polyline.hpp"
#include "curves.hpp"
#include "mainwindow.hpp"
#include <qaction.h>

//a mettre dans les attributs de classe
//a modifier pour une gestion par l'interface
#define SELECTION_MODE 0
#define CREATION_MODE 1
gml::Point3D savePoint;
int mode = CREATION_MODE;


/**************************************************************
 *
 *  constructor 
 *  @param MainWindow the mainWindow
 *  @param parent the parent widget
 *  @return name the name of the canvas
 *
 *************************************************************/
Canvas2D::Canvas2D(MainWindow* mw, QWidget* parent, const char* name)
    : AbsCanvas(parent, name)
{ 

  _mw = mw;

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

  //creation of the QActions
  QAction *polyAction = 
    new QAction(QIconSet(QPixmap("../images/polyline.png")),
		"Polyline",0,this);

  QAction *nurbsAction = 
    new QAction(QIconSet(QPixmap("../images/nurbs.png")),
		"Nurbs",0,this);

  QAction *circleAction = 
    new QAction(QIconSet(QPixmap("../images/ellipse.png")),
		"Circle",0,this);

  QAction *quadriAction = 
    new QAction(QIconSet(QPixmap("../images/quadri.png")),
		"Rectangle",0,this);

  QAction *polygAction = 
    new QAction(QIconSet(QPixmap("../images/polygone.png")),
		"Polygon",0,this);

  QAction *selectAllAction = 
    new QAction(QIconSet(QPixmap("../images/selectAll.png")),
		"Select all",0,this);

  QAction *deselectAllAction = 
    new QAction(QIconSet(QPixmap("../images/deselectAll.png")),
		"Deselect all",0,this);

  QAction *deleteAllAction = 
    new QAction(QIconSet(QPixmap("../images/deleteAll.png")),
		"DeleteAll",0,this);

  //connect actions
  connect(polyAction,
          SIGNAL( activated() ),
          this,
          SLOT(setPolyMode()) );
  connect(nurbsAction,
          SIGNAL( activated() ),
          this,
          SLOT(setNurbsMode()) );
  connect(circleAction,
          SIGNAL( activated() ),
          this,
          SLOT(setCircleMode()) );
  connect(quadriAction,
          SIGNAL( activated() ),
          this,
          SLOT(setRecMode()) );
  connect(polygAction,
          SIGNAL( activated() ),
          this,
          SLOT(setPolygMode()) );

  connect(selectAllAction,
          SIGNAL( activated() ),
          this,
	  SLOT(selectAllPoints()) );

  connect(deselectAllAction,
          SIGNAL( activated() ),
          this,
          SLOT(deselectAllPoints()) );

  connect(deleteAllAction,
          SIGNAL( activated() ),
          this,
          SLOT(deleteAllPoints()) );

  //add QActions to menu
  polyAction->addTo(_fileMenu);
  nurbsAction->addTo(_fileMenu);
  circleAction->addTo(_fileMenu);
  quadriAction->addTo(_fileMenu);
  polygAction->addTo(_fileMenu);
  
  //if it's the canvas profil, disable many tools
  if(_canvasType == PROFIL_CANVAS){
    
    _fileMenu->setItemEnabled(_fileMenu->idAt(2),false);
    _fileMenu->setItemEnabled(_fileMenu->idAt(3),false);
    _fileMenu->setItemEnabled(_fileMenu->idAt(4),false);  
  }

  _fileMenu->insertSeparator();

  selectAllAction->addTo(_fileMenu);
  deselectAllAction->addTo(_fileMenu);
  _fileMenu->insertSeparator();
  deleteAllAction->addTo(_fileMenu);

  //polyline default tool
  _toolMode = POLY_MODE;
  
  //creation of the curves class
  _figure = new Curves(this);;
}

/**************************************************************
 *
 *  build principal axes
 *
 *************************************************************/
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

/**************************************************************
 *
 *  draw axes in an openGL context
 *
 *************************************************************/
void
Canvas2D::drawAxes()
{      
  glCallList(_axesIndexDPL);
}

/**************************************************************
 *
 *  initialise the openGL context
 *
 *************************************************************/
void
Canvas2D::initializeGL()
{
  glClearColor (0.5, 0.5, 0.5, 0);
  glClearDepth(1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPolygonMode(GL_FRONT, GL_LINE);
  buildAxesDPL();
}

/**************************************************************
 *
 *  paint canvas curves in openGL context
 *
 *************************************************************/
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


/**************************************************************
 *
 *  resize the canvas
 *  @param x the height
 *  @param y the width
 *
 *************************************************************/
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


/**************************************************************
 *
 *  manage mouse press event
 *  @param event the event
 *
 *************************************************************/
void
Canvas2D::mousePressEvent(QMouseEvent* event)
{
  //display toolMenu popup with right button
  if(event->button() == Qt::RightButton){
    _fileMenu->exec(mapToGlobal(QPoint(event->x(),event->y())));
  }
  else{
    if((_canvasType != PROFIL_CANVAS) || (event->x() > width()/2.0)){
       
	_figure->managePressEvent(event,_toolMode,_canvasType);
	updateGL();
    }
  }
}

/**************************************************************
 *
 *  manage mouse move event
 *  @param event the event
 *
 *************************************************************/
void
Canvas2D::mouseMoveEvent(QMouseEvent* event)
{
    _figure->manageMoveEvent(event,_toolMode,_canvasType);
    updateGL();
}

/**************************************************************
 *
 *  manage mouse release event
 *  @param event the event
 *
 *************************************************************/
void
Canvas2D::mouseReleaseEvent(QMouseEvent* event)
{
  _figure->manageReleaseEvent(event,_toolMode,_canvasType);
  updateGL();
}


/**************************************************************
 *
 *  manage moude double click event
 *  @param event the event
 *
 *************************************************************/
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

      _figure->manageDbClickEvent(event,
				  _toolMode,
				  _canvasType);
    }
  }
}

/**************************************************************
 *
 *  get the number of square (grid resolution)
 *  @return the square number
 *
 *************************************************************/
int Canvas2D::getSquareNumber()
{
  return _squareNumber;
}

/**************************************************************
 *
 *  set the number of square (grid resolution)
 *  @param newValue the new square number
 *
 *************************************************************/
void Canvas2D::setSquareNumber(int newValue)
{
  _squareNumber = newValue;
}

/**************************************************************
 *
 *  get the curves
 *  @return the curves
 *
 *************************************************************/
Curves *Canvas2D::getFigure()
{
  return _figure;
}

/**************************************************************
 *
 *  get the selected toolMode
 *  @return the toolMode
 *
 *************************************************************/
unsigned short Canvas2D::getToolMode()
{
  return _toolMode;
}

/**************************************************************
 *
 *  get the type of this canvas
 *  @return the canvas type
 *
 *************************************************************/
unsigned short Canvas2D::getCanvasType()
{
  return _canvasType;
}

/**************************************************************
 *
 *  get the mainWindow
 *  @return the mainwindow
 *
 *************************************************************/
MainWindow& Canvas2D::getMW() {
  return *_mw;
}

/**************************************************************
 *
 *  set the curves
 *  @param the curves to set
 *
 *************************************************************/
void Canvas2D::setFigure(Curves *figure)
{
  if(_figure!=NULL){
    delete(_figure);
  }
  _figure = figure;
  updateGL();
}

/**************************************************************
 *
 *  get the popupMenu for manage tools
 *  @return the tools popupMenu
 *
 *************************************************************/
QPopupMenu *Canvas2D::getPopupMenu()
{
  return _fileMenu;
}


/**************************************************************
 *
 *  set toolMode to polylin mode
 *
 *************************************************************/
void Canvas2D::setPolyMode()
{
  _toolMode = POLY_MODE;
}

/**************************************************************
 *
 *  set toolMode to polygone mode
 *
 *************************************************************/
void Canvas2D::setPolygMode()
{
  _toolMode = POLYG_MODE;
}

/**************************************************************
 *
 *  set toolMode ti circle mode
 *
 *************************************************************/
void Canvas2D::setCircleMode()
{
  _toolMode = CIRCLE_MODE;
}

/**************************************************************
 *
 *  set toolMode to rectangle mode
 *
 *************************************************************/
void Canvas2D::setRecMode()
{
  _toolMode = REC_MODE;
}

/**************************************************************
 *
 *  set toolMode to nubs mode
 *
 *************************************************************/
void Canvas2D::setNurbsMode()
{
  _toolMode = NURBS_MODE;
}

/**************************************************************
 *
 *  delete all the points (here mean all the curves too)
 *
 *************************************************************/
void Canvas2D::deleteAllPoints()
{
  _figure->deleteAllCurves();
  //polyline default tool
  _toolMode = POLY_MODE;
}

/**************************************************************
 *
 *  select all the points
 *
 *************************************************************/
void Canvas2D::selectAllPoints()
{
  _figure->selectAll();
  std::vector <gml::Point3D> points;
  points = _figure->discretize(2);
  for(unsigned i = 0; i<points.size(); i++){
    cout<<"x = "<<points[i][0]<<" y = "<<points[i][1]<<endl;
  }
}

/**************************************************************
 *
 *  deselect all the points
 *
 *************************************************************/
void Canvas2D::deselectAllPoints()
{
  _figure->noSelection();
}


