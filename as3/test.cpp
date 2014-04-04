//*****************************************************************************
// Name: Camara Lerner
// SN: 001150339
// Class: CPSC 3770
// The main file for assignment # 3 part 1 by Kevin
//*****************************************************************************
#include <QApplication>

#include "testapp.h"

int main(int argc, char **argv) {

  QApplication app(argc, argv);
  TestApp *t = new TestApp();
  t->show();

  return app.exec();

}
