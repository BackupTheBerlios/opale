#ifndef CLASS_PLUGINMANAGER
#define CLASS_PLUGINMANAGER

#include <dlfcn.h>

#include <string>

#include <qmap.h>
#include <qpair.h>

#include <qstring.h>

#include <qdir.h>
#include <qfileinfo.h>

#include "mainwindow.hpp"

class MainWindow;


class PluginManager
{

  //Attributes
  private:

  typedef void** (*queryFunction) (void);
  typedef int    (*runFunction) (void**);

  typedef void*  HandleType;

  
  static const char*   QUERY_SYMBOL;
  static const char*   RUN_SYMBOL;
  
  static const QString PLUGIN_EXT;
  static const QString PLUGIN_DIR;
  
  QMap< QString,  QPair<bool, HandleType> > _plugins;
  
  MainWindow*  _mw;

  
  //Public Methods
  public:

  PluginManager(MainWindow* appli);

  ~PluginManager();


  
  void readAvailablePlugins();

  // public slots:
  void executePlugin(const QString & pluginFullName);
  
  
  //Private Methods
  private:

  void loadPlugin(const QString &pluginFullName);
  void unloadPlugin(HandleType handler);
  
  void loadAndUnloadPlugin(const QString & pluginFullName);
  
  
};



#endif
