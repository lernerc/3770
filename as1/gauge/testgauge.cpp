//*****************************************************************************
// Name: Camara Lerner
// SN: 001150339
// Class: CPSC 3770
// The test file to run the application for assignment # 1 part 2
//*****************************************************************************
#include <QApplication>

#include <QSlider>
#include <QHBoxLayout>

#include "gauge.h"

int main(int argc, char **argv) {

  QApplication app(argc, argv);
  
  QWidget *widget = new QWidget();
  QSlider *slider = new QSlider();
  Gauge *gauge = new Gauge();
  
  QHBoxLayout *layout = new QHBoxLayout();
  layout->addWidget(slider);
  layout->addWidget(gauge);
  
  widget->setLayout(layout);
  
  QObject::connect( slider, SIGNAL( valueChanged(int) ), gauge, SLOT(setValue(int)));
  
  slider->setRange(0, 100);
  gauge->setRange(0, 100);
  
  gauge->setMinimumSize( QSize(200, 100));
  // gauge->setMaximumSize( QSize(200, 100));

  widget->show();
  
  return app.exec();


}
