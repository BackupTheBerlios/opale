#include "canvas2d.hpp"

//a mettre dans les attributs de classe
//a modifier pour une gestion par l'interface
#define SELECTION_MODE 0
#define CREATION_MODE 1
gml::Point3D savePoint;
int mode = CREATION_MODE;



Canvas2D::Canvas2D(QWidget* parent, const char* name)
    : AbsCanvas(parent, name)
{
  _squareNumber = SQUARE_NUMBER_DEFAULT;
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
  _polyline.render();
  _symetrique.render();

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
  if((caption().compare(sectionS))==0){
    sectionClickEvent(event);
  }
  else if((caption().compare(cheminS))==0){
    cheminClickEvent(event);
  }
  else if((caption().compare(profilS))==0){
    profilClickEvent(event);
  }
  else{
    window3dClickEvent(event);
  }

  //openGl update
  updateGL();
}


void
Canvas2D::mouseMoveEvent(QMouseEvent* event)
{

  if((caption().compare(sectionS))==0){
    sectionMoveEvent(event);
  }
  else if((caption().compare(cheminS))==0){
    cheminMoveEvent(event);
  }
  else if((caption().compare(profilS))==0){
    profilMoveEvent(event);
  }
  else{
    window3dMoveEvent(event);
  }

  //openGl update
  updateGL();
}

void
Canvas2D::mouseReleaseEvent(QMouseEvent* event)
{

  if((caption().compare(sectionS))==0){
    sectionReleaseEvent(event);
  }
  else if(caption().compare(cheminS)==0){
    cheminReleaseEvent(event);
  }
  else if(caption().compare(profilS)==0){
    profilReleaseEvent(event);
  }
  else{
    window3dReleaseEvent(event);
  }
}

void
Canvas2D::mouseDoubleClickEvent(QMouseEvent* event)
{
  if(caption().compare(sectionS)==0){
    sectionDoubleClickEvent(event);
  }
  else if(caption().compare(cheminS)==0){
    cheminDoubleClickEvent(event);
  }
  else if(caption().compare(profilS)==0){
    profilDoubleClickEvent(event);
  }
  else{
    window3dDoubleClickEvent(event);
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

void Canvas2D::calculateQtToOpenGL(QMouseEvent* event, Point3D *point)
{
  //coordinate calcul for qt/openGl traduction
  (*point)[0] =
    -glOrthoParameter + 
    ((double)event->x() * ((glOrthoParameter*2)/(double)width()));
  (*point)[1] =
    glOrthoParameter - 
    ((double)event->y() * ((glOrthoParameter*2)/(double)height()));
}







/****************************************************************/
/*evenement management*/

//SECTION EVENTS

void Canvas2D::sectionClickEvent(QMouseEvent* event)
{
  //coordinate calcul for qt/openGl traduction
  Point3D point;
  calculateQtToOpenGL(event, &point);

  if(mode == CREATION_MODE){
    //force the polyline to be closed
    if(!_polyline.isClosed()){
      _polyline.close();
    }

    //add the opengl point
    _polyline.addPoint(point);
  }
  else if (mode == SELECTION_MODE){
    //if a point is selected
    int index;
    index = _polyline.isExistingPoint(point);

     _polyline.noSelection();

    if(index == -1){
      savePoint[0] = point[0];
      savePoint[1] = point[1];
    }
    else{
      _polyline.select(index);
    }
  }
}


void Canvas2D::sectionMoveEvent(QMouseEvent* event)
{
  if(mode == CREATION_MODE){
    
  }
  else if (mode == SELECTION_MODE){
    
  }
}


void Canvas2D::sectionReleaseEvent(QMouseEvent* event)
{
  if(mode == CREATION_MODE){
    
  }
  else if (mode == SELECTION_MODE){
    
  }
}

void Canvas2D::sectionDoubleClickEvent(QMouseEvent* event)
{
  if(mode == CREATION_MODE){
    
  }
  else if (mode == SELECTION_MODE){
    
  }
}


//PROFIL EVENTS

void Canvas2D::profilClickEvent(QMouseEvent* event)
{
  Point3D point;
  calculateQtToOpenGL(event, &point);

  if(mode == CREATION_MODE){
    //add the opengl point with his symetric
    if(point[0] <= 0.0){
      _polyline.addPoint(point);
      point[0] *= -1;
      _symetrique.addPoint(point);
    }
    else{
      _symetrique.addPoint(point);
      point[0] *= -1;
      _polyline.addPoint(point);
    }
  }
  else if (mode == SELECTION_MODE){
    
  }
}

void Canvas2D::profilMoveEvent(QMouseEvent* event)
{
  if(mode == CREATION_MODE){
    
  }
  else if (mode == SELECTION_MODE){
    
  }
}

void Canvas2D::profilReleaseEvent(QMouseEvent* event)
{
  if(mode == CREATION_MODE){
    
  }
  else if (mode == SELECTION_MODE){
    
  }
}

void Canvas2D::profilDoubleClickEvent(QMouseEvent* event)
{
  if(mode == CREATION_MODE){
    
  }
  else if (mode == SELECTION_MODE){
    
  }
}


//CHEMIN EVENTS

void Canvas2D::cheminClickEvent(QMouseEvent* event)
{
  Point3D point;
  calculateQtToOpenGL(event, &point);
  
  if(mode == CREATION_MODE){
    //add the opengl point
    _polyline.addPoint(point);
  }
  else if (mode == SELECTION_MODE){
    
  }
}

void Canvas2D::cheminMoveEvent(QMouseEvent* event)
{
  if(mode == CREATION_MODE){
    
  }
  else if (mode == SELECTION_MODE){
    
  }
}

void Canvas2D::cheminReleaseEvent(QMouseEvent* event)
{
  if(mode == CREATION_MODE){
    
  }
  else if (mode == SELECTION_MODE){
    
  }
}

void Canvas2D::cheminDoubleClickEvent(QMouseEvent* event)
{
  Point3D point;
  calculateQtToOpenGL(event, &point);


  if(mode == CREATION_MODE){
    //ajout du point openGl
    _polyline.addPoint(point);
    //polyline closing
    _polyline.close();
  }
  else if (mode == SELECTION_MODE){
    
  }

}


//WINDOW3D EVENTS

void Canvas2D::window3dClickEvent(QMouseEvent* event)
{
  if(mode == CREATION_MODE){
    
  }
  else if (mode == SELECTION_MODE){
    
  }
}

void Canvas2D::window3dMoveEvent(QMouseEvent* event)
{
  if(mode == CREATION_MODE){
    
  }
  else if (mode == SELECTION_MODE){
    
  }
}

void Canvas2D::window3dReleaseEvent(QMouseEvent* event)
{
  if(mode == CREATION_MODE){
    
  }
  else if (mode == SELECTION_MODE){
    
  }
}

void Canvas2D::window3dDoubleClickEvent(QMouseEvent* event)
{
  if(mode == CREATION_MODE){
    
  }
  else if (mode == SELECTION_MODE){
    
  }
}


