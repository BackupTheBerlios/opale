#include <typeinfo>
#include "canvas3d.hpp"
#include "mainwindow.hpp"

/**************************************************************
 *
 *  Canvas3D constructor
 *  @param mw the reference to the mainWindow
 *  @param parent the parent widget
 *  @param name the name
 *
 *************************************************************/
Canvas3D::Canvas3D(MainWindow* mw, QWidget* parent, const char* name)
    : AbsCanvas(parent, name) ,//QGLWidget(parent, name),
      _axesEnabled(true),
      _boundingBoxEnabled(false),
      _normalEnabled(false),
      _infoEnabled(false)
{

  _mw = mw;

  _lightPos[0] = 0;
  _lightPos[1] = 100;
  _lightPos[2] = 0;
  
  _accel  = new QAccel(this);

  //Camera stuffs
  _accel->insertItem(Key_Left,  CAMERA_TURN_LEFT);
  _accel->insertItem(Key_Right, CAMERA_TURN_RIGHT);

  _accel->insertItem(SHIFT + Key_Left,  CAMERA_TURN_AROUND_LEFT);
  _accel->insertItem(SHIFT + Key_Right, CAMERA_TURN_AROUND_RIGHT);

  _accel->insertItem(Key_Up,    CAMERA_TURN_UPPER);
  _accel->insertItem(Key_Down,  CAMERA_TURN_DOWN);

  _accel->insertItem(SHIFT + Key_Down,  CAMERA_MOVE_AWAY);
  _accel->insertItem(SHIFT + Key_Up,    CAMERA_MOVE_CLOSER);

  //TODO: to implement it
//   _accel->insertItem(CTRL + Key_Left,  CAMERA_MOVE_LEFT);
//   _accel->insertItem(CTRL + Key_Right, CAMERA_MOVE_RIGHT);
  
//   _accel->insertItem(CTRL + Key_Up,  CAMERA_MOVE_UP);
//   _accel->insertItem(CTRL + Key_Down, CAMERA_MOVE_DOWN);

  //Info keys
  _accel->insertItem(Key_F1, ENABLE_DRAW_AXES);
  _accel->insertItem(Key_F2, ENABLE_DRAW_FPS);
  _accel->insertItem(Key_F3, ENABLE_DRAW_BOUNDING_BOX);
  _accel->insertItem(Key_F4, ENABLE_DRAW_INFO_MODEL);

  //Rendering Keys
  _accel->insertItem(Key_F5, WIREFRAME_RENDERING_MODE);
  _accel->insertItem(Key_F6, FLAT_RENDERING_MODE);
  _accel->insertItem(Key_F7, GOURAUD_RENDERING_MODE);
  _accel->insertItem(Key_F8, WF_HDLR_RENDERING_MODE);
  _accel->insertItem(Key_F9, NORMAL_RENDERING_MODE);
  
  
  QObject::connect( _accel ,
                    SIGNAL( activated( int ) ) ,
                    this ,
                    SLOT( accelEvent( int ) ) ) ;


  //testing the CylinderGenerator
  
  
}

/**************************************************************
 *
 *  Canvas3D destructor
 *
 *************************************************************/
Canvas3D::~Canvas3D()
{
  if (_accel != NULL)
  {
    delete _accel;
  }
}

/**************************************************************
 *
 *  build the display lists for axes
 *
 *************************************************************/
void
Canvas3D::buildAxesDPL()
{
  _axesIndexDPL = glGenLists(1);

  qDebug("index DPL axes 3D = %d\n", _axesIndexDPL);
  
  if (_axesIndexDPL != 0)
  {
    glNewList(_axesIndexDPL, GL_COMPILE);
    
    GLUquadricObj* qobj = gluNewQuadric();
    gluQuadricNormals(  qobj, GLU_SMOOTH ) ;
    gluQuadricDrawStyle( qobj, GLU_FILL ) ;
    gluQuadricOrientation( qobj, GLU_OUTSIDE ) ;
    
    static const GLdouble axis_radius = 0.05 ;
    static const GLdouble axis_length = 1.0 ;
    static const GLdouble arrow_radius = 0.05 ;
    static const GLdouble arrow_length = 0.2 ;
    
    glPolygonMode( GL_FRONT_AND_BACK , GL_FILL ) ;
    glEnable( GL_COLOR_MATERIAL ) ;
    glColorMaterial( GL_FRONT_AND_BACK , GL_AMBIENT_AND_DIFFUSE ) ;
    
    //Y
    glPushMatrix();
    glRotated(-90, 1, 0, 0);
    glColor4f(1.0f,0.0f,0.0f, 0.5f);
    gluCylinder(qobj, axis_radius, axis_radius,axis_length, 12, 1);
    glTranslated(0.0, 0.0, axis_length);
    gluDisk(qobj, axis_radius, arrow_radius, 12, 1);
    gluCylinder(qobj, arrow_radius, 0, arrow_length, 12, 1);
    glPopMatrix();
  
    //X
    glPushMatrix();
    glRotated(90, 0, 1, 0);
    glColor4f(0.0f,1.0f,0.0f, 0.5f);
    gluCylinder(qobj, axis_radius, axis_radius, axis_length, 12, 1);
    glTranslated(0.0, 0.0, axis_length);
    gluDisk(qobj, axis_radius, arrow_radius, 12, 1);
    gluCylinder(qobj, arrow_radius, 0, arrow_length, 12, 1);
    glPopMatrix();
    
    //Z
    glPushMatrix();
    glColor4f(0.0f,0.0f, 1.0f, 0.5f);
    gluCylinder(qobj, axis_radius, axis_radius, axis_length, 12, 1);
    glTranslated(0.0, 0.0, axis_length);
    gluDisk(qobj, axis_radius, arrow_radius, 12, 1);
    gluCylinder(qobj, arrow_radius, 0, arrow_length, 12, 1);
    glPopMatrix();
  
    glEndList();
    
  }
  else
  {
    qDebug("Erreur a la creation de la Display liste pour les axes du repere3D\n");
  }

}

/**************************************************************
 *
 *  draw the axes
 *
 *************************************************************/
void
Canvas3D::drawAxes()
{
  if (_axesEnabled)
  {
    glCallList(_axesIndexDPL);
  }
}

/**************************************************************
 *
 *  draw the bounding box
 *
 *************************************************************/
void
Canvas3D::drawBoundingBox()
{
  if (_boundingBoxEnabled)
  {
    _renderer.renderBoundingBox();
  }
}

/**************************************************************
 *
 *  draw the normals
 *
 *************************************************************/
void
Canvas3D::drawNormals()
{
  if (_normalEnabled)
  {
    _renderer.renderNormals();
  }
}

/**************************************************************
 *
 *  draw info about model
 *
 *************************************************************/
void
Canvas3D::drawInfo()
{
  if(_infoEnabled)
  {

    int ntria   = _renderer.model().numberOfTriangles();
    int nquad   = _renderer.model().numberOfQuads();
    int nother  = _renderer.model().numberOfOthers();
    int nvertex = _renderer.model().numberOfVertex();

    glPushAttrib(GL_LIGHTING_BIT);
    
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);

    glColor3f(0.0 , 0.0, 1.0);
    renderText(5,
               10,
               QString("Triangles : ").append(QString::number(ntria)) );  
        
    glColor3f(0.0 , 1.0, 0);
    renderText(5,
               25,
               QString("Quads     : ").append(QString::number(nquad)) );  
    
    glColor3f(1.0 , 0.0, 0);
    renderText(5,
               40,
               QString("Others    : ").append(QString::number(nother)) );  

    glColor3f(1.0 , 1.0, 1.0);
    renderText(5,
               55,
               QString("Vertices  : ").append(QString::number(nvertex)) );  
    
//     glEnable(GL_LIGHTING);
//     glEnable(GL_LIGHT0);
    glPopAttrib();
    
  }
  
}

/**************************************************************
 *
 *  set the model
 *  @param faces the model
 *
 *************************************************************/
void
Canvas3D::setModel(Faces& faces)
{
  qDebug("Canvas3D : dans setModel");
  
  _renderer.setModel(faces);  
  updateGL();

  qDebug("Canvas3D : fin  de set Model");
  
}


void
Canvas3D::initializeGL()
{
  glEnable     (GL_DITHER);
  glEnable     (GL_DEPTH_TEST);
  glClearColor (0, 0, 0, 0);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  
  //  glPolygonMode(GL_FRONT, GL_LINE);
//   GLfloat mat_diffuse[] = {1.0, 1.0, 0, 1.0};
//   GLfloat mat_specular[] = {0, 1.0, 1.0, 1.0};
//   GLfloat shininess = 100.0;
  
  GLfloat light_position[] = {0.0, 10.0, 0.0, 0.0};
  GLfloat spot_direction[] = {0.0, -1.0, 0.0};
 
//   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
//   glMaterialf(GL_FRONT, GL_SHININESS, shininess);
  
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  //  glLightfv(GL_LIGHT0, GL_DIFFUSE, mat_diffuse);

  glLightf (GL_LIGHT0, GL_SPOT_CUTOFF, 12.5);
  glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
  glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 20.0);

//   glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
//   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
  
  
  //TODO: Remove it and compute the normal inside the objet
//  glEnable(GL_NORMALIZE);  

  
  //Renderer initialization
  qDebug("************************ OPEN GL INITIALIZATION *********************");
    
  
  buildAxesDPL();

  _renderer.initDPL();

  
  _chronometer.start();
}

void
Canvas3D::paintGL()
{
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();
  
  setView();
  
  drawAxes();
  
  _renderer.render();

  glFlush();

  drawBoundingBox();
  drawNormals();
  drawInfo();
  
  glFlush();
  
  
  _nFps++;
  drawFps();
}

void
Canvas3D::resizeGL(int width, int height)
{
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(_camera._fovy,
                 (double)width/(double)height,
                 0.01,
                 200.0);
}

/**************************************************************
 *
 *  get the renderer
 *  @return the renderer
 *
 *************************************************************/
Renderer&
Canvas3D::renderer()
{
  return _renderer;
}

/**************************************************************
 *
 *  get the mainWindow reference
 *
 *************************************************************/
MainWindow& Canvas3D::getMW() {
  return *_mw;
}


void
Canvas3D::mousePressEvent(QMouseEvent* event)
{
  _clickPos[0] = event->x();
  _clickPos[1] = event->y();

  qDebug("click en position [ %d, %d] \n", _clickPos[0], _clickPos[1]);
    
  updateGL();
}

void
Canvas3D::mouseMoveEvent(QMouseEvent* event)
{
  
  std::cout << " MOVE position x = " << event->x() 
            << " position y = " << event->y() << std::endl;
  
}

void
Canvas3D::mouseReleaseEvent(QMouseEvent* event)
{
  std::cout << " RELEASE "
            << "position x = " << event->x() 
            << " position y = " << event->y() << std::endl;
  
}

/**************************************************************
 *
 *  manage accel Event 
 *  @param id the ID of the event
 *
 *************************************************************/
void
Canvas3D::accelEvent(int id)
{

  qDebug("AccelEvent id recu = %d\n", id);

  switch(id)
  {
    case CAMERA_TURN_RIGHT:
    {
      _camera.incrementPsi();
      updateGL();
      break;
    }

    case CAMERA_TURN_LEFT:
    {
      _camera.decrementPsi();
      updateGL();
      break;
    }

    case CAMERA_TURN_DOWN:
    {
      _camera.incrementTheta();
      updateGL();
      break;
    }
            
    case CAMERA_TURN_UPPER:
    {
      _camera.decrementTheta();
      updateGL();
      break;
    }

    case CAMERA_TURN_AROUND_RIGHT:
    {
      _camera.incrementPhi();
      updateGL();
      break;
    }

    case CAMERA_TURN_AROUND_LEFT:
    {
      _camera.decrementPhi();
      updateGL();
      break;
    }

    case CAMERA_MOVE_AWAY:
    {
      _camera.incrementDistance();
      updateGL();
      break;
    }

    case CAMERA_MOVE_CLOSER:
    {
      _camera.decrementDistance();
      updateGL();
      break;
    }
    
    case ENABLE_DRAW_BOUNDING_BOX:
    {
      QString message("bounding box display toggled");
      _mw->getEventsWindow().writeComments( message );
      _boundingBoxEnabled = !_boundingBoxEnabled;
      updateGL();
      break;
    }
    
    case ENABLE_DRAW_AXES:
    {
      QString message( "axes diplay toggled");
      _mw->getEventsWindow().writeComments( message );
      _axesEnabled = !_axesEnabled;
      updateGL();
      break;
    }

    case ENABLE_DRAW_FPS:
    {
      QString message("fps informations toggled");
      _mw->getEventsWindow().writeComments( message );
      _fpsEnabled = !_fpsEnabled;
      updateGL();
      break;
    }    

    case ENABLE_DRAW_INFO_MODEL:
    {
      QString message("Informations toggled");
      _mw->getEventsWindow().writeComments(message);
      _infoEnabled = !_infoEnabled;
      updateGL();
      break;
    }    

    case WIREFRAME_RENDERING_MODE:
    {
      QString message("Wireframe rendering mode");
      _mw->getEventsWindow().writeComments(message);
      _renderer.setRenderMode(Renderer::WF);

      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

      
      glDisable(GL_LIGHT0);
      glDisable(GL_LIGHTING);
      
      //  glDisable( GL_COLOR_MATERIAL ) ;
      
      updateGL();
      break;
    }    
    
    case FLAT_RENDERING_MODE:
    {
      QString message("Flat rendering mode");
      _mw->getEventsWindow().writeComments( message );
      _renderer.setRenderMode(Renderer::FLAT);

      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      glShadeModel(GL_FLAT);

      glEnable(GL_LIGHTING);
      glEnable(GL_LIGHT0);

      //  glEnable( GL_COLOR_MATERIAL ) ;
      //glColorMaterial( GL_FRONT_AND_BACK , GL_AMBIENT_AND_DIFFUSE ) ;
      
      updateGL();
      break;
    }
        
    case GOURAUD_RENDERING_MODE:
    {
      QString message("Gouraud rendering mode");
      _mw->getEventsWindow().writeComments( message );
      _renderer.setRenderMode(Renderer::GOURAUD);

      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      glShadeModel(GL_SMOOTH);

      glEnable(GL_LIGHTING);
      glEnable(GL_LIGHT0);

      //    glEnable( GL_COLOR_MATERIAL ) ;
//      glColorMaterial( GL_FRONT_AND_BACK , GL_AMBIENT_AND_DIFFUSE ) ;
    
      updateGL();
      break;
    }
        
    case WF_HDLR_RENDERING_MODE:
    {
      QString message("Wireframe HDLR rendering mode");
      _mw->getEventsWindow().writeComments( message );
      _renderer.setRenderMode(Renderer::WF_HDLR);
      updateGL();
      break;
    }

    case NORMAL_RENDERING_MODE:
    {
      QString message("normal display toggled");
      _mw->getEventsWindow().writeComments( message );
      _normalEnabled = !_normalEnabled;
      updateGL();
      break;
    }
        
    default:
      break;
  }

  std::cout << _camera << std::endl;
}

