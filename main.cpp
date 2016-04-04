#include "mainwindow.h"
#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include "uasquickview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

//    UASQuickView u;
//    u.show();


    return a.exec();
}
