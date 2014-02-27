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
#include <QPoint>
#include <QMouseEvent>
#include <cmath>
// do something with the a time interval and a signal in QTimer for the delay stuff

Key::Key(const QString &d, int del, qreal tol, QWidget *p) : QLabel(d, p) {
   delay = del;
   tolerance = tol;
   setAlignment(Qt::AlignCenter);
   setAutoFillBackground(true);
   setPalette(QPalette(Qt::black, Qt::white));
   time = new QTimer();
   time->setInterval(delay);

/*   connect(this, SLOT(enterEvent), time, SLOT(start()));
   connect(this, SLOT(leaveEvent), time, SLOT(stop()));
*/
   QWidget::setMouseTracking(true);
}

void Key::setDelay(int d) {
   delay = d;
   time->setInterval(delay);
}

void Key::setTolerance(qreal t) {
   tolerance = t;
}

qreal dist(const QPoint& a, const QPoint& b) {
   qreal x = a.x() - b.x(), y = a.y() - b.y();
   return std::sqrt(x*x + y*y);
}

void Key::mouseMoveEvent(QMouseEvent *event) {
   QLabel::mouseMoveEvent(event);
   if(dist(event->pos(), position) < tolerance) {
     if(time->isActive())
	 emitString(text());
   } else {
      time->start();
   }
   update();
}


void Key::enterEvent(QEvent *event) {
  time->start();
}

void Key::leaveEvent(QEvent *event) {
  time->stop();
}
