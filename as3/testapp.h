//*****************************************************************************
// Name: Camara Lerner
// SN: 001150339
// Class: CPSC 3770
// The TestApp header file for assignment # 3 part 1 by Kevin
//*****************************************************************************
#ifndef TESTAPP_H
#define TESTAPP_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include "testdrag.h"

class TestApp : public QWidget {

  Q_OBJECT

 public:

  TestApp(QWidget *p = 0);
   
 public slots:

  void testComplete(int time, double distance, int drops);

 private slots:

  void reset();

 private:

  QLineEdit *leTime, *leDistance, *leDrops;
  QPushButton *pbReset;
  TestDrag *tf;

};


#endif
