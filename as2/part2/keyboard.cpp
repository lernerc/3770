#include "keyboard.h"
#include "key.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>

#include <iostream>

const QString keys[key_max] =
{"1","2","3","4","5","6","7","8","9","*","0","#"};

Keyboard::Keyboard(QWidget *p) : QWidget(p) {
   for(int i = 0; i < key_max; i++) {
      key[i] = new Key( keys[i], 250, 1.0, this);
   }

   QHBoxLayout *row[4];
   for(int i = 0; i < 4; i++) {
      row[i] = new QHBoxLayout();
   }
   for(int i = 0; i < 4; i++) {
      for(int j = 0; j < 3; j++) {
	 row[i]->addWidget(key[i*3+j]);
	 connect(key[i*3+j], SIGNAL(emitString(const QString &)), 
		 this, SLOT(addToString(const QString&)));
     }
   }
   
   QVBoxLayout *layout = new QVBoxLayout();
   for(int i = 0; i < 4; i++)
      layout->addLayout(row[i]);
   this->setLayout(layout);
}

void Keyboard::setDelay( int d ) {
   for(int i = 0; i < key_max; i++) {
      key[i]->setDelay(d);
   }
}

void Keyboard::setTolerance( qreal t ) {
   for(int i = 0; i < key_max; i++) {
      key[i]->setTolerance(t);
   }
}

void Keyboard::addToString(const QString &str) {
   emitString(str);
}
