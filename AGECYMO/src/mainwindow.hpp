#ifndef CLASS_MAINWINDOW
#define CLASS_MAINWINDOW

//qt stuff
#include <qdict.h>
#include <qstringlist.h>
#include <qkeysequence.h>
#include <qaction.h>
#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qmessagebox.h>
#include <qmainwindow.h>
#include <qapplication.h>
#include <qsignalmapper.h>
#include <qiconset.h>
#include <qpixmap.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>

//Our stuff
#include "pluginmanager.hpp"

#include "canvas2d.hpp"
#include "canvas3d.hpp"
#include "window3d.hpp"

class PluginManager;

const QString INPUT_COMPONENT_SEPARATOR = "/";

const QString FILE_KEY = "&File";
const QString HELP_KEY = "&Help";

const QString IMAGES_DIR = "../images/";
const QString QUIT_IMAGE = "exit.png";


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

  QDict<QPopupMenu> _menus;
  
  PluginManager*  _pluginManager;

  QToolBar*       _toolBar;
  
  
  public:
  MainWindow( int screen_w,
              int screen_h,
              int w_app = 50,
              int h_app = 70,
              int x_app = 10,
              int y_app = 0,
              QWidget* parent = 0,
              const char* name = 0);

  ~MainWindow();


  //This is the main method which update the GUI
  //according to the plugin's data
  void updateGUIWithPluginData(const QString & pluginID,
                               PluginType type,
                               std::vector<MenuAddOn *> & infos);
  
    
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

  void initViewFrames(int screen_height, int frame_width, int application_width = 50);
  
  void updateViewFramesPosition();

  void addStaticMenuBarContent();
  
  
  protected:
  virtual void moveEvent(QMoveEvent* event);

  public slots:

  void about();
  
 

};

#endif
