#ifndef CLASS_CONTROLPANEL_H
#define CLASS_CONTROLPANEL_H

#include <qlayout.h>
#include <qvgroupbox.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qvalidator.h>
#include <qcheckbox.h>
#include <qmessagebox.h>

class ControlPanel : public QWidget
{
  Q_OBJECT
  
  private:

  //intern widgets
  QBoxLayout* _layout;
  
  QGroupBox*  _discretizeBox;
  QGroupBox*  _cylinderBox;


  QLineEdit*   _wayTF; //TF = textfield
  QLineEdit*   _sectionTF; 

  QLineEdit*   _scaleSectionTF;
  QLineEdit*   _scaleWayTF; 

  QCheckBox*  _torsionBox;
  
  
  QIntValidator*    _wayValidator;
  QIntValidator*    _sectionValidator;

  QDoubleValidator* _scaleValidator;

  
  //values the user may change
  int _nWay;
  int _nSection;

  double _scaleFactorSection;
  double _scaleFactorWay;
  
  bool   _torsionEnabled;
  
  public:
  ControlPanel(QWidget* parent);
  ~ControlPanel();

  int wayDiscretizeValue();
  int sectionDiscretizeValue();

  double scaleFactorSection();
  double scaleFactorWay();
  
  bool isTorsionEnabled() const;

  void validateAll();

  private:
  void checkWay();
  
  private slots:
  
//  void validateWay(const QString& text);
  void validateWay();

  void validateSection();

  void validateScale();
  
};


#endif

