//*****************************************************************************
// Name: Camara Lerner
// SN: 001150339
// Class: CPSC 3770
// The header for Phone for assignment # 2 part 2 (by Kevin)
//*****************************************************************************
#ifndef PHONE_H
#define PHONE_H

#include <QMainWindow>

class QLineEdit;
class QListWidget;
class Keyboard;

class Phone : public QMainWindow {

  Q_OBJECT

public:

   Phone(QWidget *p=0);

private slots:

  void catchString(const QString &str);
  void setTolerance( int i );

private:
 
  QLineEdit *edit;
  QListWidget *history;
  Keyboard *keyboard;

};

#endif
