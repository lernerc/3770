#include "testdrag.h"
#include <QPaintEvent>
#include <QPainter>
#include <QRect>
#include <QMouseEvent>

TestDrag::TestDrag(int w, int h, int iw, int tw, QWidget *p) : QWidget(p) {
   background = QRect(0, 0, w, h);
   icon = QRect( 10, 10, iw, iw);
   target = QRect(w-tw-10, h-tw-10, tw, tw);
   QWidget::setMouseTracking(true);
   setMinimumSize(w+2, h+2);
   icon_pen = QPen(Qt::darkGreen);
   icon_pen.setWidth(1);
   target_pen = QPen(Qt::darkBlue);
   target_pen.setWidth(1);
   update();
}

void TestDrag::reset() {

}

void TestDrag::mousePressEvent(QMouseEvent* event) {
   pos = event->pos();
   if(icon.contains(event->pos()))
      icon_pen.setWidth(3);
   update();
}

void TestDrag::mouseReleaseEvent(QMouseEvent* event) {
   icon_pen.setWidth(1);
   target_pen.setWidth(1);
   update();
}

void TestDrag::mouseMoveEvent(QMouseEvent* event) {
   if(icon_pen.width() == 3) {
      icon.translate(event->pos() - pos);
      pos=event->pos();
   }
   
   
   if(target.contains(icon, true) && icon_pen.width() == 3)
      target_pen.setWidth(3);
   else
      target_pen.setWidth(1);
   update();
}


void TestDrag::paintEvent(QPaintEvent *event) {
   QPainter p(this);
   p.drawRect(background);
   p.setPen(target_pen);
   p.drawRect(target);
   p.setPen(icon_pen);
   p.drawRect(icon);
}
