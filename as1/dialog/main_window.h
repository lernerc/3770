//*****************************************************************************
// Name: Camara Lerner
// SN: 001150339
// Class: CPSC 3770
// The MainWindow header file for assignment # 1 part 3
//*****************************************************************************
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QAction;
class QTextEdit;

class MainWindow : public QMainWindow {

   Q_OBJECT

  public:

   MainWindow(QWidget *parent = 0);
   bool writeFile(const QString &filename, const QString &text);
   bool readFile(const QString &filename, QString &text);
   
  private slots:
   //File
   void createNew();
   void open();
   bool save();
   void close();
   void changed();
   
   //search
   void find();

   // would you like to save
   bool possibleSave();

  private:

   void createActions();
   void createMenus();
   void createToolBar();

   
   // File
   QAction *newAction, *openAction, *saveAction, *closeAction;
   // Edit
   QAction *undoAction, *cutAction, *copyAction, *pasteAction, *selectAllAction;
   //search
   QAction *findAction;
   QTextEdit *textEdit;
   
   bool fileChanged;
};

#endif
