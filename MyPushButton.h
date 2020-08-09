#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    ///explicit MyPushButton(QWidget *parent = nullptr);
    MyPushButton(QString normalImg, QString pressedImg="");

    QString normalImgPath;
    QString pressedImgPath;

    //按钮按下抬起模拟
    void zoom1();
    void zoom2();

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);


signals:

};

#endif // MYPUSHBUTTON_H
