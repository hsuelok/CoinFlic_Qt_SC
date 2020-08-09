#include "MainScene.h"
#include "ui_MainScene.h"

#include <QPushButton>
#include <QAction>
#include <QPainter>
#include <MyPushButton.h>
#include <QDebug>
#include <QTimer>
#include <QSound>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    setFixedSize(320*2, 588*2);

    setWindowIcon(QIcon(":/res/Coin0001.png"));
    setWindowTitle("Home");


    //退出按钮
//    connect(ui->actionexit, &QPushButton::clicked, [=](){
//        this->close();
//    });
    connect(ui->actionexit, &QAction::triggered, [=](){
        this->close();
    });

    QSound* startSound = new QSound(":/res/TapButtonSound.wav", this);


    MyPushButton* startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()/2 - startBtn->width()/2, this->height()*0.7);

    chooseScene = new ChooseLevelScene;

    connect(startBtn, &MyPushButton::clicked, [=](){
        //qDebug()<<"clicked";

        //media play

        startSound->play();

        startBtn->zoom1();

        startBtn->zoom2();

        connect(chooseScene, &ChooseLevelScene::chooseSceneBack, this, [=](){
            this->setGeometry(chooseScene->geometry());
            chooseScene->hide();
            this->show();
        });
        //延时
        QTimer::singleShot(400, this, [=](){
            //set the pos for new window;
            chooseScene->setGeometry(this->geometry());

            chooseScene->show();
            this->hide();
        });




    });



}


void MainScene::paintEvent(QPaintEvent* e){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    //画图标（左上角）
    pix.load(":/res/Title.png");
    //pix = pix.scaled(pix.width()*0.5, pix.height()*0.5);
    painter.drawPixmap(20, 60, pix);



};

MainScene::~MainScene()
{
    delete ui;
}

