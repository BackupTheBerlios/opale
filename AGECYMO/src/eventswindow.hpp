#ifndef CLASS_EVENTSWINDOW
#define CLASS_EVENTSWINDOW

#include <qmultilineedit.h>
#include <qstring.h>

class EventsWindow : public QMultiLineEdit {
private:
  
public:
  
  EventsWindow();
  
  ~EventsWindow();
  
  void writeComments(QString text);
  
};

#endif


