//bug:
//1.空格键未禁用。






#include "MainScene.h"

#include <QApplication>
#include <QDebug>
#include "dataconfig.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainScene w;
    w.show();

//    dataConfig cfig;
//    for(int i=0; i<4; i++){
//        for(int j=0; j<4; j++){
//            qDebug() << cfig.mData[1][i][j];
//        }
//        qDebug() << "";
//    }

    return a.exec();
}
