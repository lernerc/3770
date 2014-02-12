#include <QApplication>

#include "pic_viewer.h"

int main(int argc, char **argv) {

  QApplication app(argc, argv);

  PicViewer *p = new PicViewer();

  p->loadPic("small.jpg");

  p->show();

  return app.exec();

}
