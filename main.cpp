#include "mainwindow.h"
#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include "uasquickview.h"
#include "uasmeters.h"
#include "uastabbedinfoview.h"

#include "gscore.h"

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();


//    return a.exec();
    GSCore core(argc,argv);
    return core.exec();
}
