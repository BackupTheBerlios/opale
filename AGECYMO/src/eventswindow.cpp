#include <qmultilineedit.h>
#include <time.h>
#include "eventswindow.hpp"

/**************************************************************
 *
 *  EventsWindow constructor
 *
 *************************************************************/
EventsWindow::EventsWindow() :
    QMultiLineEdit(NULL, "log")
{

  this-> setReadOnly ( true );
  QColor color(200, 20, 20);
  this->setColor(color);
  this->insert("Welcome to AGECYMO\n");
  this->resize(275, 450);
  this->move(1, 433);
}

/**************************************************************
 *
 *  EventsWindow destructor
 *
 *************************************************************/
EventsWindow::~EventsWindow()
{
}

/**************************************************************
 *
 *  write a log.
 *  @param text the log message
 *
 *************************************************************/
void
EventsWindow::writeComments(QString & text)
{

  time_t now;

  struct tm *m;
  
  time(&now);

  m= localtime(&now);
  char timeString[30]="";
  char hourString[30]="";
  char minString[30]="";
  char secString[30]="";
        
  
  if (m->tm_hour < 10) {
    sprintf(hourString, "0%i", m->tm_hour);
  }
  else {
    sprintf(hourString, "%i", m->tm_hour);
  }

  if (m->tm_min < 10) {
    sprintf(minString, "0%i", m->tm_min);
  }
  else {
    sprintf(minString, "%i", m->tm_min);
  }
  
  if (m->tm_sec< 10) {
    sprintf(secString, "0%i", m->tm_sec);
  }
  else {
    sprintf(secString, "%i", m->tm_sec);
  }

  strcat(timeString, hourString);
  strcat(timeString, ":");
  strcat(timeString, minString);
  strcat(timeString, ":");
  strcat(timeString, secString);
  strcat(timeString, " --> ");

  this->setItalic(true);
  QColor color(120, 80, 100);
  this->setColor(color);
  this->insert(timeString);
  this->setItalic(false);
  this->insert(text + "\n");

}

