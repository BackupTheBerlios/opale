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
//#include "plugin.hpp"
#include "point.hpp"
#include "face.hpp"
#include "tria.hpp"
#include "quad.hpp"
#include "absface.hpp"
#include "faces.hpp"
#include "canvas2d.hpp"
#include "abscurve.hpp"
#include "circle.hpp"
#include "quadri.hpp"
#include "abscurve.hpp"
#include "polyline.hpp"

using namespace std;
using namespace gml;

//Tokens for CURVES load and save

const double END                  = -1.0;
const int NB_FRAMES               = 3;
const char * SPACE                = " ";

/***************************************************************
 *  Fonction query for curves
 * 
 *  @param mainWin the principal window of the application
 *  @return 0 if success, -1 else.
 *
 *
 ***************************************************************/
extern "C"
void** query(void){
  
  void** parameters = new void*[5];

  //Plugin's type
  PluginType* type = new PluginType(LOAD_AND_SAVE);

  //Plugin's name
  std::string *name = new string("ioCURVES");

  //Total number of entries in the different components 
  unsigned short *nbEntries = new unsigned short(2);

  //Load action 
  MenuAddOn *menuLoadAdd = new MenuAddOn();
  menuLoadAdd->typeAppel = LOAD_CALL;
  menuLoadAdd->emplacement = new string(PluginManager::MENUBAR_CMP);
  menuLoadAdd->emplacement->append("/&File/Load Curves");
  menuLoadAdd->image = new string("up.png");
  menuLoadAdd->texte = new string("CTRL+M");
  

  //Save Action 
  MenuAddOn *menuSaveAdd = new MenuAddOn();
  menuSaveAdd->typeAppel = SAVE_CALL;
  menuSaveAdd->emplacement = new string(PluginManager::MENUBAR_CMP);
  menuSaveAdd->emplacement->append("/&File/Save Curves");
  menuSaveAdd->image = new string("down.png");
  menuSaveAdd->texte = new string("CTRL+P");

  qDebug("INSIDE PLUGIN : Query IOCURVES type  = %d", *type);
    
  parameters[0] = type;
  parameters[1] = name;
  parameters[2] = nbEntries;
  parameters[3] = menuLoadAdd;
  parameters[4] = menuSaveAdd;

  return parameters;
}



/***************************************************************
 *  Fonction load for curves
 * 
 *  @param mainWin the principal window of the application
 *  @return 0 if success, -1 else.
 *
 *
 ***************************************************************/
extern "C"
int load(MainWindow *mainWin){
  int frameCpt = 0;
  unsigned short toolType;
  AbsCurve *figure;
  double xCoord, yCoord;
  gml::Point3D point;

  // The user chooses a file in order to load a VRML model
  QString fileName = 
    QFileDialog::getOpenFileName(".",
				 "*.cur",
				 mainWin,
				 "CURVES load dialog box",
				 "choose a name for CURVES load" );

  // If no name defined exit
  if(fileName.isEmpty()){
    return EXIT_FAILURE;
  }

  //opening file for writing
  ifstream file(fileName.latin1());


  while(frameCpt != NB_FRAMES){
    
    file>>toolType;

    if(frameCpt == CHEMIN_CANVAS){
      
      cout<<"chemin load"<<endl;

      if(toolType == CIRCLE_MODE){
	figure = new Circle(&mainWin->getCheminCanvas());
      }
      else if(toolType == REC_MODE){
	figure = new Quadri(&mainWin->getCheminCanvas());
      }
      else if(toolType == NURBS_MODE){
	figure = NULL;
      }
      else if(toolType == POLY_MODE){
	figure = new Polyline(&mainWin->getCheminCanvas());
      }
      else{
	figure = NULL;
      }
      
      file>>point[0];
      while(point[0] != -1.0){
	file>>point[1];
	figure->addPoint(point);
	file>>point[0];
      }

      (mainWin->getCheminCanvas()).setFigure(figure);
    }
    
    if(frameCpt == SECTION_CANVAS){

      cout<<"section load"<<endl;

      if(toolType == CIRCLE_MODE){
	figure = new Circle(&mainWin->getSectionCanvas());
      }
      else if(toolType == REC_MODE){
	figure = new Quadri(&mainWin->getSectionCanvas());
      }
      else if(toolType == NURBS_MODE){
	figure = NULL;
      }
      else if(toolType == POLY_MODE){
	figure = new Polyline(&mainWin->getSectionCanvas());
      }
      else{
	figure = NULL;
      }

      file>>point[0];
      while(point[0] != -1.0){
	file>>point[1];
	figure->addPoint(point);
	file>>point[0];
      }

      (mainWin->getSectionCanvas()).setFigure(figure);
    }

    if(frameCpt == PROFIL_CANVAS){
      
      cout<<"profil load"<<endl;

      if(toolType == NURBS_MODE){
	figure = NULL;
      }
      else if(toolType == POLY_MODE){
	cout<<"polyline profil created"<<endl;
	figure = new Polyline(&mainWin->getProfilCanvas());
      }
      else{
	figure = NULL;
      }

      file>>point[0];
      while(point[0] != -1.0){
	file>>point[1];
	cout<<"add point to profil polyline"<<endl;
	figure->addPoint(point);
	file>>point[0];
      }

      (mainWin->getProfilCanvas()).setFigure(figure);
    }


    frameCpt++;
  }

  //file closing
  file.close();

  return EXIT_SUCCESS;
}


/***************************************************************
 *  Fonction save for curves
 * 
 *  @param mainWin the principal window of the application
 *  @return 0 if success, -1 else.
 *
 *
 ***************************************************************/
extern "C"
int save(MainWindow *mainWin){

  AbsCurve *figure;
  gml::Point3D point;

  //user chooses a name for wrl file
  QString fileName = QFileDialog::getSaveFileName(
    ".",
    "*.cur",
    mainWin,
    "VRML save dialog box",
    "choose a name for VRML save" );

  //if no name defined exit
  if(fileName.isEmpty()){
    return EXIT_FAILURE;
  }

  fileName = fileName + ".cur";

  //opening file for writing
  ofstream file(fileName.latin1());


  /************ chemin canvas **********************/
  
  figure = (mainWin->getCheminCanvas()).getFigure();
  if(figure != NULL){
    if((mainWin->getCheminCanvas()).getToolMode() == CIRCLE_MODE){
      file<<CIRCLE_MODE<<SPACE;
    }
    else if((mainWin->getCheminCanvas()).getToolMode() == NURBS_MODE){
      file<<NURBS_MODE<<SPACE;
    }
    else if((mainWin->getCheminCanvas()).getToolMode() == REC_MODE){
      file<<REC_MODE<<SPACE;
    }
    else{
      file<<POLY_MODE<<SPACE;
    }
  }
  else{
    file<<NO_TOOL_MODE<<SPACE;
  }
  
  if(figure != NULL){
    for(int i = 0; i<figure->getNbPoints(); i++){
      point = figure->getPoint(i);
      file<<point[0]<<SPACE<<point[1]<<SPACE;
    }
  }
  file<<END<<endl;



  /************ section canvas **********************/
  figure = (mainWin->getSectionCanvas()).getFigure();
  if(figure != NULL){
    if((mainWin->getSectionCanvas()).getToolMode() == CIRCLE_MODE){
      file<<CIRCLE_MODE<<SPACE;
    }
    else if((mainWin->getSectionCanvas()).getToolMode() == NURBS_MODE){
      file<<NURBS_MODE<<SPACE;
    }
    else if((mainWin->getSectionCanvas()).getToolMode() == REC_MODE){
      file<<REC_MODE<<SPACE;
    }
    else{
      file<<POLY_MODE<<SPACE;
    }
  }
  else{
    file<<NO_TOOL_MODE<<SPACE;
  }
  
  if(figure != NULL){
    for(int i = 0; i<figure->getNbPoints(); i++){
      point = figure->getPoint(i);
      file<<point[0]<<SPACE<<point[1]<<SPACE;
    }
  }
  file<<SPACE<<END<<endl;



  /************ profil canvas **********************/
  figure = (mainWin->getProfilCanvas()).getFigure();
  if(figure != NULL){
    if((mainWin->getProfilCanvas()).getToolMode() == CIRCLE_MODE){
      file<<CIRCLE_MODE<<SPACE;
    }
    else if((mainWin->getProfilCanvas()).getToolMode() == NURBS_MODE){
      file<<NURBS_MODE<<SPACE;
    }
    else if((mainWin->getProfilCanvas()).getToolMode() == REC_MODE){
      file<<REC_MODE<<SPACE;
    }
    else{
      file<<POLY_MODE<<SPACE;
    }
  }
  else{
    file<<NO_TOOL_MODE<<SPACE;
  }
  
  if(figure != NULL){
    for(int i = 0; i<figure->getNbPoints(); i++){
      point = figure->getPoint(i);
      file<<point[0]<<SPACE<<point[1]<<SPACE;
    }
  }
  file<<END<<endl;

  
  //file closing
  file.close();

  return EXIT_SUCCESS;
}
