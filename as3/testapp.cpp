
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include "testapp.h"


TestApp::TestApp(QWidget *p)  : QWidget(p) {

  leTime = new QLineEdit();
  leDistance = new QLineEdit();
  leDrops = new QLineEdit();

  leTime->setReadOnly(true);
  leDistance->setReadOnly(true);
  leDrops->setReadOnly(true);

  pbReset = new QPushButton("Reset Test");

  QLabel *header1 = new QLabel("Controls");
  header1->setStyleSheet("QLabel { font-weight: bold; font-size: 16px; } ");

  QLabel *header2 = new QLabel("Results");
  header2->setStyleSheet("QLabel { font-weight: bold; font-size: 16px; } ");

  QGridLayout *layout = new QGridLayout();
  layout->addWidget(header1, 0, 0);
  layout->addWidget(pbReset, 1, 0);
  layout->addWidget(header2, 0, 2, 1, 2);
  layout->addWidget(new QLabel("Time (ms):     "), 1, 2 );
  layout->addWidget(new QLabel("Distance (px): "), 2, 2 );
  layout->addWidget(new QLabel("Drops:         "), 3, 2 );
  layout->addWidget(leTime,     1, 3);
  layout->addWidget(leDistance, 2, 3);
  layout->addWidget(leDrops,    3, 3);

  layout->setColumnMinimumWidth(1, 40);

  QHBoxLayout *top = new QHBoxLayout();
  top->addLayout(layout);
  top->addStretch();

  QVBoxLayout *layout2 = new QVBoxLayout();
  layout2->addLayout(top);
 
  tf = new TestDrag(600, 400);

  layout2->addWidget(tf);

  setLayout(layout2);
  setFixedSize( sizeHint () ); 

  connect( pbReset, SIGNAL( clicked() ), this, SLOT( reset() ) );
  connect( tf, SIGNAL( testComplete(int, double, int) ), this, SLOT( testComplete(int, double, int) ) );

}

void TestApp::testComplete(int time, double distance, int drops) {
  leTime->setText( QString("%1").arg(time) );
  leDistance->setText( QString("%1").arg(distance) );
  leDrops->setText( QString("%1").arg(drops) );
  QMessageBox::information(this, "Test Complete", "Test Complete");
}

void TestApp::reset() {
  tf->reset();
  leTime->clear();
  leDistance->clear();
  leDrops->clear();
}
