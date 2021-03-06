#include "pluginmanager.hpp"

#include "mainwindow.hpp"


#include <iostream>
#include <vector>

// Type of components which may be pluged.
const char* PluginManager::MENUBAR_CMP  = "/Menu";
const char* PluginManager::TOOLBAR_CMP  = "/Toolbar";

const char* PluginManager::QUERY_SYMBOL = "query";
const char* PluginManager::RUN_SYMBOL   = "run";

const char* PluginManager::LOAD_SYMBOL  = "load";
const char* PluginManager::SAVE_SYMBOL  = "save";


const QString PluginManager::PLUGIN_EXT("plg");
const QString PluginManager::PLUGIN_DIR("./plugins/");


/**************************************************************
 *
 *  PluginManager constructor
 *  @param parent the parent canvas
 *
 *************************************************************/
PluginManager::PluginManager(MainWindow* appli)
{
  _mw = appli;  
}

/**************************************************************
 *
 *  PluginManager destructor
 *
 *************************************************************/
PluginManager::~PluginManager()
{

  //Unload every loaded plugin
  qDebug("Destructor : PluginManager");

  //TODO : destroy the QDict one way or the other...
}

/**************************************************************
 *
 *  record the plugins
 *
 *************************************************************/
void
PluginManager::recordAvailablePlugins()
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

        loadPlugin(fileInfo->filePath()); 
      }
      ++it;
    }
  }
  else
  {
    qWarning("The plugins directory does NOT exist !!!! NO PLUGINS LOADED");
  }
    
}
 
/**************************************************************
 *
 *  launch the plugin's run function
 *  @param pluginFullName the full name of the plugin
 *
 *************************************************************/
void
PluginManager::executeRun(const QString & pluginFullName)
{
  
}

/**************************************************************
 *
 *  launch the plugin's load function
 *  @param pluginFullName the full name of the plugin
 *
 *************************************************************/
void
PluginManager::executeLoad(const QString & pluginID)
{
  PluginHandler* plgh;
  plgh = reloadPlugin(pluginID);

  if (plgh != NULL)
  {
    loadFunction lf = *(plgh->load);
    lf(_mw);
    unloadPlugin(pluginID);
  }
  else
  {
    qWarning("Unable to execute the LOAD function. Problem while reloading plugin %s", pluginID.latin1());
  }
  
}

/**************************************************************
 *
 *  launch the plugin's save function
 *  @param pluginFullName the full name of the plugin
 *
 *************************************************************/
void
PluginManager::executeSave(const QString & pluginID)
{
  PluginHandler* plgh;
  plgh = reloadPlugin(pluginID);

  if (plgh != NULL)
  {
    saveFunction sf = *(plgh->save);
    sf(_mw);
    unloadPlugin(pluginID);
  }
  else
  {
    qWarning("Unable to execute the SAVE function. Problem while reloading plugin %s", pluginID.latin1());
  }
  
}

//void
//PluginManager::executePlugin(const QString & pluginFullName)
//{
 //TODO : to implement to allow action plugin

//   //Maybe this test should be removed in the future...
//   if ( !( _actionPlugins.contains(pluginFullName) ) )
//   {
//     //Strange trying to execute a plugin which does not exist !!
//     qWarning("Plugin %s NOT FOUND in the inner MAP of the pluginManager!!!",
//              pluginFullName.latin1());
//     return;
//   }
  
//   if ( !(_actionPlugins[pluginFullName].first) ) // if the plugin is not loaded then load it !
//   {
//     loadPlugin(pluginFullName);    
//   }
  
//   //Try to call the run function
//   runFunction run = (runFunction) dlsym(_actionPlugins[pluginFullName].second,
//                                         RUN_SYMBOL);

//   if(!run)
//   {
//     qDebug("Plugin handler address is %p", _actionPlugins[pluginFullName].second);
//     qWarning("Plugin %s run Function not found !!!", pluginFullName.latin1());
//     return;
//   }

//   //TODO : to pass the appropriate arguments to the run function
//   int returnCode = run(NULL);

//   if (returnCode != EXIT_SUCCESS)
//   {
//     qDebug("Plugin handler address is %p", _actionPlugins[pluginFullName].second);
//     qWarning("FAILED TO LAUNCH Plugin %s !!!", pluginFullName.latin1());
//   }
    
//}


//We load only once after we reload once for action plugin every time for io plugins
//Loading a plugin implies to record it
// and to call MainWindow  methods to update the GUI


/**************************************************************
 *
 *  load a plugin
 *  @param pluginFullName the full name of the plugin
 *
 *************************************************************/
void
PluginManager::loadPlugin(const QString & pluginFullName)
{
  
  HandleType handler = dlopen(pluginFullName, RTLD_NOW | RTLD_GLOBAL);

  if (!handler)
  {
    qWarning("Unable to load the plugin %s\n", pluginFullName.latin1() );
    return;
  }
  
  //Plugin Succesfully loaded  !!
  qDebug("INSIDE PLUGIN MANAGER : Plugin (%s) succesfully loaded", pluginFullName.latin1() );
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
  
  void** infos = query();
  PluginType* type    = (PluginType *)infos[0];  
  std::string    name    = *(std::string *)infos[1];
  
  qDebug( " Plugin name is %s \n", name.c_str());
  
  //We need to verify that appropriate functions are callable
  bool functionsOK = true;
  
  // Plugin POLICY : 
  // For IO plugins we always unload and reload them
  // For Action plugins we unload them too but they will only be reloaded once
  switch(*type)
  {
    case LOAD_AND_SAVE:
    {
      qDebug( " Plugin Type is LOAD AND SAVE ! \n");
      
      char * err;
      
      dlerror(); //clear all error symbol
      loadFunction load = (loadFunction) dlsym(handler, LOAD_SYMBOL);

      if ( (err = dlerror()) != NULL)
      {
        functionsOK = false;
      }
      else
      {
        dlerror(); //clear all previous error
        saveFunction save = (saveFunction) dlsym(handler, SAVE_SYMBOL);
        if ( (err = dlerror()) != NULL)
        {
          functionsOK = false;
        }
      }
      break;
    };
    
    case ACTION:
    {
      qDebug( " Plugin Type is ACTION ! \n");
      
      char *err;

      dlerror();
      loadFunction load = (loadFunction) dlsym(handler, LOAD_SYMBOL);

      if ( (err = dlerror()) != NULL)
      {
        functionsOK = false;
      }
      break;
    };
        
    default:
    {
    
      break;
    }
  }

  //all type of plugins whether they are recorded or not should be unloaded
  dlclose(handler);
  
  qDebug("Plugin %s at address %p successfully unloaded",
         pluginFullName.latin1(),
         handler);

  //if functions are OK we record the plugin
  if (functionsOK)
  {
    qDebug("Plugin %s functions OK !!! ", name.c_str());
    
        PluginHandler* plgh = new PluginHandler();
        plgh->type = *type;
        plgh->handler = NULL;
        plgh->run = NULL;
        plgh->load = NULL;
        plgh->save = NULL;
        
        _plugins.insert(pluginFullName, plgh);
  }
  else //Functions can not be call we ABORT
  {
    return;
  }
    
  //OK NOW we are sure the plugin is usable and callable
  //We prepare the update for the GUI !
  unsigned short entries = *(unsigned short *)infos[2];
  qDebug("  Number of component entries is %d \n", entries);

  //Preparing the stuffs
  //std::vector<MenuAddOn *> * menus_infos= new std::vector<MenuAddOn *>(entries);
  std::vector<MenuAddOn *> menus_infos(entries);
    
  for(int i=OFFSET_ARG; i<(OFFSET_ARG + entries); i++)
  {
    std::cout << "i = " << i << std::endl;
    menus_infos[i-OFFSET_ARG] = static_cast<MenuAddOn *>(infos[i]);
  }
    
  _mw->updateGUIWithPluginData(pluginFullName, *type, menus_infos);

  std::cout << "apres updateGUI dans pluginmanager" << std::endl;
  
  // We do not need parameters sent by query anymore so we delete it !
  delete[] infos;
  
}

/**************************************************************
 *
 *  reload a plugin
 *  @param pluginFullName the full name of the plugin
 *  @return the pluginHandler (plugin's properties)
 *
 *************************************************************/
PluginHandler*
PluginManager::reloadPlugin(const QString & pluginID)
{
  PluginHandler* plgh = _plugins[pluginID];
  
  if (plgh == 0)
  {
    //Strange trying to reload an unrecorded plugin...
    qWarning("Unknown Plugin %s !!!", pluginID.latin1());
    return NULL;
  }

    
  HandleType handler = plgh->handler;

  if (handler != NULL)
  {
    //plugin already load !!
    qWarning("Plugin %s already load !!!", pluginID.latin1());
    return plgh;
  }

  
  
  handler = dlopen(pluginID, RTLD_NOW | RTLD_GLOBAL);

  if(!handler)
  {
    qWarning("Plugin %s could NOT BE LOAD !!!! WONT BE USED !!!", pluginID.latin1());
    return NULL;
  }

  //OK we found the plugin storing it
  plgh->handler = handler;

  //Now we link the functions according to the plugin type
  //TODO : to test error ?
  //If we found the plugin we hope it did  not change since the recording...
  switch(plgh->type)
  {
    case LOAD_AND_SAVE:
    {
      loadFunction lf = (loadFunction) dlsym(plgh->handler, LOAD_SYMBOL);
      plgh->load = &lf;

      saveFunction sf = (saveFunction) dlsym(plgh->handler, SAVE_SYMBOL);
      plgh->save = &sf;
      
      break;
    }

    case ACTION:
    {
      runFunction rf = (runFunction) dlsym(plgh->handler, RUN_SYMBOL);
      plgh->run = &rf;
            
      break;
    }
    
    default:
      break;
  }

  return plgh;
}

/**************************************************************
 *
 *  unload a plugin
 *  @param pluginID the id of the plugin
 *
 *************************************************************/
void
PluginManager::unloadPlugin(QString const & pluginID)
{
  PluginHandler* plgh = _plugins[pluginID];
  
  if (plgh == 0)
  {
    //Strange trying to unload an unrecorded plugin...
    return;
  }
    
  HandleType handler = plgh->handler;

  if (handler != NULL)
  {

    //THis is the C call to the dynamic loader
    int returnCode = dlclose(handler);

    if (returnCode ==0)
    {
      //Ok plugin successfully unload !
      // Updating the the handler values 
      plgh->handler = NULL;
      plgh->run = NULL;
      plgh->load = NULL;
      plgh->save = NULL;
    }
    else
    {
      qWarning("Unabled to unload the plugin %s \n", pluginID.latin1());
    }
  }
  else
  {
    qWarning("Plugin %s already unloaded !! \n", pluginID.latin1());
  }
  
}


 

