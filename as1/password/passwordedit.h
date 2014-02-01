//*****************************************************************************
// Name: Camara Lerner
// SN: 001150339
// Class: CPSC 3770
// The header file for PasswordEdit for assignment # 1 part 1
//*****************************************************************************

#ifndef PASSWORDEDIT_H
#define PASSWORDEDIT_H

#include <QLineEdit>

class QString;

class PasswordEdit : public QLineEdit {

  Q_OBJECT
  
public:

  PasswordEdit(QWidget *parent=0);
  QString text() const;
  
  public slots:

  void clear();
  void copy() const;
  void cut();
  void paste();
  void setText(const QString &);

  protected:

  virtual void keyPressEvent(QKeyEvent *);
  virtual void mousePressEvent(QMouseEvent *);
  virtual void mouseReleaseEvent(QMouseEvent *);
  private:

  QString password;
};

#endif
