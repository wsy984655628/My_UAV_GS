#-------------------------------------------------
#
# Project created by QtCreator 2016-02-23T20:26:37
#
#-------------------------------------------------

QT       += core gui
QT       += webkitwidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += 3dcore 3drenderer 3dinput 3dquick qml quick

TARGET = My_UAV_GS
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    quickview.cpp

HEADERS  += mainwindow.h \
    quickview.h

FORMS    += mainwindow.ui

RESOURCES += \
    qml.qrc \
    assets.qrc \
    qmlimages.qrc \
    map.qrc
