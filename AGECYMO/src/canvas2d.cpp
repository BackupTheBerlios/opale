#include "canvas2d.hpp"


Canvas2D::Canvas2D(QWidget* parent, const char* name)
    : AbsCanvas(parent, name)
{
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

    //ancien repère
    /*
    glBegin(GL_LINES);
    glVertex2f(0.0, 0.0);
    glVertex2f(1.0, 0.0);
    glEnd();
    
    glColor3f(0.0, 0.7, 0.0);
    
    glBegin(GL_LINES);
    glVertex2f(0.0, 0.0);
    glVertex2f(0.0, 1.0);
    glEnd();
    */

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
//  std::cout << "ici " << std::endl;
  
//   glColor3f(0.7, 0.0, 0.0);
  
//   glBegin(GL_LINES);
//   glVertex2f(0.0, 0.0);
//   glVertex2f(1.0, 0.0);
//   glEnd();

//   glColor3f(0.0, 0.7, 0.0);
  
//   glBegin(GL_LINES);
//   glVertex2f(0.0, 0.0);
//   glVertex2f(0.0, 1.0);
//   glEnd();

      
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

//mode de lecture a implémenter plus haut
int mode = 1;
Point3D saveClick;
bool inSelection = false;

void
Canvas2D::mousePressEvent(QMouseEvent* event)
{
  Point3D point;
  //calcul de la coordonnée x QT -> openGL
  point[0] =
    -glOrthoParameter + 
    ((double)event->x() * ((glOrthoParameter*2)/(double)width()));
  //calcul de la coordonnée y QT -> openGL
  point[1] =
    glOrthoParameter - 
    ((double)event->y() * ((glOrthoParameter*2)/(double)height()));
  

  //mode selection
  if(mode == 0){
    if(!inSelection){
      saveClick[0] = point[0];
      saveClick[1] = point[1];
      inSelection = true;
    }
  }


  //mode creation
  else{
      //ajout du point openGl
      _polyline.addPoint(point);
  }
  
  //openGl update
  updateGL();
}


void
Canvas2D::mouseMoveEvent(QMouseEvent* event)
{
  //openGl update
  updateGL();
}

void
Canvas2D::mouseReleaseEvent(QMouseEvent* event)
{
  Point3D point;
  //calcul de la coordonnée x QT -> openGL
  point[0] =
    -glOrthoParameter + 
    ((double)event->x() * ((glOrthoParameter*2)/(double)width()));
  //calcul de la coordonnée y QT -> openGL
  point[1] =
    glOrthoParameter - 
    ((double)event->y() * ((glOrthoParameter*2)/(double)height()));

  //mode selection
  if(mode == 0){
    _polyline.selection(saveClick[0], saveClick[1], 
			point[0], point[1]);
  }
}

void
Canvas2D::mouseDoubleClickEvent(QMouseEvent* event)
{
  Point3D point;
   //calcul de la coordonnée x QT -> openGL
  point[0] =
    -glOrthoParameter + 
    ((double)event->x() * ((glOrthoParameter*2)/(double)width()));
  //calcul de la coordonnée y QT -> openGL
  point[1] =
    glOrthoParameter - 
    ((double)event->y() * ((glOrthoParameter*2)/(double)height()));

  //ajout du point openGl
  _polyline.addPoint(point);
  //polyline closing
  _polyline.close();
  updateGL();
}
