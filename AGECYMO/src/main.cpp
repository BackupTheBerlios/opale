#include <iostream>
#include <qapplication.h>

#include "mainwindow.hpp"

#include "testVector.hpp"

const double W_RATIO = 0.7; //how many of the screen's width we use for our application
const double H_RATIO = 0.15; //how many of the screen's height we use for our application

/**
 * Compute the application size according to the
 * two constants defined upper
 */
void
initApplicationSizeAndPosition(int  &w,
                               int &h,
                               int &w_app,
                               int &h_app,
                               int &x_app,
                               int &y_app)
{
  QDesktopWidget *d = QApplication::desktop();
  w = d->width();     // returns desktop width
  h = d->height();    // returns desktop height

  w_app = static_cast<int>(w * W_RATIO);
  h_app = static_cast<int>(h * H_RATIO);

  x_app = static_cast<int>( (w - w_app) / 2.0 );
  y_app = 0;
  
  qDebug("application width = %d\n", w_app);
  qDebug("application height = %d\n", h_app);
  qDebug("application x = %d\n", x_app);
  qDebug("application y = %d\n", y_app);
}

int
main(int argc, char **argv)
{
  // set high color mode & default font
  QApplication::setColorSpec(QApplication::ManyColor);
  QApplication::setFont(QFont("Arial", 10, QFont::Normal));

  // creation of an application (handle main loop event)
  QApplication application(argc, argv);

  int w, h, w_app, h_app, x_app, y_app;
  initApplicationSizeAndPosition(w, h, w_app, h_app, x_app, y_app); 

  // creation of the central window...
  MainWindow   mainWindow(w, h, w_app, h_app, x_app, y_app);
  // connected the main window to the application
  application.setMainWidget(&mainWindow);
  //mainWindow.show();

  //TODO : remove this 
  //Test the vector class 
  testVector();
  
  // execute the application (main loop)
  return application.exec();
}


