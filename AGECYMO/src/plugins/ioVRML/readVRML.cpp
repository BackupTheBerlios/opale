// Libraries.
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "point.hpp"
#include "tria.hpp"
#include "quad.hpp"
#include "absface.hpp"

using namespace std;
using namespace gml;

//Tokens
const char* GEOMETRY         = "geometry";
const char* INDEXED_FACE_SET = "IndexedFaceSet";

const char* COORD            = "coord";
const char* COORD_INDEX      = "coordIndex";
const char* COORDINATE       = "Coordinate";

const char* POINT            = "point";

const char* L_BRACE          = "{";
const char* R_BRACE          = "}";

const char* L_SBRACKET       = "[";
const char* R_SBRACKET       = "]";



static void sequence1Construction(vector<string> & sequence) {
//   sequence.push_back("geometry");
//   sequence.push_back("IndexedFaceSet");
//   sequence.push_back("{");
//   sequence.push_back("coord");
//   sequence.push_back("Coordinate");
//   sequence.push_back("{");
//   sequence.push_back("point");
//   sequence.push_back("[");
//   sequence.push_back("]");
  
  sequence.push_back(GEOMETRY);

  sequence.push_back(INDEXED_FACE_SET);
  sequence.push_back(L_BRACE);

  sequence.push_back(COORD);
  sequence.push_back(COORDINATE);

  sequence.push_back(L_BRACE);
  sequence.push_back(POINT);

  sequence.push_back(L_SBRACKET);
  sequence.push_back(R_SBRACKET);
}

static void sequence2Construction(vector<string> & sequence) {
//   sequence.push_back("coordIndex");
//   sequence.push_back("[");
//   sequence.push_back("]");
  
  sequence.push_back(COORD_INDEX);
  sequence.push_back(L_SBRACKET);
  sequence.push_back(R_SBRACKET);
  
}

// Allows to read a VRML file.
static int readVRML(void) {

  string word;

  double currentValue, xValue, yValue, zValue;

  vector<double> indexValues;

  int numCoord = 1, nbPointsIndex = 0;

  vector<string> awaitedSequence1;
  vector<string> awaitedSequence2;
  vector<Point3D> listPoint;
  vector<AbsFace> listFaces;

  ifstream VRMLFile ("vase1.wrl",ios::in);

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

    if (awaitedSequence1.size() == 1) {
      
      if (word != awaitedSequence1.front()) {

        currentValue = atof(word.c_str());
	
	
        if (numCoord == 1) {
          xValue = currentValue;
          numCoord++;
        }
        else {
          if (numCoord == 2) {
            yValue = currentValue;
            numCoord++;
          }
          else {
            zValue = currentValue;
            Point3D p;
            p[0] = xValue;
            p[1] = yValue;
            p[2] = zValue;
            listPoint.push_back(p);
            numCoord = 1;
	
          }
        }
      }
    }

    if (awaitedSequence2.size() == 1) {
     
      
      if (word != awaitedSequence2.front()) {
      
        currentValue = atof(word.c_str());

        if (currentValue == -1) {

          if (nbPointsIndex < 3) {
            return EXIT_FAILURE;
          }

          vector<Point3D> *v;
          for (int i=0;i<=nbPointsIndex;i++) {
//	    v.push_back(& listPoint.at(indexValues.at(i)));
          }
          if (nbPointsIndex == 3) {
            //    Tria t(v, indexValues.at(0), indexValues.at(1), indexValues.at(2));
            //listFaces.push_back(t);
          }
          else {
            if (nbPointsIndex == 4) {
              //   Quad q(v,
//                indexValues.at(0),
//                indexValues.at(1),
//                indexValues.at(2),
//                indexValues.at(3));

//         listFaces.push_back(q);
            }
            else {
              //Face f(v, nbPointsIndex, 
            }
          }
        }
        else {
          indexValues.push_back(currentValue);
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

    if (awaitedSequence1.empty()) {
      sequence1Construction(awaitedSequence1);
    }

    if (awaitedSequence2.empty()) {
      sequence2Construction(awaitedSequence2);
    }

  } 

  return EXIT_SUCCESS;
}

// Returns information about ReadVRML.
extern "C" char *query(void) {
  return "ReadVRML";
}

// Executes ReadVRML.
extern "C" int run(void **param) {
  return readVRML();
}
