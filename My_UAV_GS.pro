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
    quickviewitem.cpp \
    uasquickview.cpp \
    quickviewtextitem.cpp \
    uastabbedinfoview.cpp \
    uascompass.cpp \
    uastabbedmenuview.cpp \
    uascontral.cpp \
    uasparameter.cpp \
    uassimulation.cpp

HEADERS  += mainwindow.h \
    uasinterface.h \
    quickviewitem.h \
    uasquickview.h \
    quickviewtextitem.h \
    uastabbedinfoview.h \
    uascompass.h \
    uastabbedmenuview.h \
    uascontral.h \
    uasparameter.h \
    uassimulation.h

FORMS    += mainwindow.ui \
    uasquickview.ui \
    uastabbedinfoview.ui \
    uascompass.ui \
    uastabbedmenuview.ui \
    uascontral.ui \
    uasparameter.ui \
    uassimulation.ui

RESOURCES += \
    qml.qrc \
    assets.qrc \
    qmlimages.qrc \
    map.qrc
