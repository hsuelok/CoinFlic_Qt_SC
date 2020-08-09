#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include "ChooseLevelScene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainScene; }
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();

    //重写paintEvent
    void paintEvent(QPaintEvent* e);

    ChooseLevelScene* chooseScene = NULL;

    //ChooseLevelScene * chooseScene = NULL;

private:
    Ui::MainScene *ui;
};
#endif // MAINSCENE_H
