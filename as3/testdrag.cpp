//*****************************************************************************
// Name: Camara Lerner
// SN: 001150339
// Class: CPSC 3770
// The TestDrag implementation file for assignment # 3 part 1
//*****************************************************************************
#include "testdrag.h"
#include <QPaintEvent>
#include <QPainter>
#include <QRect>
#include <QMouseEvent>
#include <cmath>
#include <cstdlib>

TestDrag::TestDrag(int w, int h, int iw, int tw, QWidget *p) : QWidget(p) {
   background = QRect(0, 0, w, h);
   icon = QRect( 10, 10, iw, iw);
   target = QRect(w-tw-10, h-tw-10, tw, tw);
   isTest=false;
   testDone=false;
   selected = false;
   time = new QTimer(this);
   target_pen = QPen(Qt::darkBlue);
   icon_pen = QPen(Qt::darkGreen);

   connect(time, SIGNAL(timeout()), this, SLOT(addPoint()));

   setMinimumSize(w+2, h+2);
   icon_pen.setWidth(1);
   target_pen.setWidth(1);
   drag.push_back(icon.topLeft());
   line.moveTo(icon.topLeft());
   time->setInterval(50);
   QWidget::setMouseTracking(true);
   update();

}

void TestDrag::addPoint() {
   drag.push_back(icon.topLeft());
   line.lineTo(icon.topLeft());
}

void TestDrag::reset() {
   icon.moveTo(10, 10);
   drag.clear();
   line = QPainterPath();
   drop.clear();
   drag.push_back(icon.topLeft());
   line.moveTo(icon.topLeft());
   isTest=false;
   testDone=false;
   update();// reset any test information
}

void TestDrag::mousePressEvent(QMouseEvent* event) {
   if(!isTest && !testDone) {
      isTest=true;
      time->start();
      totalTime.start();
   }
   pos = event->pos();
   if(icon.contains(event->pos()) && !testDone) {
     selected = true;
     icon_pen.setWidth(3);
   }
   update();
}

void TestDrag::mouseReleaseEvent(QMouseEvent* event) {
  selected = false;
  icon_pen.setWidth(1);
  target_pen.setWidth(1);
  if(target.contains(icon) && !testDone) {
     selected=false;
     testDone=true;
     time->stop();
     qreal dist = calcDist(drag);
     update();
     testComplete(totalTime.elapsed(), dist, drop.size());
  }
  // finish stuff
  // else
  if(!testDone)
     drop.push_back(icon.topLeft());
  update();

}

void TestDrag::mouseMoveEvent(QMouseEvent* event) {
  if(selected && !testDone) {
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
   //p.setRenderHint(QPainter::Antialiasing, true);
   p.drawRect(background);
   p.setPen(target_pen);
   p.drawRect(target);
   p.setPen(icon_pen);
   p.drawRect(icon);
   if(testDone) {
      p.drawPath(line);
      icon_pen.setWidth(3);
      p.setPen(icon_pen);
      for(int i = 0; i < drag.size(); i++)
	 p.drawEllipse(drag[i].x(), drag[i].y(), 3, 3);
      icon_pen.setWidth(1);
      QPen d(Qt::red);
      d.setWidth(3);
      p.setPen(d);
      QPoint x(5,0), y(0, 5);
      for(int i = 0; i < drop.size(); i++) {
	 p.drawLine(drop[i]+x+y, drop[i]-x-y);
	 p.drawLine(drop[i]+x-y, drop[i]-x+y);
      }
   }
}

bool operator<(const QPoint &a, const QPoint &b) {
   return a.x() < b.x() && a.y() < b.y();
}

bool operator>(const QPoint &a, const QPoint &b) {
   return a.x() > b.x() && a.y() > b.y();
}

qreal calcDist(QVector<QPoint> a) {
   qreal dist = 0;
   for(int i = 0; i < (int)a.size() - 1; i++) {
      dist += std::sqrt((a[i].x()-a[i+1].x())*(a[i].x()-a[i+1].x())
		   + (a[i].y()-a[i+1].y())*(a[i].y()-a[i+1].y()));
   }
   return dist;
}
