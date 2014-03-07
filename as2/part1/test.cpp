//*****************************************************************************
// Name: Camara Lerner
// SN: 001150339
// Class: CPSC 3770
// The test file to run application for assignment # 2 part 1 (by Kev)
//*****************************************************************************
#include <QApplication>

#include "pic_viewer.h"

int main(int argc, char **argv) {

  QApplication app(argc, argv);

  PicViewer *p = new PicViewer();

  // p->loadPic("non-existance");
  p->loadPic("/home/lernerc9/3770/as2/part1/small.jpg");

  p->show();

  return app.exec();

}
