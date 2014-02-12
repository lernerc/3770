#include "pic_viewer.h"
#include <QMouseEvent>
#include <QPaintEvent>
#include <QImage>
#include <QPainter>
#include <QMessageBox>
#include <iostream>
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
      want = totalImage;
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
   painter.drawImage(totalImage, image, want);
   
   if(mode == 1) {
      // move mode
      // two equally sized rectanges beside the cursor
      painter.drawRect( cursor.x() + 5, cursor.y() - 8, 10, 5);
      painter.drawRect( cursor.x() + 7, cursor.y() - 6, 10, 5);
   } else if(mode == 2) {
      // zoom mode
      // two rectanges one inside the other beside the cursor
      painter.drawRect( cursor.x() + 5, cursor.y() - 8, 10, 6);
      painter.drawRect( cursor.x() + 7, cursor.y() - 6, 6, 2);
   }
}
