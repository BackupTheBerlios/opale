#ifndef CLASS_ABSCANVAS_H
#define CLASS_ABSCANVAS_H

//Qt's objectes
#include "qdatetime.h"
#include "qstring.h"
#include "qgl.h"

//Our objects
#include "camera.hpp"

/******************************************************
 *  dirived from QGLWidget. generic canvas
 *
 ******************************************************/
class AbsCanvas : public QGLWidget
{
  Q_OBJECT

  //Public Members/Attributes
  public:
  
  //Protected Members/Attributes
  protected:
  
  static const int MIN_TIME_FOR_FPS_MEASURE = 2; /**for fps measures*/
  static const int FPS_X_OFFSET = 10; /**fps x offset*/
  static const int FPS_Y_OFFSET = 10; /**fps y offset*/

  int _nFps; /**frame per second*/
  int _fpsEnabled; /**True if we display the FPS on the Canvas false otherwise*/
  
  QTime _chronometer; /**used to count the number of frames rendered.*/
  gml::Camera _camera; /**The Camera associated*/
    
  int _axesIndexDPL; /**indexe of the display list containing the axes.*/


  //Public Methods
  public:

  /**************************************************************
   *
   *  AbsCanvas constructor
   *  @param parent the parent widget
   *  @param name the name
   *
   *************************************************************/
  AbsCanvas(QWidget* parent = 0, const char* name = 0);

  /**************************************************************
   *
   *  AbsCanvas destructor
   *
   *************************************************************/
  virtual ~AbsCanvas();

  //Protected Methods
  protected:

  /**************************************************************
   *
   *  build the display list for axes
   *
   *************************************************************/
  virtual void buildAxesDPL() = 0;

  /**************************************************************
   *
   *  draw the axes
   *
   *************************************************************/
  virtual void drawAxes() = 0;

  /**************************************************************
   *
   *  set the view according to the camera
   *
   *************************************************************/
  void setView();

  /**************************************************************
   *
   *  draw fps info
   *
   *************************************************************/
  void drawFps();
  
};



#endif
