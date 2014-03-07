//*****************************************************************************
// Name: Camara Lerner
// SN: 001150339
// Class: CPSC 3770
// The test file to run the application for assignment # 2 part 2 (by Kev)
//*****************************************************************************

#include <QApplication>

#include "phone.h"


int main(int argc, char **argv) {

  QApplication app(argc, argv);
  Phone *p = new Phone();
  p->show();
  return app.exec();

}
