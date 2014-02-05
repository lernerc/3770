//*****************************************************************************
// Name: Camara Lerner
// SN: 001150339
// Class: CPSC 3770
// The MainWindow header file for assignment # 1 part 1
//*****************************************************************************

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLabel;
class PasswordEdit;
class QPushButton;

class MainWindowTest : public QMainWindow {

  Q_OBJECT
  
public:

  MainWindowTest(QWidget *parent=0);
  
private slots:

  void showPassword();
  
private:

  QLabel *label;
  PasswordEdit *password;
  QPushButton *button;

};

#endif
