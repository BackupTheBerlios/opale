#include "curves.hpp"
#include "canvas2d.hpp"
#include "circle.hpp"
#include "quadri.hpp"
#include "polygone.hpp"
#include "nurbscurve.hpp"


/**************************************************************
 *
 *  Curves constructor
 *  @param parent the parent canvas
 *
 *************************************************************/
Curves::Curves(Canvas2D *parent)
{
  _currentToolType = NO_TOOL_MODE;
  _listOfCurves.clear();

  _parent = parent;

  //initialise colors
  _redComponent = RED_DEFAULT; 
  _greenComponent = GREEN_DEFAULT; 
  _blueComponent = BLUE_DEFAULT;
  _redComponentSelect = RED_DEFAULT_SELECT; 
  _greenComponentSelect = GREEN_DEFAULT_SELECT; 
  _blueComponentSelect = BLUE_DEFAULT_SELECT;

  _isClosed = false;
  noSelection();
}


/**************************************************************
 *
 *  Curves destructor
 *
 *************************************************************/
Curves::~Curves()
{
  //delete all curves
  for(unsigned i=0 ; i<_listOfCurves.size(); i++){
    delete (_listOfCurves[i]);
  }
  _listOfCurves.clear();
  
  //delete all control points
  for(unsigned i=0 ; i<_listOfControlPoints.size(); i++){
    delete (_listOfControlPoints[i]);
  }
  _listOfControlPoints.clear();

  _isSelected.clear();
}


/**************************************************************
 *
 *  returns the number of managed curves
 *  @return the number of curves
 *
 *************************************************************/
int Curves::getNbCurves()
{
  return _listOfCurves.size();
}
 

/**************************************************************
 *
 *  delete all the curves
 *
 *************************************************************/
void Curves::deleteAllCurves()
{
  
  for(int i = 0; i<getNbCurves(); i++){
    delete(_listOfCurves[i]);
  }
  _listOfCurves.clear();
  _listOfControlPoints.clear();

  _currentToolType = NO_TOOL_MODE;
  _isClosed = false;
  _isSelected.clear();

  _parent->getPopupMenu()
    ->setItemEnabled(_parent->getPopupMenu()->idAt(0),true);
  _parent->getPopupMenu()
    ->setItemEnabled(_parent->getPopupMenu()->idAt(1),true);
  _parent->getPopupMenu()
    ->setItemEnabled(_parent->getPopupMenu()->idAt(2),true);
  _parent->getPopupMenu()
    ->setItemEnabled(_parent->getPopupMenu()->idAt(3),true);
  _parent->getPopupMenu()
    ->setItemEnabled(_parent->getPopupMenu()->idAt(4),true);
  
  //popupMenu management

  if(_parent->getCanvasType() == PROFIL_CANVAS){
    _parent->getPopupMenu()
      ->setItemEnabled(_parent->getPopupMenu()->idAt(2),false);
    _parent->getPopupMenu()
      ->setItemEnabled(_parent->getPopupMenu()->idAt(3),false);
    _parent->getPopupMenu()
      ->setItemEnabled(_parent->getPopupMenu()->idAt(4),false);
  }
  
}

/**************************************************************
 *
 *  add a curve to the curves list
 *  @param newCurve the newCurve
 *
 *************************************************************/
void Curves::addCurve(AbsCurve *newCurve)
{
  _listOfCurves.push_back(newCurve);
}

/**************************************************************
 *
 *  get all the curves
 *  @return a vector of curves
 *
 *************************************************************/
std::vector<AbsCurve*> Curves::getAllCurves()
{
  return _listOfCurves;
}

/**************************************************************
 *
 *  change the current tool type
 *  @param toolType the new curent tool type
 *
 *************************************************************/
void Curves::setCurrentToolType(unsigned short toolType)
{
  _currentToolType = toolType;
}

/**************************************************************
 *
 *  get the current tool type
 *  @return the current toolType
 *
 *************************************************************/
unsigned short Curves::getCurrentToolType()
{
  return _currentToolType;
}

/**************************************************************
 *
 *  returns the number of control points
 *  @return the number of control points
 *
 *************************************************************/
int Curves::getNbControlPoints()
{
  return _listOfControlPoints.size();
}

/**************************************************************
 *
 *  add a point to control network
 *  @param newPoint the new control point
 *
 *************************************************************/
void Curves::addPoint(gml::Point3D *newPoint){
  _listOfControlPoints.push_back(newPoint);
}

/**************************************************************
 *
 *  move a point of the control network
 *  @param index the index of the point in the network
 *  @param newPosition the new position of the point
 *
 *************************************************************/
void Curves::movePoint(int index, gml::Point3D newPosition){
  if(((unsigned)index<_listOfControlPoints.size()) || (index >= 0)){ 
    (*_listOfControlPoints[index])[0] = newPosition[0];
    (*_listOfControlPoints[index])[1] = newPosition[1];
  }
}

/**************************************************************
 *
 *  get a point at an index
 *  @param index the index of the point in the network
 *  @return the point at the index or NULL if not exists
 *
 *************************************************************/
gml::Point3D *Curves::getPointAtIndex(unsigned short index)
{
  if(index <_listOfControlPoints.size()){
    return _listOfControlPoints[index];
  }
  return NULL;
}

/**************************************************************
 *
 *  get all the points of the network (save utility)
 *  @return the vector of all control points
 *
 *************************************************************/
std::vector<gml::Point3D*> Curves::getAllPoints()
{
  return _listOfControlPoints;
}

/**************************************************************
 *
 *  define if the control network is closed
 *  @return true if closed, false else
 *
 *************************************************************/
bool Curves::isClosed() const{
  return _isClosed;
}


/**************************************************************
 *
 *  close the control network. Rattach the last point of the
 *  last curve to the first point of the first curve
 *
 *************************************************************/
void Curves::close(){
  if(getNbCurves() != 0){
    _listOfCurves[getNbCurves()-1]->addPoint(_listOfControlPoints[0])
      == ADDED;
  }
  _isClosed = true;
}


/**************************************************************
 *
 *  define the selected point when the user clicks on the canvas
 *  @param point the position of the click
 *  @return the index of the point, NO_EXIST if not exists
 *
 *************************************************************/
int Curves::isExistingPoint(gml::Point3D point) const{

  double increment; 
  increment = Control_point_size / 2.0;
  for(unsigned i = 0; i<_listOfControlPoints.size(); i++){
    if(((*_listOfControlPoints[i])[0] <= point[0] + increment) &&
       ((*_listOfControlPoints[i])[0] >= point[0] - increment) &&
       ((*_listOfControlPoints[i])[1] <= point[1] + increment) &&
       ((*_listOfControlPoints[i])[1] >= point[1] - increment)){
      return i;
    }
  }
  return NO_EXIST;
}

/**************************************************************
 *
 *  select a point
 *  @param index the index of the point to be selected
 *
 *************************************************************/
void Curves::select(unsigned short index){
  bool alreadySelected = false;
  for(unsigned i = 0; i<_isSelected.size(); i++){
    if(_isSelected[i] == index){
      alreadySelected = true;
    }
  }
  if((index<_listOfControlPoints.size()) && (!alreadySelected)){ 
    _isSelected.push_back(index);
  }
}

/**************************************************************
 *
 *  define if a point is selected
 *  @param index the index of the point
 *  @return true if selected, false else
 *
 *************************************************************/
bool Curves::isSelected(int index){
  for(unsigned i = 0; i<_isSelected.size(); i++){
    if(index == _isSelected[i]){
      return true;
    }
  }
  return false;
}

/**************************************************************
 *
 *  deselect all the points
 *
 *************************************************************/
void Curves::noSelection(){
  _isSelected.clear();
}

/**************************************************************
 *
 *  select all the points
 *
 *************************************************************/
void Curves::selectAll()
{
  noSelection();
  for(unsigned i = 0; i<_listOfControlPoints.size(); i++){
    select(i);
  }
}

/**************************************************************
 *
 *  draw the entiere figure on the canvas (all the curves)
 *
 *************************************************************/
void Curves::render()
{
  cout<<"rendu de la curves"<<endl;

  double increment; 
  increment = Control_point_size / 2.0;
  
  //render for all the curves

  cout<<"nb de courbes ="<<_listOfCurves.size()<<endl;

  for(unsigned i = 0; i<_listOfCurves.size(); i++){
    _listOfCurves[i]->render();
  }

  //render for control point network
  for(int i = 0 ; i < int(_listOfControlPoints.size()); i++){
    if(isSelected(i)){
       glColor3f(_redComponentSelect,
		 _greenComponentSelect, 
		 _blueComponentSelect);
    }
    else{
      glColor3f(_redComponent,
		 _greenComponent, 
		 _blueComponent);
    }
    glBegin(GL_POLYGON);
    glVertex2f((*_listOfControlPoints[i])[0]-increment, 
	       (*_listOfControlPoints[i])[1]-increment);
    glVertex2f((*_listOfControlPoints[i])[0]-increment, 
	       (*_listOfControlPoints[i])[1]+increment);
    glVertex2f((*_listOfControlPoints[i])[0]+increment, 
	       (*_listOfControlPoints[i])[1]+increment);
    glVertex2f((*_listOfControlPoints[i])[0]+increment, 
	       (*_listOfControlPoints[i])[1]-increment);
    glEnd();
  }
}


/**************************************************************
 *
 *  translate Qt coordinates into OpenGL coordinates
 *  @param event the event containing qt position
 *  @param point the new OpenGL coordinates
 *
 *************************************************************/
void Curves::calculateQtToOpenGL(QMouseEvent* event, gml::Point3D *point)
{
  //coordinate calcul for qt/openGl traduction
  (*point)[0] =
    -glOrthoParameter + 
    ((double)event->x() * ((glOrthoParameter*2)/(double)_parent->width()));
  (*point)[1] =
    glOrthoParameter - 
    ((double)event->y() * ((glOrthoParameter*2)/(double)_parent->height()));
}


/**************************************************************
 *
 *  discretize the entiere figure (all the curves).
 *  @param nbSegments the number of segments of the global
 *  network. we have to find a multiple of the number of curves.
 *  @return the list of points
 *
 *************************************************************/
std::vector<gml::Point3D> Curves::discretize(int nbSegments)
{
  std::vector<gml::Point3D> pointsList;
  std::vector<gml::Point3D> tmp;
  int nbCurves = getNbCurves();
  int result;

  //find a multiple

  result = nbSegments/nbCurves;
  result = nbCurves*result;
  while(result<nbSegments){
    nbSegments+=1;
    result = nbSegments/nbCurves;
    result = nbCurves*result;
  }
  nbSegments = nbSegments/nbCurves;

  for(int i = 0; i<getNbCurves(); i++){
    tmp = _listOfCurves[i]->discretize(nbSegments);

    //if it's the first curve, add the first point
    if(i==0){
      pointsList.push_back(tmp[0]);
    }

    for(unsigned z = 1; z < tmp.size() ; z++){
      pointsList.push_back(tmp[z]);
    }
  }
  return pointsList;
}

/**************************************************************
 *
 *  set the control points colors
 *  @param red the red component
 *  @param green the green component
 *  @param blue the blue component
 *
 *************************************************************/
void Curves::setColor(double red, double green, double blue){
  _redComponent = red;
  _greenComponent = green;
  _blueComponent = blue;
}

/**************************************************************
 *
 *  set the selected control points colors
 *  @param red the red component
 *  @param green the green component
 *  @param blue the blue component
 *
 *************************************************************/
void Curves::setSelectionColor(double red, double green, double blue){
  _redComponentSelect = red;
  _greenComponentSelect = green;
  _blueComponentSelect = blue;
}

/**************************************************************
 *
 *  get the network control points color
 *  @param red the red component
 *  @param green the green component
 *  @param blue the blue component
 *
 *************************************************************/
gml::Point3D Curves::getColor()
{
  gml::Point3D colors;
  colors[0] = (_redComponent);
  colors[1] = (_greenComponent);
  colors[2] = (_blueComponent);
  return colors;
}

/**************************************************************
 *
 *  get the network control points color when selected
 *  @return a vector point with the RGB colors
 *
 *************************************************************/
gml::Point3D Curves::getSelectionColor()
{
  gml::Point3D colors;
  colors[0] = (_redComponentSelect);
  colors[1] = (_greenComponentSelect);
  colors[2] = (_blueComponentSelect);
  return colors;
}

/**************************************************************
 *
 *  manage the mousePressEvent
 *  @param event the event
 *  @param toolType the canvas toolType in use
 *  @param canvasType the type of the canvas
 *
 *************************************************************/
void Curves::managePressEvent(QMouseEvent* event,
			      unsigned short toolType,
			      unsigned short canvasType)
{
  gml::Point3D *position = new gml::Point3D();
  calculateQtToOpenGL(event,position);
  int index;

  _startMovePoint[0] = (*position)[0];
  _startMovePoint[1] = (*position)[1];

  AbsCurve *newCurve;

  //Selection MODE
  if(event->state() != Qt::ControlButton){
    //add to selection group with shift
    if(event->state() == Qt::ShiftButton){
      if((index=isExistingPoint(*position)) != NO_EXIST){
	if(!isSelected(index)){
	    select(index);
	}
      }
    }
    
    //deselect and add without shift
    else{
      if((index=isExistingPoint(*position)) != NO_EXIST){
	if(!isSelected(index)){
	  noSelection();
	    select(index);
	}	
      }
	else{
	  noSelection();
	}
    }
    delete(position);
  }


  //creation MODE
  else{

    //changement de courbe
    if(toolType != _currentToolType){

      //polyline creation
      if(toolType == POLY_MODE){
        newCurve = new Polyline();
        _listOfCurves.push_back(newCurve);
        _currentToolType = POLY_MODE;

        _parent->getMW().getEventsWindow().writeComments("New point added!!");

        //management of the popupMenu
	_parent->getPopupMenu()
	  ->setItemEnabled(_parent->getPopupMenu()->idAt(0),false);
	_parent->getPopupMenu()
	  ->setItemEnabled(_parent->getPopupMenu()->idAt(1),true);
	_parent->getPopupMenu()
	  ->setItemEnabled(_parent->getPopupMenu()->idAt(2),false);
	_parent->getPopupMenu()
	  ->setItemEnabled(_parent->getPopupMenu()->idAt(3),false);
	_parent->getPopupMenu()
	  ->setItemEnabled(_parent->getPopupMenu()->idAt(4),false);

      }

      //polygone creation
      if(toolType == POLYG_MODE){
        newCurve = new Polygone();
        close();
        _listOfCurves.push_back(newCurve);
        _currentToolType = POLYG_MODE;
	
        //management of the popupMenu
	_parent->getPopupMenu()
	  ->setItemEnabled(_parent->getPopupMenu()->idAt(0),false);
	_parent->getPopupMenu()
	  ->setItemEnabled(_parent->getPopupMenu()->idAt(1),false);
	_parent->getPopupMenu()
	  ->setItemEnabled(_parent->getPopupMenu()->idAt(2),false);
	_parent->getPopupMenu()
	  ->setItemEnabled(_parent->getPopupMenu()->idAt(3),false);
	_parent->getPopupMenu()
	  ->setItemEnabled(_parent->getPopupMenu()->idAt(4),false);

      }

      //rectangle creation
      if(toolType == REC_MODE){
        newCurve = new Quadri();
        close();
        _listOfCurves.push_back(newCurve);
        _currentToolType = REC_MODE;

        //management of the popupMenu
	_parent->getPopupMenu()
	  ->setItemEnabled(_parent->getPopupMenu()->idAt(0),false);
	_parent->getPopupMenu()
	  ->setItemEnabled(_parent->getPopupMenu()->idAt(1),false);
	_parent->getPopupMenu()
	  ->setItemEnabled(_parent->getPopupMenu()->idAt(2),false);
	_parent->getPopupMenu()
	  ->setItemEnabled(_parent->getPopupMenu()->idAt(3),false);
	_parent->getPopupMenu()
	  ->setItemEnabled(_parent->getPopupMenu()->idAt(4),false);

      }
      if(toolType == CIRCLE_MODE){
        newCurve = new Circle();
        close();
        _listOfCurves.push_back(newCurve);
        _currentToolType = CIRCLE_MODE;
	
        //management of the popupMenu
	_parent->getPopupMenu()
	  ->setItemEnabled(_parent->getPopupMenu()->idAt(0),false);
	_parent->getPopupMenu()
	  ->setItemEnabled(_parent->getPopupMenu()->idAt(1),false);
	_parent->getPopupMenu()
	  ->setItemEnabled(_parent->getPopupMenu()->idAt(2),false);
	_parent->getPopupMenu()
	  ->setItemEnabled(_parent->getPopupMenu()->idAt(3),false);
	_parent->getPopupMenu()
	  ->setItemEnabled(_parent->getPopupMenu()->idAt(4),false);

      }
      if(toolType == NURBS_MODE){
        newCurve = new NurbsCurve();
        _listOfCurves.push_back(newCurve);
        _currentToolType = NURBS_MODE;
	
        //management of the popupMenu
	_parent->getPopupMenu()
	  ->setItemEnabled(_parent->getPopupMenu()->idAt(0),true);
	_parent->getPopupMenu()
	  ->setItemEnabled(_parent->getPopupMenu()->idAt(1),false);
	_parent->getPopupMenu()
	  ->setItemEnabled(_parent->getPopupMenu()->idAt(2),false);
	_parent->getPopupMenu()
	  ->setItemEnabled(_parent->getPopupMenu()->idAt(3),false);
	_parent->getPopupMenu()
	  ->setItemEnabled(_parent->getPopupMenu()->idAt(4),false);
      }

      //we add the last point of the last curve to the new curve
      //control if it's the first curve
      if(getNbCurves()!=1){
        if((_listOfCurves[getNbCurves()-1]->addPoint(
              _listOfControlPoints[getNbControlPoints()-1]))==ADDED){
          addPoint(position);
        }
      }
    }

    if((_listOfCurves[getNbCurves()-1]->addPoint(position))==ADDED){
      addPoint(position);
      noSelection();
      select(isExistingPoint(*position));
    }
    else{
      delete(position);
    }
  }
}


/**************************************************************
 *
 *  manage the mouseMoveEvent
 *  @param event the event
 *  @param toolType the canvas toolType in use
 *  @param canvasType the type of the canvas
 *
 *************************************************************/
void Curves::manageMoveEvent(QMouseEvent* event,
                             unsigned short toolType,
                             unsigned short canvasType)
{
  gml::Point3D position;
  calculateQtToOpenGL(event,&position);

  //Selection MODE
  if(event->state() != Qt::ControlButton){
    gml::Point3D newPos;
    for(unsigned i = 0; i<_listOfControlPoints.size(); i++){
      if(isSelected((int)i)){
        newPos[0] = (*_listOfControlPoints[i])[0] 
          + (position[0] - _startMovePoint[0]);
        newPos[1] = (*_listOfControlPoints[i])[1]
          + (position[1] - _startMovePoint[1]);
        movePoint((int)i, newPos);
      }
    }
    _startMovePoint[0] = position[0];
    _startMovePoint[1] = position[1];
  }
}


/**************************************************************
 *
 *  manage the mouseReleaseEvent
 *  @param event the event
 *  @param toolType the canvas toolType in use
 *  @param canvasType the type of the canvas
 *
 *************************************************************/
void Curves::manageReleaseEvent(QMouseEvent* event,
                                unsigned short toolType,
                                unsigned short canvasType)
{
  gml::Point3D position;
  calculateQtToOpenGL(event,&position);

  //Selection MODE
  if(event->state() != Qt::ControlButton){

  }
  else{
    //passer l'evenenement a la courbe concernée !!!!!
  }
}

/**************************************************************
 *
 *  manage the doubleClickEvent
 *  @param event the event
 *  @param toolType the canvas toolType in use
 *  @param canvasType the type of the canvas
 *
 *************************************************************/
void Curves::manageDbClickEvent(QMouseEvent* event,
                                unsigned short toolType,
                                unsigned short canvasType)
{
  gml::Point3D position;
  calculateQtToOpenGL(event,&position);
  _startMovePoint[0] = position[0];
  _startMovePoint[1] = position[1];

  //Selection MODE
  if(event->state() != Qt::ControlButton){
    
  }
  //Creation MODE
  else{
    close();
  }

}


