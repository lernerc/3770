//*****************************************************************************
// Name: Camara Lerner
// SN: 001150339
// Class: CPSC 3770
// The header for Key for assignment # 2 part 2
//*****************************************************************************
#include <QWidget>

class Keyboard : public QWidget {

  Q_OBJECT

public:

  Keyboard(QWidget *p=0);
     
public slots:

  void setDelay( int d );
  void setTolerance( qreal t );

signals:

  void emitString(const QString &str);

};
