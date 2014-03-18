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
   selected = false;
   update();
}

void TestDrag::reset() {

}

void TestDrag::mousePressEvent(QMouseEvent* event) {
   pos = event->pos();
   if(icon.contains(event->pos())) {
     selected = true;
     icon_pen.setWidth(3);
   }
   update();
}

void TestDrag::mouseReleaseEvent(QMouseEvent* event) {
  selected = false;
  icon_pen.setWidth(1);
  target_pen.setWidth(1);
  update();
}

void TestDrag::mouseMoveEvent(QMouseEvent* event) {
  if(selected) {
    if((icon.bottomRight() + event->pos() - pos < background.bottomRight())
       && (icon.bottomLeft() + event->pos() - pos < background.bottomLeft())
       && (icon.topRight() + event->pos() - pos > background.topRight())
       && (icon.topLeft() + event->pos() - pos > background.topLeft()))
      icon.translate(event->pos() - pos);
    else
      selected=false;
    pos = event->pos();
  }
   
   
   if(target.contains(icon, true) && selected)
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

bool operator<(const QPoint &a, const QPoint &b) {
  if(a.x() != b.x())
    return a.x() < b.x();
  return a.y() < b.y();
}
