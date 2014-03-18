#ifndef TESTDRAG_H
#define TESTDRAG_H
#include <QWidget>
#include <QPen>
#include <QPoint>

class QPaintEvent;
class QRect;
class QMouseEvent;

class TestDrag : public QWidget {
  Q_OBJECT
 public:
  TestDrag(int w=600, int h=400, int iw=25, int tw=100, QWidget *p=0);
 public slots:
  void reset();
 signals:
  void testComplete(int, double, int);
  protected:
  virtual void paintEvent(QPaintEvent *event);
  virtual void mousePressEvent(QMouseEvent* event);
  virtual void mouseReleaseEvent(QMouseEvent* event);
  virtual void mouseMoveEvent(QMouseEvent* event);
  private:
  QRect background, icon, target;
  QPen icon_pen, target_pen;
  QPoint pos;
  bool selected;
};

bool operator<(const QPoint &a, const QPoint &b);

#endif
