//*****************************************************************************
// Name: Camara Lerner
// SN: 001150339
// Class: CPSC 3770
// The MainWindow implimentation file for assignment # 1 part 3
//*****************************************************************************
#include "main_window.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QTextEdit>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>
#include <QInputDialog>
#include <QFileDialog>
#include <QTextDocument>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

   textEdit = new QTextEdit();

   setCentralWidget(textEdit);
   connect(textEdit, SIGNAL(textChanged()), this, SLOT(changed()));
   
   createActions();
   createMenus();
   createToolBar();

   statusBar()->show();
}

void MainWindow::createActions() {

   //File
   newAction = new QAction("&New", this);
   newAction->setShortcut(QKeySequence::New);
   newAction->setStatusTip("Create a new document");
   connect(newAction, SIGNAL(triggered()), this, SLOT(createNew()));

   openAction = new QAction("&Open", this);
   openAction->setShortcut(QKeySequence::Open);
   openAction->setStatusTip("Opens an existing document");
   connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

   saveAction = new QAction("&Save", this);
   saveAction->setShortcut(QKeySequence::Save);
   saveAction->setStatusTip("Save the open document");
   connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

   closeAction = new QAction("E&xit", this);
   closeAction->setStatusTip("Closes this window");
   connect(closeAction, SIGNAL(triggered()), this, SLOT(close()));

   //Edit
   undoAction = new QAction("&Undo", this);
   undoAction->setShortcut(QKeySequence::Undo);
   undoAction->setStatusTip("Undoes the last action");
   connect(undoAction, SIGNAL(triggered()), textEdit, SLOT(undo()));

   cutAction = new QAction("Cu&t", this);
   cutAction->setShortcut(QKeySequence::Cut);
   cutAction->setStatusTip("Cuts the current selected text");
   connect(cutAction, SIGNAL(triggered()), textEdit, SLOT(cut()));

   copyAction = new QAction("&Copy", this);
   copyAction->setShortcut(QKeySequence::Copy);
   copyAction->setStatusTip("Copies the current selected text");
   connect(copyAction, SIGNAL(triggered()), textEdit, SLOT(copy()));

   pasteAction = new QAction("&Paste", this);
   pasteAction->setShortcut(QKeySequence::Paste);
   pasteAction->setStatusTip(
      "Pastes the last copy or cut text to the text editor");
   connect(pasteAction, SIGNAL(triggered()), textEdit, SLOT(paste()));

   selectAllAction = new QAction("Select &All", this);
   selectAllAction->setShortcut(QKeySequence::SelectAll);
   selectAllAction->setStatusTip("Selects all the text in the document");
   connect(selectAllAction, SIGNAL(triggered()), textEdit, SLOT(selectAll()));
   
   //search
   findAction = new QAction("&Find", this);
   findAction->setShortcut(QKeySequence::Find);
   findAction->setStatusTip("Find the input text");
   connect(findAction, SIGNAL(triggered()), this, SLOT(find()));

}

void MainWindow::createMenus() {

   QMenu *fileMenu = menuBar()->addMenu("&File");
   fileMenu->addAction(newAction);
   fileMenu->addAction(openAction);
   fileMenu->addAction(saveAction);
   fileMenu->addSeparator();
   fileMenu->addAction(closeAction);

   QMenu *editMenu = menuBar()->addMenu("&Edit");
   editMenu->addAction(undoAction);
   editMenu->addSeparator();
   editMenu->addAction(cutAction);
   editMenu->addAction(copyAction);
   editMenu->addAction(pasteAction);
   editMenu->addSeparator();
   editMenu->addAction(selectAllAction);

   QMenu *searchMenu = menuBar()->addMenu("&Search");
   searchMenu->addAction(findAction);
   
}

void MainWindow::createToolBar() {

   QToolBar *fileToolBar = addToolBar("&File");
   fileToolBar->addAction(newAction);
   fileToolBar->addAction(openAction);
   fileToolBar->addAction(saveAction);
   
   QToolBar *editToolBar = addToolBar("&Edit");
   editToolBar->addAction(undoAction);
   editToolBar->addAction(cutAction);
   editToolBar->addAction(copyAction);
   editToolBar->addAction(pasteAction);
   
   QToolBar *searchToolBar = addToolBar("%Search");
   searchToolBar->addAction(findAction);
   
}

bool MainWindow::writeFile(const QString &filename, const QString &text) {

  QFile file(filename);
  
  if (!file.open(QIODevice::WriteOnly)) {
    QMessageBox::warning(this, tr("Unable to save"), 
       tr("Cannot write file %1: %2").arg(filename).arg(file.errorString()));
    return false;
  }
  
  QTextStream out(&file);
  
  out << text;
  return true;

}

bool MainWindow::readFile(const QString &filename, QString &text) {

  QFile file(filename);
  
  if (!file.open(QIODevice::ReadOnly)) {
    QMessageBox::warning(this, tr("Unable to read"), 
       tr("Cannot write file %1: %2").arg(filename).arg(file.errorString()));
    return false;
  }
  
  QTextStream in(&file);
  text = in.readAll();
  return true;
}
bool MainWindow::possibleSave() {
   // find out if they would like to save the file
   QString message = QString("The document has been modified. Would you like to save the changes?");

// something with dialogs
   if(fileChanged) {
      int button =
	 QMessageBox::question(0, QString("File Modified"), message,
			       QMessageBox::Yes | QMessageBox::No
			       | QMessageBox::Cancel,
			       QMessageBox::Cancel);
      if(button == QMessageBox::Yes) {
	 if(save()) {
	    fileChanged = false;
	    return true;
	 }
      } else if(button == QMessageBox::Cancel) {
	 return false;
      }
   }
   return true;
}

//File
void MainWindow::createNew() {

   if(possibleSave()) {
      textEdit->selectAll();
      textEdit->clear();
      fileChanged = false;
   }
}

void MainWindow::open() {

   if(!possibleSave())
      return;
   // open the file
   QString filename = QFileDialog::getOpenFileName(this, QString("Open File ..."));
   if(filename.size() > 0) {
      QString output;
      if(readFile(filename, output)) {
	 textEdit->selectAll();
	 textEdit->clear();
	 QTextDocument *text = new QTextDocument(output);
	 textEdit->setDocument(text);
	 fileChanged = false;
      }
   }
}

bool MainWindow::save() {
   // save the file
   QString filename = QFileDialog::getSaveFileName(this, QString("Save File As ..."));
   QTextDocument *output = textEdit->document();
   if(filename.size() > 0) {
      if(writeFile(filename, output->toPlainText())) {
	 fileChanged = false;
	 return true;
      }
   } else {
      return false;
   }
}

void MainWindow::close() {

   if(possibleSave())
      QMainWindow::close();
}

//search
void MainWindow::find() {
   bool ok;
   QInputDialog findText(this);
   findText.setModal(false);
   QString text = findText.getText(this, QString("Find Text"),
				   QString("Search for text:"),
				   QLineEdit::Normal, QString(""), &ok);
   
   if(ok) {
      if(!textEdit->find(text)) {
	 QMessageBox notFound(QMessageBox::Information, QString("No Match"),
			      QString("Text not found."), QMessageBox::Ok,
			      this);
	 notFound.exec();
	 // output a dialog to say no matching word found
      }
   }
}

void MainWindow::changed() {
   fileChanged = true;
}
