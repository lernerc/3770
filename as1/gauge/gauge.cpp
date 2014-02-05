//*****************************************************************************
// Name: Camara Lerner
// SN: 001150339
// Class: CPSC 3770
// The implemetation file for Gauge in assignment # 1 part 2
//*****************************************************************************
#include "gauge.h"
#include <algorithm>
#include <QPainter>
#include <QVector>
#include <iostream>

Gauge::Gauge(QWidget *parent) : QWidget(parent) {
   value = low = 0;
   high = 100;
}

void Gauge::setRange(int l, int h) {
   low = l;
   high = h;
   update();
}

void Gauge::setValue(int val) {
   value = std::max(std::min(val, high), low);
   update();
}
  
void Gauge::paintEvent(QPaintEvent *event) {
   QPainter painter(this);

   painter.setRenderHint(QPainter::Antialiasing, true);
   QPen pen;
   pen.setWidth(2);

   // draw the beginning of the light ticks
   
   if((double)(value - low)/(high - low) < 0.5) {
      pen.setColor(Qt::green);
   } else if((double)(value - low)/(high - low) < 0.8) {
      pen.setColor(Qt::yellow);
   } else {
      pen.setColor(Qt::red);
   }
   painter.setPen(pen);

   int i = 0;
   painter.setWindow(-50, -50, 100, 100);
   double rotate = 270.0/30;
   painter.rotate(225);
   int ticks = (int)((double)(value - low)/(double)(high - low)*30 + 0.5) + 1;
   double sum = 0;
   for(; i < ticks; i++) {
      painter.drawRect(0, -48, 1, 5);
      if(i != 30)
	 painter.rotate(rotate);
   }

   // draw the dark ticks
   
   if((double)(value - low)/(high - low) < 0.5) {
      pen.setColor(Qt::darkGreen);
   } else if((double)(value - low)/(high - low) < 0.8) {
      pen.setColor(Qt::darkYellow);
   } else {
      pen.setColor(Qt::darkRed);
   }
   painter.setPen(pen);
      
   for(; i < 31; i++) {
      sum += rotate;
      painter.drawRect(0, -48, 1, 5);
      if(i!=30)
	 painter.rotate(rotate);
   }

   // drawing the needle
   
   pen.setColor(Qt::black);
   painter.setPen(pen);
   painter.rotate((double)(value - low)/(high - low)*270 + 270);
   painter.drawRect( 0, 0, 1, 40);
   
}
   
