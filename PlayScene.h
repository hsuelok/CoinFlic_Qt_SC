#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "MyCoin.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int levelNum);

    int levelIndex;
    int gameArray[4][4];  //for the face of the coin;
    MyCoin* coinBtn[4][4];

    bool isWin;


    void paintEvent(QPaintEvent* e);
signals:
    void chooseSceneBack();
};

#endif // PLAYSCENE_H
