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

using namespace std;
using namespace gml;

//Tokens for VRML load and save
const char* L_BRACE               = "{";
const char* R_BRACE               = "}";
const char* L_SBRACKET            = "[";
const char* R_SBRACKET            = "]";
const char* HEADER                = "#VRML V2.0 utf8\n";
const char* GROUP_NODE            = "Group";
const char* CHILDREN_PARAMETER    = "children";
const char* SHAPE_NODE            = "Shape";
const char* APPEARANCE_PARAMETER  = "appearance";
const char* APPEARANCE_NODE       = "Appearance";
const char* MATERIAL_PARAMETER    = "material";
const char* MATERIAL_NODE         = "Material";
const char* GEOMETRY_PARAMETER    = "geometry";
const char* INDEXED_FACE_SET_NODE = "IndexedFaceSet";
const char* COORD_PARAMETER       = "coord";
const char* COORDINATE_NODE       = "Coordinate";
const char* POINT_PARAMETER       = "point";
const char* COORD_INDEX_PARAMETER = "coordIndex";
const char* SPACE                 = " ";


extern "C"
void** query(void){
  
  void** parameters = new void*[5];

  //Plugin's type
  PluginType* type = new PluginType(LOAD_AND_SAVE);

  //Plugin's name
  std::string *name = new string("ioVRML");

  //Total number of entries in the different components 
  unsigned short *nbEntries = new unsigned short(2);

  //Load action 
  MenuAddOn *menuLoadAdd = new MenuAddOn();
  menuLoadAdd->typeAppel = LOAD_CALL;
  menuLoadAdd->emplacement = new string(PluginManager::MENUBAR_CMP);
  menuLoadAdd->emplacement->append("/&File/Load Model");
  menuLoadAdd->image = new string("fileopen.png");
  menuLoadAdd->texte = new string("CTRL+L");
  

  //Save Action 
  MenuAddOn *menuSaveAdd = new MenuAddOn();
  menuSaveAdd->typeAppel = SAVE_CALL;
  menuSaveAdd->emplacement = new string(PluginManager::MENUBAR_CMP);
  menuSaveAdd->emplacement->append("/&File/Save Model");
  menuSaveAdd->image = new string("filesaveas.png");
  menuSaveAdd->texte = new string("CTRL+S");

  qDebug("INSIDE PLUGIN : Query IOVRML type  = %d", *type);
  
  
  parameters[0] = type;
  parameters[1] = name;
  parameters[2] = nbEntries;
  parameters[3] = menuLoadAdd;
  parameters[4] = menuSaveAdd;

  return parameters;
}

// Sequence for points coordinates 
static void sequence1Construction(vector<string> & sequence) {
  sequence.push_back("point");
  sequence.push_back("[");
  sequence.push_back("]");
}


// Sequence for indexes (points order)
static void sequence2Construction(vector<string> & sequence) {
  sequence.push_back("coordIndex");
  sequence.push_back("[");
  sequence.push_back("]");
}

extern "C"
int load(MainWindow *mainW){
  
  // Using of the main window in order to enable the model access
  //MainWindow *mainW = (MainWindow*)mainWindow[0];

  // Variables declaration
  string word;

  int currentIndex;

  double currentValue, xValue, yValue, zValue;

  vector<int> indexValues;

  int numCoord = 1, nbPointsIndex = 0;

  vector<string> awaitedSequence1;
  vector<string> awaitedSequence2;
  vector<Point3D> *listPoint = new vector<Point3D>();
  vector<AbsFace*> *listFaces = new vector<AbsFace*>();

  int indexesTranslation = 0;


  // User chooses a file in order to load a VRML model
  QString fileName = QFileDialog::getOpenFileName(
    ".",
    "*.wrl",
    mainW,
    "VRML load dialog box",
    "choose a name for VRML load" );

  // If no name defined exit
  if(fileName.isEmpty()){
    return EXIT_FAILURE;
  }

  // Open the file
  ifstream VRMLFile (fileName,ios::in);

  Tria *t;
  Quad *q;
  Face *f;


  // Making of awaited sequences
  sequence1Construction(awaitedSequence1);
  sequence2Construction(awaitedSequence2);

  // If the file doesn't exist
  if(!VRMLFile){ 
    cerr << "File not found !" << endl; 
    return EXIT_FAILURE;
  } 

  

  // Reading of the file
  while (!VRMLFile.eof()){ 
    
    VRMLFile >> word;

    // When the first sequence is found
    if (awaitedSequence1.size() == 1) {
      
      if (word != awaitedSequence1.front()) {

        currentValue = atof(word.c_str());
	
        // Coordinate X management
        if (numCoord == 1) {
          xValue = currentValue;
          numCoord++;
        }
        else {
          // Coordinate Y management
          if (numCoord == 2) {
            yValue = currentValue;
            numCoord++;
          }
          // Coordinate Z management 
          else {
            zValue = currentValue;
            Point3D p;
            p[0] = xValue;
            p[1] = yValue;
            p[2] = zValue;
            cout << "x=" << p[0] << "y=" << p[1] << "z=" << p[2] << endl;
            listPoint->push_back(p);
            numCoord = 1;
	
          }
        }
      }
    }
    

    // When the second sequence is found
    if (awaitedSequence2.size() == 1) {
     
      
      if (word != awaitedSequence2.front()) {
      
        currentIndex = atoi(word.c_str());
	
        if (currentIndex == -1) {

          if (nbPointsIndex < 3) {
            return EXIT_FAILURE;
          }

          // Moving of indexes
          for (int i=0; i<=nbPointsIndex;i++) {
            indexValues[i] += indexesTranslation;
          }

          if (nbPointsIndex == 3) {
            t = new Tria(listPoint, indexValues[0], indexValues[1], indexValues[2]);
            listFaces->push_back(t);
          }
          else {
            if (nbPointsIndex == 4) {
              q = new Quad(listPoint, indexValues[0], indexValues[1], indexValues[2], indexValues[3]);
              listFaces->push_back(q);
            }
            else {
              f = new Face(&indexValues, listPoint, nbPointsIndex);
              listFaces->push_back(f);
            }
          }

          nbPointsIndex = 0;
          indexValues.clear();
	    
        }
        else {
          indexValues.push_back(currentIndex);
          nbPointsIndex++;
        }
	
	
      }
    }
    

    if (word == awaitedSequence1.front()) {
      awaitedSequence1.erase(awaitedSequence1.begin());
    } 
    
    if (word == awaitedSequence2.front()) {
      awaitedSequence2.erase(awaitedSequence2.begin());
    }
   
    // If there are more one point coordinate declaration
    if (awaitedSequence1.empty()) {
      sequence1Construction(awaitedSequence1);
    }

    // If there are more one index declaration
    if (awaitedSequence2.empty()) {


      //nbPointsIndex--;
      // Management of the last index
      if (nbPointsIndex < 3) {
	return EXIT_FAILURE;
      }
      
      // Moving of indexes
      for (int i=0; i<=nbPointsIndex;i++) {
	indexValues[i] += indexesTranslation;
      }
      
      if (nbPointsIndex == 3) {
	t = new Tria(listPoint, indexValues[0], indexValues[1], indexValues[2]);
	listFaces->push_back(t);
      }
      else {
	if (nbPointsIndex == 4) {
	  q = new Quad(listPoint, indexValues[0], indexValues[1], indexValues[2], indexValues[3]);
	  listFaces->push_back(q);
	}
	else {
	  f = new Face(&indexValues, listPoint, nbPointsIndex);
	  listFaces->push_back(f);
	}
      }


      // Indexes management
      indexesTranslation = indexesTranslation + listPoint->size();
    
      
      sequence2Construction(awaitedSequence2);
    }

  } 

  Faces* faces = new Faces(listPoint, listFaces);
  //cout << "La face :" << endl << *f;
  mainW->setModel(*faces);

  qDebug("Fin de la methode LOAD du plugin VRML");
  

  return EXIT_SUCCESS;
}


/***************************************************************
 *  Fonction save
 * 
 *  @param mainWin the principal window of the application
 *  @return 0 if success, -1 else.
 *
 *
 ***************************************************************/
extern "C"
int save(MainWindow *mainWin){
  //we load faces to write in the file
  Faces *faces_to_write;
  faces_to_write = new Faces(mainWin->model());

  //list of indexes for faces load
  vector<int> *index_list;

  //user chooses a name for wrl file
  QString fileName = QFileDialog::getSaveFileName(
    ".",
    "*.wrl",
    mainWin,
    "VRML save dialog box",
    "choose a name for VRML save" );

  //if no name defined exit
  if(fileName.isEmpty()){
    return EXIT_FAILURE;
  }

  //opening file for writing
  ofstream file(fileName.latin1());

  int cpt, nbFaces, nbPoints;
  std::vector<gml::Point3D> points;
  std::vector<AbsFace*> faces;
  AbsFace *workFace;

  //file control
  if(!file.is_open()){
    QMessageBox::information( mainWin, "Generalized cylinder",
                              "Unable to open file for save.\n");
    return EXIT_FAILURE;
  }

  //points and faces load
  points = faces_to_write->points();
  faces = faces_to_write->faces();
  nbPoints = points.size();
  nbFaces = faces.size();

  //header writing
  file<<HEADER<<endl;

  //architecture writing
  file<<endl<<GROUP_NODE<<SPACE<<L_BRACE<<endl
      <<CHILDREN_PARAMETER<<SPACE<<L_SBRACKET<<endl
      <<SHAPE_NODE<<SPACE<<L_BRACE<<endl
      <<APPEARANCE_PARAMETER<<SPACE<<APPEARANCE_NODE<<SPACE<<L_BRACE<<endl
      <<MATERIAL_PARAMETER<<SPACE<<MATERIAL_NODE<<L_BRACE<<endl
      <<R_BRACE<<endl
      <<R_BRACE<<endl
      <<GEOMETRY_PARAMETER<<SPACE<<INDEXED_FACE_SET_NODE<<SPACE<<L_BRACE<<endl
      <<COORD_PARAMETER<<SPACE<<COORDINATE_NODE<<SPACE<<L_BRACE<<endl
      <<POINT_PARAMETER<<SPACE<<L_SBRACKET<<SPACE;

  //we write the points
  for(cpt = 0; cpt<nbPoints; cpt++){
    if(cpt != 0){
      file<<", ";
    }
    file<<points[cpt][0]<<SPACE<<points[cpt][1]<<SPACE<<points[cpt][2];
  }
  file<<R_SBRACKET<<endl<<R_BRACE<<endl;


  //we write the faces (indexes) 
  file<<endl<<COORD_INDEX_PARAMETER<<SPACE<<L_SBRACKET<<SPACE;
  for(cpt = 0; cpt<nbFaces; cpt++){
    if(cpt!=0){
      file<<SPACE;
    }
    workFace = faces[cpt];
    index_list = workFace->getIndexes();
    for(unsigned int i = 0; i<index_list->size(); i++){
      file<<(*index_list)[i]<<SPACE;
    }
    file<<"-1";
  }

  //braces closing
  file<<SPACE<<R_SBRACKET<<endl
      <<R_BRACE<<endl<<R_BRACE<<endl
      <<R_SBRACKET<<endl
      <<R_BRACE<<endl;

  //file closing
  file.close();

  return EXIT_SUCCESS;
}
