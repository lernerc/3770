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

};
