// Normal Mode
// Move Mode use setMouseTracking
// Zoom Mode - each pixel move you multiply by 1.02 so pow(1.02, pixel moves)
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
};
