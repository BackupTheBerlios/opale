#ifndef CLASS_WINDOW3D
#define CLASS_WINDOW3D

#include <qframe.h>
#include <qlayout.h>

#include "abscanvas.hpp"
#include "canvas3d.hpp"

class Window3D : public QFrame
{
  private:

  static const int MID_LINE_WIDTH = 3;
  
  static int frame_cpt;
    
  const QString TITLE;
  
  QBoxLayout _layout;
  AbsCanvas* _canvas;
    
  public:
  Window3D(QWidget* parent = 0,
           const char* name= 0);

  virtual ~Window3D();

  void attachCanvas(AbsCanvas *abscanvas);

  AbsCanvas& canvas();
  
  void setCameraPosition(gml::Point3D const& new_position);

  void setCameraPosition(double px, double py, double pz);

  void setCameraUp(double upx, double upy, double upz);

  
};

#endif
