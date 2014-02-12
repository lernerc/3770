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
}

void PicViewer::loadPic(const QString &name) {
   
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
  
}

void PicViewer::mouseMoveEvent(QMouseEvent *event) {
      
}

void PicViewer::paintEvent(QPaintEvent *event) {

   // QPainter has a function drawImage to render the image at different sizes
   QPainter painter(this);
   painter.drawImage(totalImage, image, want);
}
