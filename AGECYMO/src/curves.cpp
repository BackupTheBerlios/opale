//
//  curves.cpp
//  
//  implementation of the class Curves
//
#include "curves.hpp"
#include "canvas2d.hpp"


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
  
  for(unsigned i = 0; i<getNbCurves(); i++){
    delete(_listOfCurves[i]);
  }
  _listOfCurves.clear();
  _listOfControlPoints.clear();

  _currentToolType = NO_TOOL_MODE;
  _isClosed = false;
  _isSelected.clear();

  //popupMenu management
  _parent->getPopupMenu()->setItemEnabled(0,true);
  _parent->getPopupMenu()->setItemEnabled(1,true);
  _parent->getPopupMenu()->setItemEnabled(2,true);
  _parent->getPopupMenu()->setItemEnabled(3,true);

  if(_parent->getCanvasType() == SECTION_CANVAS){
    _parent->getPopupMenu()->setItemEnabled(2,false);
    _parent->getPopupMenu()->setItemEnabled(3,false);
  }
  
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
    if((_listOfCurves[getNbCurves()-1]->addPoint(_listOfControlPoints[0]))
       == ADDED){
      _isClosed = true;
    }
  }
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
  double increment; 
  increment = Control_point_size / 2.0;
  
  //render for all the curves
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
 *  discretize the entiere figure (all the curves)
 *  @param nbSegments the number of segments between two control
 *   point of the network
 *  @return the list of points
 *
 *************************************************************/
std::vector<gml::Point3D> Curves::discretize(int nbSegments)
{
  std::vector<gml::Point3D> pointsList;
  std::vector<gml::Point3D> tmp;

  for(unsigned i = 0; i<getNbCurves(); i++){
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
	_listOfCurves.push_back(new Polyline());
	_currentToolType = POLY_MODE;

	//management of the popupMenu
	_parent->getPopupMenu()->setItemEnabled(0,false);
	_parent->getPopupMenu()->setItemEnabled(1,true);
	_parent->getPopupMenu()->setItemEnabled(2,false);
	_parent->getPopupMenu()->setItemEnabled(3,false);
      }

      //rectangle creation
      if(toolType == REC_MODE){
	_listOfCurves.push_back(new Polyline());
	_currentToolType = REC_MODE;

	//management of the popupMenu
	_parent->getPopupMenu()->setItemEnabled(0,false);
	_parent->getPopupMenu()->setItemEnabled(1,false);
	_parent->getPopupMenu()->setItemEnabled(2,false);
	_parent->getPopupMenu()->setItemEnabled(3,false);
      }
      if(toolType == CIRCLE_MODE){
	_listOfCurves.push_back(new Polyline());
	_currentToolType = CIRCLE_MODE;

	//management of the popupMenu
	_parent->getPopupMenu()->setItemEnabled(0,false);
	_parent->getPopupMenu()->setItemEnabled(1,false);
	_parent->getPopupMenu()->setItemEnabled(2,false);
	_parent->getPopupMenu()->setItemEnabled(3,false);
      }
      if(toolType == NURBS_MODE){
	_listOfCurves.push_back(new Polyline());
	_currentToolType = NURBS_MODE;

	//management of the popupMenu
	_parent->getPopupMenu()->setItemEnabled(0,true);
	_parent->getPopupMenu()->setItemEnabled(1,false);
	_parent->getPopupMenu()->setItemEnabled(2,false);
	_parent->getPopupMenu()->setItemEnabled(3,false);
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
    //passer l'evenenement a la courbe concern�e !!!!!
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

