//*****************************************************************************
// Name: Camara Lerner
// SN: 001150339
// Class: CPSC 3770
// The implementation file for MainWindow for assignment # 1 part 1
//*****************************************************************************

#include "mainwindow.h"
#include "passwordedit.h"

#include <QtGui>

MainWindowTest::MainWindowTest(QWidget *parent) : QMainWindow(parent) {

  label = new QLabel("Type password: ");
  password = new PasswordEdit();
  button = new QPushButton("Show");
  
  QHBoxLayout *layout = new QHBoxLayout();
  layout->addWidget(label);
  layout->addWidget(password);
  layout->addWidget(button);
  
  setCentralWidget(new QWidget());
  centralWidget()->setLayout(layout);
  
  connect(button, SIGNAL(clicked()), this, SLOT(showPassword()));
 }

void MainWindowTest::showPassword() {
  QMessageBox::information(this, "Password", QString("Your password is: %1").arg(password->text()));
}
