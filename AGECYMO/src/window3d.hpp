#ifndef CLASS_WINDOW3D
#define CLASS_WINDOW3D

#include <qframe.h>
#include <qlayout.h>

#include "abscanvas.hpp"
#include "canvas3d.hpp"

/******************************************************
 *  derived from QFrame. openGL 3D window
 *
 ******************************************************/
class Window3D : public QFrame
{
  private:

  static const int MID_LINE_WIDTH = 3;
  
  static int frame_cpt;
    
  const QString TITLE;
  
  QBoxLayout _layout;
  AbsCanvas* _canvas;
    
  public:

  /**************************************************************
   *
   *  Window3D constructor
   *  @param parent the parent canvas
   *  @param name the name
   *
   *************************************************************/
  Window3D(QWidget* parent = 0,
           const char* name= 0);

  /**************************************************************
   *
   *  Window3D destructor
   *
   *************************************************************/
  virtual ~Window3D();

  /**************************************************************
   *
   *  attach a canvas to this
   *  @param the abscanvas to attach
   *
   *************************************************************/
  void attachCanvas(AbsCanvas *abscanvas);

  /**************************************************************
   *
   *  get the attached AbsCanvas
   *  @return the attached AbsCanvas
   *
   *************************************************************/
  AbsCanvas& canvas();
  
  /**************************************************************
   *
   *  set the position of the camera
   *  @param newPosition a vector for camera position
   *
   *************************************************************/
  void setCameraPosition(gml::Point3D const& new_position);

  /**************************************************************
   *
   *  set the camera position
   *  @param px x coordinate of camera
   *  @param py y coordinate of camera
   *  @param pz z coordinate of camera
   *
   *************************************************************/
  void setCameraPosition(double px, double py, double pz);

  /**************************************************************
   *
   *  define the up vector of the camera
   *  @param px x coordinate of camera
   *  @param py y coordinate of camera
   *  @param pz z coordinate of camera
   *
   *************************************************************/
  void setCameraUp(double upx, double upy, double upz);

  
};

#endif
