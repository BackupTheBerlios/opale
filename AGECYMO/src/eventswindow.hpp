#ifndef CLASS_EVENTSWINDOW
#define CLASS_EVENTSWINDOW

#include <qmultilineedit.h>
#include <qstring.h>

/******************************************************
 *  derived from QMultiLineEdit. this classe provides 
 *  a user information window
 *
 ******************************************************/
class EventsWindow : public QMultiLineEdit
{
  private:
  
  public:
  
  /**************************************************************
   *
   *  EventsWindow constructor
   *
   *************************************************************/
  EventsWindow();
  
  /**************************************************************
   *
   *  EventsWindow destructor
   *
   *************************************************************/
  ~EventsWindow();
  
  /**************************************************************
   *
   *  write a log.
   *  @param text the log message
   *
   *************************************************************/
  void writeComments(QString text);
  
};

#endif


