#include "PlayScene.h"

#include <QDebug>
#include <QPainter>
#include <QMenuBar>
#include "MyPushButton.h"
#include <QTimer>
#include <QLabel>
#include "MyCoin.h"
#include "dataconfig.h"
#include <QPropertyAnimation>
#include <QSound>
#include <iostream>
//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}

PlayScene::PlayScene(int levelNum){
    QString str = QString("level %1 selected").arg(levelNum);
    qDebug() << str;
    this->levelIndex = levelNum;
    this->setFixedSize(320*2, 588*2);
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    this->setWindowTitle("Play Scene");


    QMenuBar* bar = menuBar();
    //QMenuBar* bar = new QMenuBar;
    bar->setParent(this);
    QMenu* startMenu = bar->addMenu("开始");
    QAction* quitAction = startMenu->addAction("退出");
    connect(quitAction, &QAction::triggered, [=](){
        this->close();
    });


    MyPushButton* backBtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    //backBtn->resize(QSize(backBtn->width()*5, backBtn->height()*5));

    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(), this->height()-backBtn->height());

    //mainScene = new MainScene;

    QSound* backSound = new QSound(":/res/BackButtonSound.wav");
    QSound* winSound = new QSound(":/res/LevelWinSound.wav");
    QSound* flipSound = new QSound(":/res/ConFlipSound.wav");

    connect(backBtn, &MyPushButton::clicked, [=](){
        //mainScene->show();
//        QTimer::singleShot(200, this, [=](){
//            emit this->chooseSceneBack();
//            this->hide();
//        });
        //qDebug() << "clicked";
        backSound->play();
        QTimer::singleShot(200, this, [=](){
            qDebug() << "clicked";
            emit this->chooseSceneBack();
            //this->hide();   为什么这个hide出来会报错而ChooseLevelScene返回不会。

        });
    });



    QLabel* label = new QLabel;
    label->setParent(this);

    QFont font;
    font.setFamily("Times New Roman");
    font.setPointSize(20);
    label->setFont(font);
    QString str1 = QString("Level: %1").arg(this->levelIndex);
    qDebug() << str1;
    label->setText(str1);
    label->setGeometry(30, this->height()-50, 240, 50);

    dataConfig cfig;
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            this->gameArray[i][j] = cfig.mData[levelNum][i][j];
        }
    }

    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            QLabel *label = new QLabel;
            label->setGeometry(0,0, 100, 100);
            QPixmap pmp = QPixmap(":/res/BoardNode(1).png");
            pmp = pmp.scaled(pmp.width()*2, pmp.height()*2);
            label->setPixmap(pmp);
            label->setParent(this);

            label->move(57*2+100*i, 200*2+j*100);

            QString str;
            if(gameArray[i][j]==1){
                str = ":/res/Coin0001.png";
            }
            else{
                str = ":/res/Coin0008.png";
            }
            MyCoin* coin = new MyCoin(str);
            coin->setParent(this);
            coin->move(59*2+100*i, 204*2+j*100);
            //coin->show();
            coin->posX = i;
            coin->posY = j;
            coin->flag = this->gameArray[i][j];

            this->coinBtn[i][j] = coin;

            QLabel* winLabel = new QLabel;
            QPixmap winPix;
            winPix.load(":/res/LevelCompletedDialogBg.png");
            winPix = winPix.scaled(winPix.width()*2, winPix.height()*2);
            winLabel->setGeometry(0, 0, winPix.width(), winPix.height());
            winLabel->setPixmap(winPix);
            winLabel->setParent(this);
            winLabel->move((this->width()-winPix.width())*0.5, -winPix.height());

            connect(coin, &MyCoin::clicked, [=](){

                flipSound->play();
                coin->changeFlag();
                this->gameArray[i][j] = !this->gameArray[i][j];

                //btn banned while one coin clip;
                for(int i=0; i<4; i++){
                    for(int j=0; j<4; j++){
                        this->coinBtn[i][j]->isWin = 1;
                    }
                }

                QTimer::singleShot(300, this, [=](){
                    if(coin->posX+1<=3)
                    {
                        coinBtn[coin->posX+1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX+1][coin->posY] = !this->gameArray[coin->posX+1][coin->posY];
                    }
                    if(coin->posX-1>=0)
                    {
                        coinBtn[coin->posX-1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX-1][coin->posY] = !this->gameArray[coin->posX-1][coin->posY];
                    }
                    if(coin->posY+1<=3)
                    {
                        coinBtn[coin->posX][coin->posY+1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY+1] = !this->gameArray[coin->posX][coin->posY+1];
                    }
                    if(coin->posY-1>=0)
                    {
                        coinBtn[coin->posX][coin->posY-1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY-1] = !this->gameArray[coin->posX][coin->posY-1];
                    }
                    for(int i=0; i<4; i++){
                        for(int j=0; j<4; j++){
                            this->coinBtn[i][j]->isWin = 0;
                        }
                    }

                    this->isWin = true;
                    for(int i=0; i<4; ++i){
                        for(int j=0; j<4; j++){
                            if(this->gameArray[i][j]==1) continue;
                            else{
                                isWin = false;
                                break;
                            }
                        }
                    }
//                    for(int i=0; i<4; ++i){
//                        for(int j=0; j<4; j++){
//                            std::cout << this->gameArray[i][j] << ' ';
//                        }
//                        std::cout << std::endl;
//                    }
//                    qDebug() << isWin << "-------";
                    if(isWin==false){
                        ;
                    }else{
                        qDebug() << "Succeed";
                        for(int i=0; i<4; ++i){
                            for(int j=0; j<4; ++j){
                                coinBtn[i][j]->isWin = true;
                            }
                        }

                        QTimer::singleShot(1000, this, [=](){
                            winSound->play();
                            QPropertyAnimation* animation = new QPropertyAnimation(winLabel, "geometry");
                            animation->setDuration(1000);
                            animation->setStartValue(QRect(winLabel->x(), winLabel->y(), winLabel->width(), winLabel->height()));
                            animation->setEndValue(QRect(winLabel->x(), winLabel->y()+114*2, winLabel->width(), winLabel->height()));
                            animation->setEasingCurve(QEasingCurve::OutBounce);
                            animation->start();
                        });
                    }
                });



            });

        }
    }



};

void PlayScene::paintEvent(QPaintEvent* e){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width()*2)*0.5, 60, pix.width(), pix.height(), pix);
};
