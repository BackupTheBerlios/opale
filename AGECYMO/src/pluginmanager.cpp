#include "pluginmanager.hpp"


const char*   PluginManager::QUERY_SYMBOL = "query";
const char*   PluginManager::RUN_SYMBOL = "run";

const QString PluginManager::PLUGIN_EXT("plg");
const QString PluginManager::PLUGIN_DIR ("./plugins/");



PluginManager::PluginManager(MainWindow* appli)
{
  _mw = appli;  
}

PluginManager::~PluginManager()
{

  //Unload every loaded plugin
  qDebug("Destructor : PluginManager");
  
  QMap< QString,  QPair<bool, HandleType> >::Iterator it;
  
  for ( it = _plugins.begin(); it != _plugins.end(); ++it )
  {
    if (it.data().first) //loaded ?
    {
      qDebug("plugin %s unloaded", it.key().latin1());
      dlclose(it.data().second);
    }
  }
  
}



void
PluginManager::readAvailablePlugins()
{
  QDir pluginDir(PLUGIN_DIR);

  if (pluginDir.exists())
  {
    pluginDir.setFilter(QDir::Files | QDir::NoSymLinks);

    //preparing to read the plugins
    //Code taken from the Qt documentation
    const QFileInfoList *list = pluginDir.entryInfoList();
    QFileInfoListIterator it( *list );
    QFileInfo *fileInfo;

    while ( (fileInfo = it.current()) != 0 )
    {
      if (fileInfo->extension() == PLUGIN_EXT)
      {
        std::cout << "Found a plugin named :" << fileInfo->fileName() << std::endl;

        loadAndUnloadPlugin(fileInfo->filePath());
        
        
      }
      ++it;
    }


  }
  else
  {
    std::cerr << "The plugins directory does NOT exist !!!! NO PLUGINS LOADED" << std::endl;
  }
    
}

void
PluginManager::executePlugin(const QString & pluginFullName)
{
 //TODO : to return an error code or a success code ?

  //Maybe this test should be removed in the future...
  if ( !( _plugins.contains(pluginFullName) ) )
  {
    //Strange trying to execute a plugin which does not exist !!
    qWarning("Plugin %s NOT FOUND in the inner MAP of the pluginManager!!!",
             pluginFullName.latin1());
    return;
  }
  
  if ( !(_plugins[pluginFullName].first) ) // if the plugin is not loaded then load it !
  {
    loadPlugin(pluginFullName);    
  }
  
  //Try to call the run function
  runFunction run = (runFunction) dlsym(_plugins[pluginFullName].second,
                                        RUN_SYMBOL);

  if(!run)
  {
    qDebug("Plugin handler address is %p", _plugins[pluginFullName].second);
    qWarning("Plugin %s run Function not found !!!", pluginFullName.latin1());
    return;
  }

  //TODO : to pass the appropriate arguments to the run function
  int returnCode = run(NULL);

  if (returnCode != EXIT_SUCCESS)
  {
    qDebug("Plugin handler address is %p", _plugins[pluginFullName].second);
    qWarning("FAILED TO LAUNCH Plugin %s !!!", pluginFullName.latin1());
  }
    
}

void
PluginManager::loadPlugin(const QString & pluginFullName)
{
  //TODO: to implement it or to delete it...
}

void
PluginManager::unloadPlugin(HandleType handler)
{
  //TODO: to implement it or to delete it...
}


void
PluginManager::loadAndUnloadPlugin(const QString & pluginFullName)
{
  //TODO: to use the load and unloadPlugin functions ???
  
  HandleType handler = dlopen(pluginFullName, RTLD_NOW | RTLD_GLOBAL);

  if (!handler)
  {
    qWarning("Unable to load the plugin %s\n", pluginFullName.latin1() );
    return;
  }
  
  //Plugin Succesfully loaded  !!
  qDebug("Plugin %s succesfully loaded", pluginFullName.latin1() );
  qDebug("pointer plugin address is %p", handler);
  
  
  //Try to Query it !
  queryFunction query = (queryFunction) dlsym(handler, QUERY_SYMBOL);

  
  if (!query) //query function not found. Typically the plugin
              //does not fit to the required interface for the query function
  {
    dlclose(handler);
    qWarning("query function not found \n Plugin %s will not be USED !!!",
             pluginFullName.latin1());
    return;
  }
  
  //The query function is ok
  // First we call the Query function to retrieve information about the plugin
  // and how we should use it

  void** infos = query();
  
  
  //Then we update the GUI because the functionalities
  //provided by the plugin should work

  //TODO: to call the appropriate method in the MainWindow class
        
  //finally we unload the plugin and store it as available but not loaded...
  _plugins[ pluginFullName ] = qMakePair(false, handler);
  dlclose(handler);

  qDebug("Plugin %s at address %p successfully unloaded",
         pluginFullName.latin1(),
         handler);
}
