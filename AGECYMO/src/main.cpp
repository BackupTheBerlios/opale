#include <iostream>
#include <qapplication.h>

#include "mainwindow.hpp"

#include "testVector.hpp"

const double W_RATIO = 0.8; //how many of the screen's width we use for our application
const double H_RATIO = 0.07; //how many of the screen's height we use for our application

/**
 * Compute the application size according to the
 * two constants defined upper
 */
void
initApplicationSizeAndPosition(int w_application, int &w_frame)
{
  QDesktopWidget *d = QApplication::desktop();
  int w = d->width();     // returns desktop width
  int h = d->height();    // returns desktop height


  w_frame = min ( (w - w_application), (h - 40));

  w_frame = w_frame / 2;
  
  
  
  qDebug("Screen w = %d\n", w);
  qDebug("Screen h = %d\n", h);
  qDebug("Width frame = %d\n", w_frame);

}

int
main(int argc, char **argv)
{
  // set high color mode & default font
  QApplication::setColorSpec(QApplication::ManyColor);
  QApplication::setFont(QFont("Arial", 10, QFont::Normal));

  // creation of an application (handle main loop event)
  QApplication application(argc, argv);

  int w_app;
  initApplicationSizeAndPosition(55, w_app); 
  
  // creation of the central window...
  MainWindow   mainWindow(w_app, w_app, 85, 130, 0, 0);

  // connected the main window to the application
  application.setMainWidget(&mainWindow);
  //mainWindow.show();

  //TODO : remove this 
  //Test the vector class 
  testVector();
  
  // execute the application (main loop)
  return application.exec();
}


