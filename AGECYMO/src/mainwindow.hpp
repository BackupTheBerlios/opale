#ifndef CLASS_MAINWINDOW
#define CLASS_MAINWINDOW

#include <qdict.h>

#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qmessagebox.h>
#include <qmainwindow.h>
#include <qapplication.h>



#include "pluginmanager.hpp"

#include "canvas2d.hpp"
#include "canvas3d.hpp"
#include "window3d.hpp"

class PluginManager;

const QString FILE_KEY = "&File";
const QString HELP_KEY = "&Help";

class MainWindow : public QMainWindow
{
  Q_OBJECT

  private:


  
  
  const char* TITLE;
    
  int _screen_w; //screen's width
  int _screen_h; //screen's height
  
  Window3D* _w3d;
  Window3D* _wChemin;
  Window3D* _wSection;
  Window3D* _wProfil;
  
//   Window3D* _wXY;
//   Window3D* _wXZ;
//   Window3D* _wYZ;


  QDict<QPopupMenu> _menus;
  
  
  PluginManager*  _pluginManager;
  
  
  public:
  MainWindow( int screen_w,
              int screen_h,
              int w_app = 800,
              int h_app = 50,
              int x_app = 20,
              int y_app = 0,
              QWidget* parent = 0,
              const char* name = 0);

  ~MainWindow();

  //methods used by plugins !

  //Those functions return a pointer to manipulate the canvas
  Canvas3D& getCanvas3D(); 
  Canvas2D& getCheminCanvas();
  Canvas2D& getProfilCanvas();
  Canvas2D& getSectionCanvas();

  //Function to manage the model
  Faces& model();

  void setModel(Faces & faces);
  
  
  
  
  
  private:

  void initViewFrames();
  void updateViewFramesPosition();

  void addStaticMenuBarContent();
  
  
  protected:
  virtual void moveEvent(QMoveEvent* event);

  public slots:

  void about();
  
 

};

#endif
