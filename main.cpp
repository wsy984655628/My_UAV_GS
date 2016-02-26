#include "mainwindow.h"
#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setBaseSize(1000,600);
//    w.setFixedSize(1200,600);
    w.show();

    return a.exec();
}
