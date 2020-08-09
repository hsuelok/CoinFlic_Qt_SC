#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

//#include <QWidget>
#include <QMainWindow>
#include "PlayScene.h"

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QMainWindow *parent = nullptr);


    void paintEvent(QPaintEvent* );
    //MainScene* mainScene = NULL;

    //
    PlayScene* play = NULL;

signals:
    //发送给主界面，点击返回
    void chooseSceneBack();

};

#endif // CHOOSELEVELSCENE_H
