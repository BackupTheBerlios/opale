#include <cstdlib>
#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>


//Qt stuff
#include <qapplication.h>
#include <qfiledialog.h>
#include <qmessagebox.h>

//Our stuff
#include "mainwindow.hpp"
#include "point.hpp"
#include "face.hpp"
#include "tria.hpp"
#include "quad.hpp"
#include "absface.hpp"
#include "faces.hpp"

using namespace std;
using namespace gml;


extern "C"
void** query(void)
{
  void** parameters = new void*[5];

  //Plugin's type
  PluginType* type = new PluginType(LOAD_AND_SAVE);

  //Plugin's name
  std::string *name = new string("ioPLY");

  //Total number of entries in the different components 
  unsigned short *nbEntries = new unsigned short(2);

  //Load action 
  MenuAddOn *menuLoadAdd = new MenuAddOn();
  menuLoadAdd->typeAppel = LOAD_CALL;
  menuLoadAdd->emplacement = new string(PluginManager::MENUBAR_CMP);
  menuLoadAdd->emplacement->append("/&File/Import/An PLY Model");
  menuLoadAdd->image = NULL;
  menuLoadAdd->texte = NULL;
  

  //Save Action 
  MenuAddOn *menuSaveAdd = new MenuAddOn();
  menuSaveAdd->typeAppel = SAVE_CALL;
  menuSaveAdd->emplacement = new string(PluginManager::MENUBAR_CMP);
  menuSaveAdd->emplacement->append("/&File/Export To/An PLY Model");
  menuSaveAdd->image = NULL;
  menuSaveAdd->texte = NULL;

  qDebug("INSIDE PLUGIN : Query OBJ type  = %d", *type);
  
  
  parameters[0] = type;
  parameters[1] = name;
  parameters[2] = nbEntries;
  parameters[3] = menuLoadAdd;
  parameters[4] = menuSaveAdd;

  return parameters;
}


extern "C"
int load(MainWindow *mainW)
{
  qDebug("Dans load du PLUGIN ioPLY ");
}


extern "C"
int save(MainWindow *mainWin)
{
  qDebug("Dans Save du PLUGIN ioPLY ");
  
}
