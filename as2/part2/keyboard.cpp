#include "keyboard.h"


Keyboard::Keyboard(QWidget *p) : QWidget(p) {
   for(int i = 0; i <= 9; i++) {
      key[i] = Key(i+'0', 250, 1.0, this);
   }
   key[10] = Key('*', 250, 1.0, this);
   key[11] = Key('#', 250, 1.0, this);
   
}

void Keyboard::setDelay( int d ) {
   for(int i = 0; i < key_max; i++) {
      key[i].setDelay(d);
   }
}

void Keyboard::setTolerance( qreal t ) {
   for(int i = 0; i < key_max; i++) {
      key[i].setTolerance(t);
   }
}

