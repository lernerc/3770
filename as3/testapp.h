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
