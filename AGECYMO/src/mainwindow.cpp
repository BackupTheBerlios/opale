#include "mainwindow.hpp"


MainWindow::MainWindow(int screen_w,
                       int screen_h,
                       int w_app,
                       int h_app,
                       int x_app,
                       int y_app,
                       QWidget* parent,
                       const char* name)
    : QMainWindow(parent, name),
      TITLE("Another Modeler"),
      _screen_w(screen_w),
      _screen_h(screen_h)
{
  resize(w_app, h_app);
  move(x_app, y_app);
  setCaption(TITLE);
  show();

  initViewFrames();  
}

MainWindow::~MainWindow()
{
//   delete _wYZ;
//   delete _wXZ;
//   delete _wXY;

  delete _wSection;
  delete _wProfil;
  delete _wChemin;
  delete _w3d;
}

void
MainWindow::initViewFrames()
{
  _w3d = new Window3D();
  Canvas3D* _canvas3d = new Canvas3D(_w3d);
  _w3d->attachCanvas(_canvas3d);

  _wChemin = new Window3D();
  Canvas2D* _canvasChemin = new Canvas2D(_wChemin);
  _wChemin->attachCanvas(_canvasChemin);

  _wProfil = new Window3D();
  Canvas2D* _canvasProfil = new Canvas2D(_wProfil);
  _wProfil->attachCanvas(_canvasProfil);

  _wSection = new Window3D();
  Canvas2D* _canvasSection = new Canvas2D(_wSection);
  _wSection->attachCanvas(_canvasSection);
     
  int mw_w = width();
  int mw_h = height();
  int mw_w2 = mw_w / 2;
  
  int h2 = frameGeometry().height();
  int h3 = geometry().height();

  qDebug("Inside initViewFrames");
  qDebug("mw_h =  %d\n", mw_h);
  qDebug("h2 =  %d\n", h2);
  qDebug("h3 =  %d\n", h3);
  
  int f_h = (_screen_h - mw_h) / 2;
  int w_h = (f_h < mw_w2)? (f_h) : (mw_w2);

  _w3d->resize(w_h, w_h);
  _wChemin->resize(w_h, w_h);
  _wSection->resize(w_h, w_h);
  _wProfil->resize(w_h, w_h);

  
  if (w_h != mw_w2)
  {
    resize(2*w_h, mw_h);
    move(((_screen_w - 2*w_h)/2), 0);
  }

  //Set title for each frame !!
  _wChemin->setCaption("Chemin");
  _wSection->setCaption("Section");
  _wProfil->setCaption("Profil");
  
  //Moves cameras for each frame !
//   _wChemin->setCameraPosition(0, 0, 100);
//   _wSection->setCameraPosition(0, 100, 0);
//   _wSection->setCameraUp(1, 0, 0);
//   _wProfil->setCameraPosition(-100, 0, 0);
  
  //Move the frames !
  _wChemin->move(x(), h2);
  _wSection->move(x() + w_h, h2);
  _wProfil->move(x(), h2 + w_h);
  _w3d->move(x() + w_h, h2 + w_h);
  
  //ok show the frames !
  _wChemin->show();
  _wSection->show();
  _wProfil->show();
  _w3d->show();
}
void
MainWindow::updateViewFramesPosition()
{
  int h2 = frameGeometry().height();

//  _w3d.move(x() + _w3d.width(), y() + _w3d.width() + height());
}

Canvas3D&
MainWindow::getCanvas3D()
{
  return dynamic_cast<Canvas3D &>( _w3d->canvas() );
}

Canvas2D&
MainWindow::getCheminCanvas()
{
  return dynamic_cast<Canvas2D &>( _wChemin->canvas() );
}

Canvas2D&
MainWindow::getProfilCanvas()
{
  return dynamic_cast<Canvas2D &>( _wProfil->canvas() );
}

Canvas2D& 
MainWindow::getSectionCanvas()
{
  return dynamic_cast<Canvas2D &>( _wSection->canvas() );
}

Faces&
MainWindow::model()
{
  return dynamic_cast<Canvas3D &>( _w3d->canvas() ).renderer().model();
}

void
MainWindow::setModel(Faces& faces)
{
  dynamic_cast<Canvas3D &>( _w3d->canvas() ).renderer().setModel(faces);
}


//Qt EVENTS
void
MainWindow::moveEvent(QMoveEvent* event)
{
  qDebug("Move event received\n");
  updateViewFramesPosition();
}
