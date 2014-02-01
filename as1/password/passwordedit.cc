//*****************************************************************************
// Name: Camara Lerner
// SN: 001150339
// Class: CPSC 3770
// The implementation file for PasswordEdit for assignment # 1 part 1
//*****************************************************************************

#include "passwordedit.h"
#include <QString>
#include <QKeyEvent>
#include <Qt>
#include <iostream>
using namespace std;


PasswordEdit::PasswordEdit(QWidget *parent) : QLineEdit(parent) {
   password = "";  
}

void PasswordEdit::clear() {
   password="";
   QLineEdit::clear();
}

void PasswordEdit::setText(const QString& now) {
   password = now;
   QLineEdit::setText(QString(password.size(), '*'));
}

QString PasswordEdit::text() const {
   return password;
}

void PasswordEdit::keyPressEvent(QKeyEvent *event) {

   int cursor = cursorPosition();
   if(event->key() >= Qt::Key_Home && event->key() <= Qt::Key_Down) {
      QLineEdit::keyPressEvent(event);
      return;
   } else {
      if(hasSelectedText()) {
	 int str = selectionStart();
	 if((event->key() == Qt::Key_Space)
	    || (event->key() >= Qt::Key_Exclam
		&& event->key() <= Qt::Key_AsciiTilde)
	    || (event->key() == Qt::Key_Backspace)
	    || (event->key() == Qt::Key_Delete)) {
	    password.remove(str, selectedText().length());
	    setText(password);
	    bool sure = false;
	    cursorBackward(sure, password.size());
	    cursorForward(sure, str);
	    if((event->key() == Qt::Key_Backspace)
	       || (event->key() == Qt::Key_Delete)) {
	       return;
	    }
	 }
      } else if(event->key() == Qt::Key_Backspace) {
	 if(cursor >= 1) {
	    password.remove(cursor - 1, 1);
	    cursor--;
	 }
	 QLineEdit::keyPressEvent(event);
	 QLineEdit::keyPressEvent(event);
	 bool sure = false;
	 setText(password);
	 cursorBackward(sure, password.size());
	 cursorForward(sure,cursor);
	 return;
      } else if(event->key() == Qt::Key_Delete) {
	 if(cursor <= password.size() - 1)
	    password.remove(cursor, 1);
	 QLineEdit::keyPressEvent(event);
	 QLineEdit::keyPressEvent(event);
	 bool sure = false;
	 setText(password);
	 cursorBackward(sure, password.size());
	 cursorForward(sure,cursor);
	 return;
      }
      if((event->key() == Qt::Key_Space)
	 || (event->key() >= Qt::Key_Exclam
	     && event->key() <= Qt::Key_AsciiTilde)) {
	 password.insert(cursor, event->text());
    	 cursor++;
      }
   }
    
   QLineEdit::keyPressEvent(event);
   bool sure = false;
   setText(password);
   cursorBackward(sure, password.size());
   cursorForward(sure,cursor);
}

void PasswordEdit::mousePressEvent(QMouseEvent *event)  {
   if(event->button() == Qt::LeftButton
      && event->modifiers().testFlag(Qt::ShiftModifier)) {
      QLineEdit::setText(password);
   }
   QLineEdit::mousePressEvent(event);
}

void PasswordEdit::mouseReleaseEvent(QMouseEvent *event) {
   QLineEdit::mouseReleaseEvent(event);
   setText(password);
}

void PasswordEdit::copy() const {
   //???????????????????????????????????????????????????????????????????????????
}

void PasswordEdit::cut() {
   //???????????????????????????????????????????????????????????????????????????
}

void PasswordEdit::paste() {
   //???????????????????????????????????????????????????????????????????????????
}

