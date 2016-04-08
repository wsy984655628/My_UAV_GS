#-------------------------------------------------
#
# Project created by QtCreator 2016-02-23T20:26:37
#
#-------------------------------------------------

QT       += core gui
QT       += webkitwidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets serialport
QT += 3dcore 3drenderer 3dinput 3dquick qml quick

DEFINES += QT_DLL QWT_DLL
LIBS += -L"C:\Qt\5.5\mingw492_32\lib" -lqwtd
LIBS += -L"C:\Qt\5.5\mingw492_32\lib" -lqwt
INCLUDEPATH += C:\Qt\5.5\mingw492_32\include\Qwt


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
    uassimulation.cpp \
    uasmeters.cpp \
    SerialCommunication/serialconsole.cpp \
    SerialCommunication/serialsettingdialog.cpp \
    my_gs.cpp \
    comm/linkmanager.cpp \
    comm/mavlinkprotocol.cpp \
    uas/uas.cpp \
    uas/uasmanager.cpp \
    gscore.cpp

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
    uassimulation.h \
    uasmeters.h \
    SerialCommunication/serialconsole.h \
    SerialCommunication/serialsettingdialog.h \
    my_gs.h \
    comm/gsmavlink.h \
    comm/linkmanager.h \
    comm/mavlinkprotocol.h \
    uas/uas.h \
    uas/uasinterface.h \
    uas/uasmanager.h \
    gscore.h

FORMS    += mainwindow.ui \
    uasquickview.ui \
    uastabbedinfoview.ui \
    uascompass.ui \
    uastabbedmenuview.ui \
    uascontral.ui \
    uasparameter.ui \
    uassimulation.ui \
    uasmeters.ui \
    SerialCommunication/serialsettingdialog.ui

RESOURCES += \
    qml.qrc \
    assets.qrc \
    qmlimages.qrc \
    map.qrc
