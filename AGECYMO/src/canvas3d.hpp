#ifndef CLASS_CANVAS3D
#define CLASS_CANVAS3D


#include <qaccel.h>

#include "point.hpp"
#include "camera.hpp"
#include "abscanvas.hpp"
#include "renderer.hpp"
#include "mainwindow.hpp"

#include "cylinderGenerator.hpp"

class CylinderGenerator;
class MainWindow;

/******************************************************
 *  dirived from AbsCanvas.manage a canvas for 3D context
 *
 ******************************************************/
class Canvas3D : public AbsCanvas   //public QGLWidget
{
  Q_OBJECT
  
  public:

  /******************************************************
   *  enum for accelerator key
   *
   ******************************************************/
  enum AccelKey
  {
    CAMERA_TURN_RIGHT ,
    CAMERA_TURN_LEFT  ,
    CAMERA_TURN_DOWN  ,
    CAMERA_TURN_UPPER ,
    CAMERA_TURN_AROUND_LEFT,
    CAMERA_TURN_AROUND_RIGHT,
    CAMERA_MOVE_AWAY  ,
    CAMERA_MOVE_CLOSER,
    CAMERA_MOVE_UP,
    CAMERA_MOVE_DOWN,
    CAMERA_MOVE_LEFT,
    CAMERA_MOVE_RIGHT,
    ENABLE_DRAW_AXES,         // F1 Key
    ENABLE_DRAW_FPS,          // F2 Key
    ENABLE_DRAW_BOUNDING_BOX, // F3 Key
    ENABLE_DRAW_INFO_MODEL,   // F4 Key. Number of quads, tria etc
    WIREFRAME_RENDERING_MODE, // F5 Key
    FLAT_RENDERING_MODE,      // F6
    GOURAUD_RENDERING_MODE,   // F7
    WF_HDLR_RENDERING_MODE,   // F8
    NORMAL_RENDERING_MODE,    // F9 displays the normals too.
  };

  private:
  
  MainWindow* _mw; /**referenceto the mainWindow*/

  Renderer _renderer; /**the renderer class*/

  bool     _axesEnabled; /**if axe mode enabled*/
  bool     _boundingBoxEnabled; /**if bounding box mode enabled*/
  bool     _normalEnabled; /**if normal mode enabled*/
  bool     _infoEnabled; /**if info mode enabled*/
  
  
  gml::Point2D _clickPos; /**position saved when the user clicks*/

  gml::Point3D _lightPos; /**position of the light which is used for gouraud shading*/
  
  QAccel*  _accel; /**accelerator key*/
  
  
  public:

  /**************************************************************
   *
   *  Canvas3D constructor
   *  @param mw the reference to the mainWindow
   *  @param parent the parent widget
   *  @param name the name
   *
   *************************************************************/
  Canvas3D(MainWindow* mw, QWidget* parent = 0, const char* name = 0);

  /**************************************************************
   *
   *  Canvas3D destructor
   *
   *************************************************************/
  ~Canvas3D();
  
  /**************************************************************
   *
   *  get the renderer
   *  @return the renderer
   *
   *************************************************************/
  Renderer& renderer();

  /**************************************************************
   *
   *  draw the bounding box
   *
   *************************************************************/
  void  drawBoundingBox();

  /**************************************************************
   *
   *  draw the normals
   *
   *************************************************************/
  void  drawNormals();
  
  /**************************************************************
   *
   *  draw info about model
   *
   *************************************************************/
  void  drawInfo();
  
  /**************************************************************
   *
   *  set the model
   *  @param faces the model
   *
   *************************************************************/
  void  setModel(Faces& faces);

  /**************************************************************
   *
   *  get the mainWindow reference
   *
   *************************************************************/
  MainWindow& getMW();
  
  protected:

  virtual void initializeGL     ();
  virtual void paintGL          ();
  virtual void resizeGL         (int, int);  
  
  virtual void mousePressEvent  (QMouseEvent *);
  virtual void mouseMoveEvent   (QMouseEvent *);
  virtual void mouseReleaseEvent(QMouseEvent *);

  
  private:

  /**************************************************************
   *
   *  build the display lists for axes
   *
   *************************************************************/
  void buildAxesDPL();

  /**************************************************************
   *
   *  draw the axes
   *
   *************************************************************/
  void drawAxes();


  private slots:

  /**************************************************************
   *
   *  manage accel Event 
   *  @param id the ID of the event
   *
   *************************************************************/
  void accelEvent(int id);
  
 
};


#endif
