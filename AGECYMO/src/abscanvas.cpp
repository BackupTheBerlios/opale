#include "abscanvas.hpp"


AbsCanvas::AbsCanvas(QWidget* parent, const char* name)
    : QGLWidget(parent, name),
      _nFps(0),
      _fpsEnabled(true)
{
  _camera.setCameraPosition(0, 0, 2);
  _camera.setCameraUp(0, 1, 0);
  _camera.setCameraLookAt(0, 0, 0);
}

AbsCanvas::~AbsCanvas()
{
}

void
AbsCanvas::setView()
{

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
    int fps = static_cast<int>(_nFps / seconds);
    std::cout << "FPS = " << fps << std::endl;

    if (seconds > 1)
    {
      _nFps = 0;
      _chronometer.restart();
    }

    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);

    glColor3f(0.0 , 0.0, 1.0);
    
    renderText(FPS_X_OFFSET,
               height() - FPS_Y_OFFSET,
               QString("FPS : ").append(QString::number(fps)) );

  }
}
