#include <qstring.h>

#include "window3d.hpp"


int Window3D::frame_cpt = 1;

Window3D::Window3D(QWidget* parent, const char* name)
    : QFrame(parent, name),
      TITLE(QString("Perspective View ") + QString::number(frame_cpt++)),
    _layout(this, QBoxLayout::LeftToRight)//,
//      _canvas(this)
{
//  _layout = new QBoxLayout(this, QBoxLayout::LeftToRight);

//  _canvas = acanvas;
  
  setMidLineWidth(MID_LINE_WIDTH);
  setFrameShape(QFrame::Panel);
  setFrameShadow(QFrame::Plain);
  setCaption(TITLE);

  //_layout.addWidget(_canvas);
  
}

Window3D::~Window3D()
{
  delete _canvas;
}

void
Window3D::attachCanvas(AbsCanvas* acanvas)
{
  _canvas = acanvas;
  _layout.addWidget(_canvas);
}

AbsCanvas&
Window3D::canvas()
{
  return *(_canvas);
}


void
Window3D::setCameraPosition(gml::Point3D const& new_position)
{
  // _canvas->setCameraPosition(new_position);
}

void
Window3D::setCameraPosition(double px, double py, double pz)
{
  //_canvas->setCameraPosition(px, py, pz);
}

void
Window3D::setCameraUp(double upx, double upy, double upz)
{
  //_canvas->setCameraUp( upx, upy, upz);
}
