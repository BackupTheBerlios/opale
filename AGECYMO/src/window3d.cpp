#include <qstring.h>

#include "window3d.hpp"


int Window3D::frame_cpt = 1;

/**************************************************************
 *
 *  Window3D constructor
 *  @param parent the parent canvas
 *  @param name the name
 *
 *************************************************************/
Window3D::Window3D(QWidget* parent, const char* name)
    : QFrame(parent, name),
      TITLE(QString("Perspective View ") + QString::number(frame_cpt++)),
    _layout(this, QBoxLayout::LeftToRight)//,
{ 
  setMidLineWidth(MID_LINE_WIDTH);
  setFrameShape(QFrame::Panel);
  setFrameShadow(QFrame::Plain);
  setCaption(TITLE);
}

/**************************************************************
 *
 *  Window3D destructor
 *
 *************************************************************/
Window3D::~Window3D()
{
  delete _canvas;
}

/**************************************************************
 *
 *  attach a canvas to this
 *  @param the abscanvas to attach
 *
 *************************************************************/
void
Window3D::attachCanvas(AbsCanvas* acanvas)
{
  _canvas = acanvas;
  _layout.addWidget(_canvas);
}

/**************************************************************
 *
 *  get the attached AbsCanvas
 *  @return the attached AbsCanvas
 *
 *************************************************************/
AbsCanvas&
Window3D::canvas()
{
  return *(_canvas);
}

/**************************************************************
 *
 *  set the position of the camera
 *  @param newPosition a vector for camera position
 *
 *************************************************************/
void
Window3D::setCameraPosition(gml::Point3D const& new_position)
{
  // _canvas->setCameraPosition(new_position);
}

/**************************************************************
 *
 *  set the camera position
 *  @param px x coordinate of camera
 *  @param py y coordinate of camera
 *  @param pz z coordinate of camera
 *
 *************************************************************/
void
Window3D::setCameraPosition(double px, double py, double pz)
{
  //_canvas->setCameraPosition(px, py, pz);
}

/**************************************************************
 *
 *  define the up vector of the camera
 *  @param px x coordinate of camera
 *  @param py y coordinate of camera
 *  @param pz z coordinate of camera
 *
 *************************************************************/
void
Window3D::setCameraUp(double upx, double upy, double upz)
{
  //_canvas->setCameraUp( upx, upy, upz);
}

/**************************************************************
 *
 *  manage close Event. a window3D cannot be closed
 *  @param ce the close Event
 *
 *************************************************************/
void Window3D::closeEvent(QCloseEvent* ce ){
  ce->ignore();
}
