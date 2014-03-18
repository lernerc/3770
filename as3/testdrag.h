#ifndef TESTDRAG_H
#define TESTDRAG_H
#include <QWidget>

class TestDrag : public QWidget {
  Q_OBJECT
 public:
  TestDrag(int w, int h, int iw, int tw, QWidget *p);
 public slots:
  void reset();
 signals:
  void testComplete(int, double, int);

};

#endif
