//
//  plugins load and save for the curves
//  
//

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
#include "canvas2d.hpp"
#include "polyline.hpp"
#include "nurbscurve.hpp"
#include "abscurve.hpp"
#include "circle.hpp"
#include "polygone.hpp"
#include "quadri.hpp"

using namespace std;
using namespace gml;

//Tokens for CURVES load and save
const double CONTROL_NETWORK_END  = -10.0;
const double CURVE_END            = -20.0;
const double CANVAS_END           = -30.0;
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
  Curves *figure;
  double xCoord, yCoord;
  gml::Point3D *point;
  double canvasType;
  double closeParameter;
  gml::Point3D colors;
  double curveType;
  AbsCurve *curve;
  double indexCurve;

  curve = NULL;

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
  
  for(int i = 0; i<NB_FRAMES; i++){

    //get the canvas type and create curves class
    file>>canvasType;

    if(canvasType == CHEMIN_CANVAS){
      figure = new Curves(&mainWin->getCheminCanvas());
    }
    else if(canvasType == SECTION_CANVAS){
      figure = new Curves(&mainWin->getSectionCanvas());
    }
    else if(canvasType == PROFIL_CANVAS){
      figure = new Curves(&mainWin->getProfilCanvas());
    }
    else{
      //here a log error
    }

    //get the close parameter
    file>>closeParameter;
    if(closeParameter){
      figure->close();
    }

    //get the colors
    file>>colors[0];
    file>>colors[1];
    file>>colors[2];
    figure->setColor(colors[0], colors[1], colors[2]);
    file>>colors[0];
    file>>colors[1];
    file>>colors[2];
    figure->setSelectionColor(colors[0], colors[1], colors[2]);

    //get the current tool type
    unsigned short currentToolType;
    file>>currentToolType;
    figure->setCurrentToolType(currentToolType);

    //get the control points
    file>>xCoord;
    while(xCoord != CONTROL_NETWORK_END){
      file>>yCoord;
      point = new gml::Point3D();
      (*point)[0] = xCoord;
      (*point)[1] = yCoord;
      figure->addPoint(point);
      file>>xCoord;
    }
 
    //get the curves
    file>>curveType;
    while(curveType != CANVAS_END){


      if(curveType == POLY_MODE){
	curve = new Polyline();
      }
      else if(curveType == REC_MODE){
	curve = new Quadri();
      }
      else if(curveType == POLYG_MODE){
	curve = new Polygone();
      }
      else if(curveType == CIRCLE_MODE){
	curve = new Circle();
      }
      else if(curveType == NURBS_MODE){
	curve = new NurbsCurve();
      }
      if(curve == NULL){
	//here a log error
      }

      file>>indexCurve;
      gml::Point3D *lepoint;

      //add the control points of the curve
      while(indexCurve != CURVE_END){
	curve->addPoint(figure->getPointAtIndex((unsigned)indexCurve));
	file>>indexCurve;
	cout<<indexCurve<<endl;
      }
      figure->addCurve(curve);
      file>>curveType;
    }
    
    //update all the curves
    if(canvasType == CHEMIN_CANVAS){
      (mainWin->getCheminCanvas()).setFigure(figure);
    }
    else if(canvasType == SECTION_CANVAS){
      (mainWin->getSectionCanvas()).setFigure(figure);
    }
    else if(canvasType == PROFIL_CANVAS){
      (mainWin->getProfilCanvas()).setFigure(figure);
    }
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

  Curves *figure;
  std::vector<gml::Point3D*> controlPoints;
  std::vector<AbsCurve*> curves_list;;

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


  for(int i = 0; i<NB_FRAMES; i++){
    if(i == CHEMIN_CANVAS){
      figure = (mainWin->getCheminCanvas()).getFigure();
    }
    else if(i == SECTION_CANVAS){
      figure = (mainWin->getSectionCanvas()).getFigure();
    }
    else if(i == PROFIL_CANVAS){
      figure = (mainWin->getProfilCanvas()).getFigure();
    }

    //write the figure object

    if(figure != NULL){

      //write the canvas type
      file<<i<<SPACE;
      
      //write the close parameter
      if(figure->isClosed()){
	file<<1.0;
      }
      else{
	file<<0.0;
      }
      file<<SPACE;
      
      //write color parameters
      gml::Point3D colors = figure->getColor();
      file<<colors[0]<<SPACE<<colors[1]<<SPACE<<colors[2]<<SPACE;
      colors = figure->getSelectionColor();
      file<<colors[0]<<SPACE<<colors[1]<<SPACE<<colors[2]<<SPACE;
      
      //write the current tool type
      file<<figure->getCurrentToolType()<<SPACE;
      
      //write the network points
      controlPoints = figure->getAllPoints();
      double x,y;
      for(unsigned z = 0; z<controlPoints.size(); z++){
	x = (*controlPoints[z])[0];
	y = (*controlPoints[z])[1];
	file<<x<<SPACE<<y<<SPACE;
      }
      file<<CONTROL_NETWORK_END<<SPACE;

      //write the curves
      curves_list = figure->getAllCurves();

      for(unsigned z = 0; z<curves_list.size(); z++){
	
	//write the type of the curve
	if(typeid(*curves_list[z]) == typeid(Polyline)){
	  file<<POLY_MODE<<SPACE;
	}
	else if(typeid(*curves_list[z]) == typeid(NurbsCurve)){
	  file<<NURBS_MODE<<SPACE;
	}
	else if(typeid(*curves_list[z]) == typeid(Polygone)){
	  file<<POLYG_MODE<<SPACE;
	}
	else if(typeid(*curves_list[z]) == typeid(Circle)){
	  file<<CIRCLE_MODE<<SPACE;
	}
	else if(typeid(*curves_list[z]) == typeid(Quadri)){
	  file<<REC_MODE<<SPACE;
	}
	else{
	  //here a log error
	}

	//write the index of the points
	for(int j = 0; j<curves_list[z]->getNbPoints(); j++){
	  for(unsigned k = 0; k<controlPoints.size(); k++){
	    if(curves_list[z]->getPoint(j) == controlPoints[k]){
	      file<<k<<SPACE;
	    }
	  }
	}

	file<<CURVE_END<<SPACE;
      }

      file<<CANVAS_END<<SPACE;

    }
  }

  //file closing
  file.close();

  return EXIT_SUCCESS;
}
