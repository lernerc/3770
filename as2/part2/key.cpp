//*****************************************************************************
// Name: Camara Lerner
// SN: 001150339
// Class: CPSC 3770
// The implementation file for Key for assignment # 2 part 2
//*****************************************************************************
#include "key.h"

Key::Key(const QString &d, int del, qreal tol, QWidget *p) : QLabel(p) {
   delay = del;
   tolerance = tol;
   // do something with d
}

void Key::setDelay(int d) {
   delay = d;
}

void Key::setTolerance(qreal t) {
   tolerance = t;
}

/*void Key::emitString(const QString &str) {

}
*/
