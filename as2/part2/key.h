//*****************************************************************************
// Name: Camara Lerner
// SN: 001150339
// Class: CPSC 3770
// The header for Key for assignment # 2 part 2
//*****************************************************************************

#ifndef KEY_H
#define KEY_H

#include <QWidget>
#include <QLabel>
#include <QSize>

class QTimer;
class QPoint;
class QMouseEvent;

class Key : public QLabel {

  Q_OBJECT

public:

   Key(const QString &d="", int del=250, qreal tol=1.0, QWidget *p=0);
    
   QSize sizeHint() const { return QSize(100, 100); }
   
   public slots:
   
   void setDelay(int d);
   void setTolerance(qreal t);
   void mouseMoveEvent(QMouseEvent *event);
   void emitSignal();
   
  protected:
   
   virtual void enterEvent(QEvent *event);
   virtual void leaveEvent(QEvent *event);

/*   private slots:

   void 
*/ 
  signals:
   
   void emitString(const QString &str);
   
  private:
   int delay;
   qreal tolerance;
   QTimer* time;
   QPoint position;
   bool emitted;
};
#endif
