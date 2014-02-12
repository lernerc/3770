//*****************************************************************************
// Name: Camara Lerner
// SN: 001150339
// Class: CPSC 3770
// The header for PicViewer for assignment # 2 part 1
//*****************************************************************************
#include <QWidget>

class QImage;
class QMouseEvent;
class QPaintEvent;

class PicViewer : public QWidget {
  public:
   PicViewer(QWidget *parent = 0);
   void loadPic(const QString &name);

  protected:
   virtual void mouseReleaseEvent(QMouseEvent *event);
   virtual void mouseMoveEvent(QMouseEvent *event);
   virtual void paintEvent(QPaintEvent *event);
  private:
   QImage image;
   QRectF totalImage, want;
   int mode;
   QPoint cursor;
   QPoint modeStart;
   QPointF topLeft;
};
