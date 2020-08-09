#include "MyPushButton.h"

#include <QPushButton>
#include <QDebug>
#include <QPropertyAnimation>
#include <QMouseEvent>
//MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
//{

//}

MyPushButton::MyPushButton(QString normalImg, QString pressedImg){
    this->normalImgPath = normalImg;
    this->pressedImgPath = pressedImg;

    QPixmap pix;
    bool ret = pix.load(normalImg);
    pix = pix.scaled(pix.width()*2, pix.height()*2);
    if(!ret){
        qDebug()<<"图片加载失败";
        return;
    }

    this->setFixedSize(pix.width(), pix.height());

    //去掉边框
    this->setStyleSheet("QPushButton{border:0px;}");

    this->setIcon(pix);

    this->setIconSize(QSize(pix.width(), pix.height()));

};

void MyPushButton::zoom1(){
    //创建动画对象
    QPropertyAnimation* animation = new QPropertyAnimation(this, "geometry");

    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    animation->setEndValue(QRect(this->x(), this->y()+20, this->width(), this->height()));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    animation->start();

};

void MyPushButton::zoom2(){
    //创建动画对象
    QPropertyAnimation* animation = new QPropertyAnimation(this, "geometry");

    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(), this->y()+20, this->width(), this->height()));
    animation->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    animation->start();
}

void MyPushButton::mousePressEvent(QMouseEvent *e){
    if(this->pressedImgPath!=""){
        QPixmap pix;
        bool ret = pix.load(this->pressedImgPath);
        pix = pix.scaled(pix.width()*2, pix.height()*2);
        if(!ret){
            qDebug()<<"图片加载失败";
            return;
        }
        this->setFixedSize(pix.width(), pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(), pix.height()));
    }
    return QPushButton::mousePressEvent(e);
};
void MyPushButton::mouseReleaseEvent(QMouseEvent *e){
    if(this->pressedImgPath!=""){
        QPixmap pix;
        bool ret = pix.load(this->normalImgPath);
        pix = pix.scaled(pix.width()*2, pix.height()*2);
        if(!ret){
            qDebug()<<"图片加载失败";
            return;
        }
        this->setFixedSize(pix.width(), pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(), pix.height()));
    }
    return QPushButton::mouseReleaseEvent(e);
};
