//*****************************************************************************
// Name: Camara Lerner
// SN: 001150339
// Class: CPSC 3770
// The implementation file for PicViewer for assignment # 2 part 1
//*****************************************************************************
#include "pic_viewer.h"
#include <QMouseEvent>
#include <QPaintEvent>
#include <QImage>
#include <QPainter>
#include <QMessageBox>
#include <QRectF>

#include <iostream>
#include <cmath>

// 0 Normal Mode
// 1 Move Mode use setMouseTracking
// 2 Zoom Mode - each pixel move you multiply by 1.02 so pow(1.02, pixel moves)

PicViewer::PicViewer(QWidget *parent) : QWidget(parent) {
   mode = 0;
   QWidget::setMouseTracking(true);
}

void PicViewer::loadPic(const QString &name) {
   mode = 0;
   if(image.load(name)) {
      target = QRectF(0,0, image.size().width(), image.size().height()); 
      source = QRectF(0,0, image.size().width(), image.size().height());
      update();
   } else {
      QMessageBox notLoaded(QMessageBox::Critical, QString("Loading Error"),
			    QString("The file given could not be loaded."),
			    QMessageBox::Ok, this);
      notLoaded.exec();
   }
}

void PicViewer::mouseReleaseEvent(QMouseEvent *event) {
   if(event->button() == Qt::LeftButton) {
      mode++;
      mode %= 3;
   }
   update();
}

void PicViewer::mouseMoveEvent(QMouseEvent *event) {
   update();
}

void PicViewer::paintEvent(QPaintEvent *event) {
   move = QCursor::pos() - cursor;
   cursor = QCursor::pos();

   // QPainter has a function drawImage to render the image at different sizes
   QPainter painter(this);
   if(mode == 0)
      painter.drawImage(target, image, source);
   else if(mode == 1) {
      
      // move mode
      target =  QRectF(target.topLeft().x() + move.x(),
		       target.topLeft().y() + move.y(),
		       target.size().width(), target.size().height());
      painter.drawImage(target, image, source);
            
      // two equally sized rectanges beside the cursor
      painter.drawRect( cursor.x() + 5, cursor.y() - 8, 10, 5);
      painter.drawRect( cursor.x() + 7, cursor.y() - 6, 10, 5);

   } else if(mode == 2) {

      // zoom mode assume zooming around top left corner
      qreal mult = std::pow(1.02, move.y());
      qreal width = target.size().width() * mult,
	 height = target.size().height() * mult;
      target = QRectF(target.topLeft().x(),
		      target.topLeft().y(),
		      width, height);
      painter.drawImage(target, image, source);
      
      // two rectanges one inside the other beside the cursor
      painter.drawRect( cursor.x() + 5, cursor.y() - 8, 10, 6);
      painter.drawRect( cursor.x() + 7, cursor.y() - 6, 6, 2);
   }
}
