#ifndef CLASS_HELPWINDOW_H
#define CLASS_HELPWINDOW_H

#include <iostream>

#include <qframe.h>
#include <qtextbrowser.h>
#include <qfile.h>
#include <qvbox.h>
#include <qmime.h>
#include <qstylesheet.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qiconset.h>
#include <qpixmap.h>
#include <qpopupmenu.h>
#include <qmenubar.h>
#include <qmainwindow.h>
#include <qstringlist.h>

/******************************************************
 *  derived from QMainWindow. help for user
 *
 ******************************************************/
class HelpWindow : public QMainWindow
{
  Q_OBJECT
  
  private:
  QTextBrowser* _browser; /**the text browser*/
  QStringList history; /**the history*/
  
  int backwardId; /**backwardId*/ 
  int forwardId; /**forwardId*/
  
  public:

  /**************************************************************
   *
   *  HelpWindow constructor
   *  @param home the home url
   *
   *************************************************************/
  HelpWindow(const QString& home);

  public slots:
 
 
  /**************************************************************
   *
   *  redirection to a url
   *  @param url the new url
   *
   *************************************************************/
  void redirection( const QString& url );
  
  private slots:

  /**************************************************************
   *
   *  enable backward
   *
   *************************************************************/
  void setBackwardAvailable( bool );

  /**************************************************************
   *
   *  enable or disable forward
   *
   *************************************************************/
  void setForwardAvailable( bool );

  /**************************************************************
   *
   *  change the source
   *  @param url the new url
   *
   *************************************************************/
  void sourceChanged( const QString& url ); 
};

#endif
