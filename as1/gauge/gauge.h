//*****************************************************************************
// Name: Camara Lerner
// SN: 001150339
// Class: CPSC 3770
// The header file for Gauge in assignment # 1 part 2
//*****************************************************************************
#ifndef GAUGE_H
#define GAUGE_H

#include <QWidget>

class Gauge : public QWidget {

  Q_OBJECT
  
public: 

  Gauge(QWidget *parent = 0);
  void setRange(int l, int h);

public slots:

  void setValue(int val);
  
protected:

  void paintEvent(QPaintEvent *event);
  
private:

  int low, high;
  int value;

};

#endif
