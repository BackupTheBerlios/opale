#include "abscanvas.hpp"


AbsCanvas::AbsCanvas(QWidget* parent, const char* name)
    : QGLWidget(parent, name),
      _nFps(0),
      _fpsEnabled(false)
{
  setCameraPosition(0, 0, 100);
  setCameraUp(0, 1, 0);
  setCameraLookAt(0, 0, 0);
}

AbsCanvas::~AbsCanvas()
{
}

void
AbsCanvas::setView()
{
  glMatrixMode (GL_MODELVIEW);   
  glLoadIdentity();

  gluLookAt (_camera._position[0],
             _camera._position[1],
             _camera._position[2],
             _camera._lookat[0],
             _camera._lookat[1],
             _camera._lookat[2],
             _camera._up[0],
             _camera._up[1],
             _camera._up[2]);
}

void
AbsCanvas::drawFps()
{
  if (_fpsEnabled)
  {
    double seconds = _chronometer.elapsed()/1000.0;
    
    if (seconds > 5)
    {
      double fps = _nFps / seconds;
      std::cout << "FPS = " << fps << std::endl;

      renderText(FPS_X_OFFSET,
                 height() - FPS_Y_OFFSET,
                 QString("FPS").append(QString::number(fps)) );
      
      _nFps = 0;
      _chronometer.restart();
    }
  }
}

void
AbsCanvas::setCameraPosition(gml::Point3D const& new_position)
{
  _camera._position = new_position;
}


void
AbsCanvas::setCameraPosition(double px, double py, double pz)
{
  _camera._position[0] = px;
  _camera._position[1] = py;
  _camera._position[2] = pz;
}

void
AbsCanvas::setCameraUp(double upx, double upy, double upz)
{
  _camera._up[0] = upx;
  _camera._up[1] = upy;
  _camera._up[2] = upz;
}

void
AbsCanvas::setCameraLookAt(double cx, double cy, double cz)
{
  _camera._lookat[0] = cx;
  _camera._lookat[1] = cy;
  _camera._lookat[2] = cz;  
}
