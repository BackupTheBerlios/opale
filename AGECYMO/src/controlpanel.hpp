#ifndef CLASS_CONTROLPANEL_H
#define CLASS_CONTROLPANEL_H

#include <qlayout.h>
#include <qvgroupbox.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qvalidator.h>
#include <qcheckbox.h>


class ControlPanel : public QWidget
{
  private:

  //intern widgets
  QBoxLayout* _layout;
  
  QGroupBox*  _discretizeBox;
  QGroupBox*  _cylinderBox;


  QLineEdit*   _wayTF; //TF = textfield
  QLineEdit*   _sectionTF; 
  //QLineEdit*   _torsionTF; 
  QLineEdit*   _scaleTF; 

  QCheckBox*  _torsionBox;
  
  
  // QIntValidator _wayValidator;
//  QIntValidator _sectionValidator;
  
  //values the user may change
  int _nWay;
  int _nSection;

  double _scaleFactor;
  bool   _torsionEnabled;
  
  public:
  ControlPanel(QWidget* parent);
  ~ControlPanel();

  int wayDiscretizeValue() const;
  int sectionDiscretizeValue() const;

  double scaleFactor() const;
  bool isTorsionEnabled() const;
  

};


#endif

