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

void
Canvas2D::mousePressEvent(QMouseEvent* event)
{
  if(caption() == "Section"){
    sectionClickEvent(event);
  }
  else if(caption().compare(cheminS)==0){
    cheminClickEvent(event);
  }
  else if(caption() == NULL){
    profilClickEvent(event);
  }
  else{
    window3dClickEvent(event);
  }

  cout<<caption().compare(sectionS)<<endl;

  //openGl update
  updateGL();
}


void
Canvas2D::mouseMoveEvent(QMouseEvent* event)
{

  if(caption().compare(sectionS)==0){
    sectionMoveEvent(event);
  }
  else if(caption().compare(cheminS)==0){
    cheminMoveEvent(event);
  }
  else if(caption().compare(profilS)==0){
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

  if(caption().compare(sectionS)==0){
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


void Canvas2D::sectionClickEvent(QMouseEvent* event)
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
  
  //polyline closing
  if(!_polyline.isClosed()){
      _polyline.close();
  }

  //add the opengl point
  _polyline.addPoint(point);
  
}

void Canvas2D::profilClickEvent(QMouseEvent* event)
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

  //add the opengl point
  _polyline.addPoint(point);
  point[0] *= -1;
  _symetrique.addPoint(point);

}

void Canvas2D::cheminClickEvent(QMouseEvent* event)
{

}

void Canvas2D::window3dClickEvent(QMouseEvent* event)
{

}

void Canvas2D::sectionMoveEvent(QMouseEvent* event)
{

}

void Canvas2D::profilMoveEvent(QMouseEvent* event)
{

}

void Canvas2D::cheminMoveEvent(QMouseEvent* event)
{

}

void Canvas2D::window3dMoveEvent(QMouseEvent* event)
{

}

void Canvas2D::sectionReleaseEvent(QMouseEvent* event)
{

}

void Canvas2D::profilReleaseEvent(QMouseEvent* event)
{

}

void Canvas2D::cheminReleaseEvent(QMouseEvent* event)
{

}

void Canvas2D::window3dReleaseEvent(QMouseEvent* event)
{

}

void Canvas2D::sectionDoubleClickEvent(QMouseEvent* event)
{

}

void Canvas2D::profilDoubleClickEvent(QMouseEvent* event)
{

}

void Canvas2D::cheminDoubleClickEvent(QMouseEvent* event)
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

void Canvas2D::window3dDoubleClickEvent(QMouseEvent* event)
{

}
