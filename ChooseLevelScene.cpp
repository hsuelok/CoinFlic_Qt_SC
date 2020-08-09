#include "ChooseLevelScene.h"
#include <QIcon>
#include <QMenuBar>
#include <QMenu>
#include <QPainter>
#include "MyPushButton.h"
#include <QTimer>
#include <QLabel>
#include <QDebug>
#include <QSound>

ChooseLevelScene::ChooseLevelScene(QMainWindow *parent) : QMainWindow(parent)
//ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(320*2, 588*2);
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    this->setWindowTitle("选择关卡");

    QMenuBar* bar = menuBar();
    //QMenuBar* bar = new QMenuBar;
    bar->setParent(this);
    QMenu* startMenu = bar->addMenu("开始");
    QAction* quitAction = startMenu->addAction("退出");
    connect(quitAction, &QAction::triggered, [=](){
        this->close();
    });

    // sound selected
    QSound* chooseSound = new QSound(":/res/TapButtonSound.wav");
    QSound* backSound = new QSound(":/res/BackButtonSound.wav");

    MyPushButton* backBtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    //backBtn->resize(QSize(backBtn->width()*5, backBtn->height()*5));

    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(), this->height()-backBtn->height());

    //mainScene = new MainScene;

    connect(backBtn, &MyPushButton::clicked, [=](){

        backSound->play();
        //mainScene->show();
        QTimer::singleShot(200, this, [=](){
            emit this->chooseSceneBack();
            this->hide();
        });
    });



    // create the button choosing level
    for(int i=0; i<20; i++){
        MyPushButton * menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(i%4*140+50, i/4*140+260);

        connect(menuBtn, &MyPushButton::clicked, [=](){
            chooseSound->play();

            QString str = QString("level %1 selected").arg(i+1);
            qDebug() << str;

            this->hide();
            play = new PlayScene(i+1);
            play->setGeometry(this->geometry());
            play->show();

            connect(play, &PlayScene::chooseSceneBack, [=](){
                this->setGeometry(play->geometry());
                play->hide();
                this->show();
                delete play;
                play = NULL;
            });


        });


        QLabel* label = new QLabel(this);
        label->setFixedSize(menuBtn->width(), menuBtn->height());
        label->setText(QString::number(i+1));
        label->move(i%4*140+50, i/4*140+260);
        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        //penetration
        label->setAttribute(Qt::WA_TransparentForMouseEvents);

    }

}


void ChooseLevelScene::paintEvent(QPaintEvent* e){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width()*2)*0.5, 60, pix.width()*2, pix.height()*2, pix);
};
