//*****************************************************************************
// Name: Camara Lerner
// SN: 001150339
// Class: CPSC 3770
// The test file to run the application for assignment # 1 part 3
//*****************************************************************************
#include <QApplication>

#include "main_window.h"

int main(int argc, char **argv) {

  QApplication app(argc, argv);
  MainWindow *window = new MainWindow();
  window->show();
  return app.exec();

}
