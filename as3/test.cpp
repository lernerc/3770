#include <QApplication>

#include "testapp.h"

int main(int argc, char **argv) {

  QApplication app(argc, argv);
  TestApp *t = new TestApp();
  t->show();

  return app.exec();

}
