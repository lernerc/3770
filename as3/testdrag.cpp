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
   drag.push_back(icon.topLeft());
}

void TestDrag::reset() {
   icon.moveTo(10, 10);
   drag.clear();
   drop.clear();
   drag.push_back(icon.topLeft());
   // reset any test information
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
  // if test done
  // finish stuff
  // else
  drop.push_back(icon.topLeft());
  update();

}

void TestDrag::mouseMoveEvent(QMouseEvent* event) {
  if(selected) {
     if(((icon.bottomRight() + event->pos() - pos) < background.bottomRight())
	&& ((icon.topLeft() + event->pos() - pos) > background.topLeft()))
	icon.translate(event->pos() - pos);
     else {
	// moves the icon to the actual edge 
	if(icon.bottomRight().x() + event->pos().x() - pos.x()
	   > background.bottomRight().x())
	   icon.moveTo(background.bottomRight().x() - icon.width(),
		       pos.y());
	if(icon.bottomRight().y() + event->pos().y() - pos.y()
	   > background.bottomRight().y())
	   icon.moveTo(pos.x(),
		       background.bottomRight().y() - icon.height());
	if(icon.topLeft().x() + event->pos().x() - pos.x()
	   < background.topLeft().x())
	   icon.moveTo(background.topLeft().x(), pos.y());
	if(icon.topLeft().y() + event->pos().y() - pos.y()
	   < background.topLeft().y())
	   icon.moveTo(pos.x(), background.topLeft().y());
	
	selected=false;
	// do I have to do this, because I force them to release the mouse to
	// continue to move it
        //drop.push_back(icon.topLeft());
     }
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
   return a.x() < b.x() && a.y() < b.y();
}

bool operator>(const QPoint &a, const QPoint &b) {
   return a.x() > b.x() && a.y() > b.y();
}
