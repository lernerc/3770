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
      totalImage = QRectF(0,0, image.size().width(), image.size().height());
      want = QRectF(0,0, image.size().width(), image.size().height());
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
      topLeft = want.topLeft();
      wantSize = want.size();
      mode++;
      mode %= 3;
      modeStart = event->pos();
   }
   cursor = event->pos();
   update();
}

void PicViewer::mouseMoveEvent(QMouseEvent *event) {
   cursor = event->pos();
   update();
}

void PicViewer::paintEvent(QPaintEvent *event) {

   // QPainter has a function drawImage to render the image at different sizes
   QPainter painter(this);
   if(mode == 0) {
      painter.drawImage(totalImage, image, want);
   } else if(mode == 1) {
      // move mode
      want = QRectF(topLeft.x() + modeStart.x() - cursor.x(),
		    topLeft.y() + modeStart.y() - cursor.y(),
	 want.size().width(), want.size().height());
      painter.drawImage(totalImage, image, want);
      
      
      
      // two equally sized rectanges beside the cursor
      painter.drawRect( cursor.x() + 5, cursor.y() - 8, 10, 5);
      painter.drawRect( cursor.x() + 7, cursor.y() - 6, 10, 5);
   } else if(mode == 2) {
      // zoom mode assume zooming around top left corner
      double mult = std::pow(1.02, modeStart.y() - cursor.y());
      want = QRectF( want.topLeft().x(), want.topLeft().y(),
		     wantSize.width() * mult, wantSize.height() * mult);
      painter.drawImage(totalImage, image, want);

      // two rectanges one inside the other beside the cursor
      painter.drawRect( cursor.x() + 5, cursor.y() - 8, 10, 6);
      painter.drawRect( cursor.x() + 7, cursor.y() - 6, 6, 2);
   }
}
