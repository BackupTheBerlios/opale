#include "controlpanel.hpp"


const QString DISCRETIZE_BOX_NAME = QString("Discretize Parameters ");
const QString CYLINDER_BOX_NAME   = QString("Cylinder Parameters ");


ControlPanel::ControlPanel(QWidget* parent)
    : QWidget(parent, "Control Panel"),
      _nWay(10),
      _nSection(10),
      _scaleFactor(1.0),
      _torsionEnabled(false)
{
  setMaximumWidth(170);
  
  _layout = new QVBoxLayout(this);

  _discretizeBox = new QGroupBox( 2, Qt::Horizontal, DISCRETIZE_BOX_NAME, this );
  _cylinderBox   = new QGroupBox( 2, Qt::Horizontal, CYLINDER_BOX_NAME, this );

  QLabel* way = new QLabel( QString("Way"), _discretizeBox);
  _wayTF     = new QLineEdit( _discretizeBox );
  _wayTF->setFixedSize( 80, 20 );
  QIntValidator wayValidator(2, 1000000, _discretizeBox);
  _wayTF->setValidator( &wayValidator);
  
  
  QLabel* section = new QLabel( QString("Section"), _discretizeBox);
  _sectionTF = new QLineEdit( _discretizeBox );
  _sectionTF->setFixedSize(80, 20);
  QIntValidator sectionValidator(3, 1000000, this);
  _sectionTF->setValidator( &sectionValidator ) ;
  
//  QLabel* torsion = new QLabel( QString("Torsion"), _cylinderBox);
//  _torsionTF = new QLineEdit( _cylinderBox );
//  _torsionTF->setFixedSize(80, 20);

  QLabel* torsion = new QLabel( QString("Torsion"), _cylinderBox);
  _torsionBox = new QCheckBox( _cylinderBox);

  
  QLabel* scale = new QLabel( QString("Scale"), _cylinderBox);

  _scaleTF   = new QLineEdit( _cylinderBox );
  _scaleTF->setFixedSize(80, 20);

  QDoubleValidator scaleValidator(0.0000001, 1000000.0, 2, _cylinderBox);
  _scaleTF->setValidator(&scaleValidator);
  
  
  _layout->addWidget( _discretizeBox);
  _layout->addWidget( _cylinderBox);
  
}

ControlPanel::~ControlPanel()
{
}



//accessors
int
ControlPanel::wayDiscretizeValue() const
{
  return _nWay;
}

int
ControlPanel::sectionDiscretizeValue() const
{
  return _nSection;
}


double
ControlPanel::scaleFactor() const
{
  return _scaleFactor;
}


bool
ControlPanel::isTorsionEnabled() const
{
  return _torsionEnabled;
}
// end of accessors


