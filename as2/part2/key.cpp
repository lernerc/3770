//*****************************************************************************
// Name: Camara Lerner
// SN: 001150339
// Class: CPSC 3770
// The implementation file for Key for assignment # 2 part 2
//*****************************************************************************
#include "key.h"
#include <QString>
#include <QTimer>
#include <QPalette>
// do something with the a time interval and a signal in QTimer for the delay stuff

Key::Key(const QString &d, int del, qreal tol, QWidget *p) : QLabel(d, p) {
   delay = del;
   tolerance = tol;
   setAlignment(Qt::AlignCenter);
   setAutoFillBackground(true);
   setPalette(QPalette(Qt::black, Qt::white));
   time.setInterval(tolerance);
}

void Key::setDelay(int d) {
   delay = d;
}

void Key::setTolerance(qreal t) {
   tolerance = t;
   time.setInterval(tolerance);
}

void Key::enterEvent(QEvent *event) {
   time.start();
   // if considered stopped
   // emitString(text());

}

void Key::leaveEvent(QEvent *event) {
   time.stop();
}
