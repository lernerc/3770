//*****************************************************************************
// Name: Camara Lerner
// SN: 001150339
// Class: CPSC 3770
// The header for Keyboard for assignment # 2 part 2
//*****************************************************************************
#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QWidget>

#include "key.h"

const int key_max = 12;

class Keyboard : public QWidget {

  Q_OBJECT

public:

  Keyboard(QWidget *p=0);
     
public slots:

  void setDelay( int d );
  void setTolerance( qreal t );

signals:

  void emitString(const QString &str);

  private slots:

  void addToString(const QString &str);

  private:
  Key *key[key_max];

};

#endif
