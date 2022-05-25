#include "mainwindow.h"
#include <QApplication>
#include<QDebug>
#include"host.h"
#include"dialog9.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Dialog9 D;
    D.show();

    return a.exec();
}
