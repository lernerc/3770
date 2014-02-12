//*****************************************************************************
// Name: Camara Lerner
// SN: 001150339
// Class: CPSC 3770
// The implementation file for Phone for assignment # 2 part 2 (by Kevin)
//*****************************************************************************
#include <QtGui>
#include "key.h"
#include "keyboard.h"
#include "phone.h"

   Phone::Phone(QWidget *p) : QMainWindow(p) {

      edit = new QLineEdit();
      keyboard = new Keyboard();
      history = new QListWidget();

      QSpinBox *delaySpin = new QSpinBox();
      delaySpin->setSingleStep(10);
      delaySpin->setRange(0, 2000);
    
      QSpinBox *tolSpin = new QSpinBox();

      edit->setReadOnly(true);

      QVBoxLayout *layout = new QVBoxLayout();
      layout->addWidget( new QLabel("Recent calls:") );
      layout->addWidget(history);

      layout->addWidget(edit);
      layout->addWidget(keyboard);

      QHBoxLayout *bottom = new QHBoxLayout();
      bottom->addWidget( new QLabel("Delay: ") );
      bottom->addWidget( delaySpin );
      bottom->addWidget( new QLabel("Tolerance: ") );
      bottom->addWidget( tolSpin );

      layout->addLayout(bottom);

      QWidget *w = new QWidget();
      w->setLayout(layout);

      connect( keyboard, SIGNAL( emitString(const QString &) ), this, SLOT( catchString(const QString &) ) );
      connect( delaySpin, SIGNAL( valueChanged(int) ), keyboard, SLOT( setDelay(int) ) );
      connect( tolSpin, SIGNAL( valueChanged(int) ), this, SLOT( setTolerance(int) ) );

      delaySpin->setValue(100);
      tolSpin->setValue(1);

      setCentralWidget(w);

   }

  void Phone::catchString(const QString &str) {

     if (str == "*") {
       edit->backspace();
     } else if (str == "#") {
       history->addItem( edit->text() );
       history->setCurrentRow( history->count() - 1 );
       edit->clear();
     } else {
       edit->insert(str);
     }

  }

  void Phone::setTolerance( int i ) {
     keyboard->setTolerance( (qreal) i );
  }
