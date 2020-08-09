#include "MyCoin.h"

#include <QDebug>
#include <QPixmap>

//MyCoin::MyCoin(QWidget *parent) : QPushButton(parent)
//{

//}


MyCoin::MyCoin(QString btnImg){
    QPixmap pix;
    bool ret = pix.load(btnImg);
    if(!ret){
        QString str = QString("图片%1加载失败").arg(btnImg);
        qDebug() << str;
        return;
    }
    pix = pix.scaled(pix.width()*2, pix.height()*2);
    this->setFixedSize(pix.width(), pix.height());
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(), pix.height()));

    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    connect(timer1, &QTimer::timeout, [=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->min++);
        pix.load(str);
        pix = pix.scaled(pix.width()*2, pix.height()*2);
        this->setFixedSize(pix.width(), pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(), pix.height()));

        //Over:
        if(this->min>this->max){
            this->min = 1;
            timer1->stop();
            isAnimation = false;
        }
    });
    connect(timer2, &QTimer::timeout, [=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->max--);
        pix.load(str);
        pix = pix.scaled(pix.width()*2, pix.height()*2);
        this->setFixedSize(pix.width(), pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(), pix.height()));

        //Over:
        if(this->min>this->max){
            this->max = 8;
            timer2->stop();
            isAnimation = false;
        }
    });

};

void MyCoin::changeFlag(){
    if(this->flag){
        this->flag = false;
        timer1->start(30);
        isAnimation = true;
    }
    else{
        this->flag = true;
        timer2->start(30);
        isAnimation = true;
    }
};

void MyCoin::mousePressEvent(QMouseEvent* e){
    if(this->isAnimation||this->isWin){
        return;
    }else{
        return QPushButton::mousePressEvent(e);
    }
};


