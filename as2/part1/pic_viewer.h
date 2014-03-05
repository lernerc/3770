//*****************************************************************************
// Name: Camara Lerner
// SN: 001150339
// Class: CPSC 3770
// The header for PicViewer for assignment # 2 part 1
//*****************************************************************************

#ifndef PIC_VIEWER_H
#define PIC_VIEWER_H

#include <QWidget>

class QImage;
class QMouseEvent;
class QPaintEvent;
class QSizeF;
class QPointF;

class PicViewer : public QWidget {

   Q_OBJECT
   
  public:
   PicViewer(QWidget *parent = 0);
   void loadPic(const QString &name);

  protected:
   virtual void mouseReleaseEvent(QMouseEvent *event);
   virtual void mouseMoveEvent(QMouseEvent *event);
   virtual void paintEvent(QPaintEvent *event);
  private:
   QImage image;
   QRectF target, source;
   int mode;
   QPoint move, cursor;
};

#endif
