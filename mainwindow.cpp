#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "uasquickview.h"
#include "uastabbedinfoview.h"
#include "uastabbedmenuview.h"

#include <QQmlAspectEngine>
#include <QRenderAspect>
#include <QInputAspect>
#include <QQmlContext>
#include <QWindow>
#include <QScreen>
#include <QString>
#include <QOpenGLContext>

#include <QQmlApplicationEngine>
#include <QQuickView>

#include <QGridLayout>

class View3D: public QWindow
{
public:
    View3D(QScreen* targetScreen = Q_NULLPTR):QWindow(targetScreen)
    {
        setSurfaceType(QSurface::OpenGLSurface);
        QSurfaceFormat format;
        if (QOpenGLContext::openGLModuleType() == QOpenGLContext::LibGL) {
            format.setVersion(4, 3);
            format.setProfile(QSurfaceFormat::CoreProfile);
        }
        format.setDepthBufferSize( 24 );
        format.setSamples( 4 );
        format.setStencilBufferSize(8);
        setFormat(format);
        create();
    }
};

Settings::Settings(QObject *parent):QObject(parent)
{
    pitch = 0.0;
    roll  = 0.0;
    yaw   = 0.0;
}
void Settings::setPitch(float Pitch)
{
    if(pitch == Pitch) return;
    pitch = Pitch;
//    emit PitchChanged("Pitch", pitch);
}

void Settings::setRoll(float Roll)
{
    if(roll == Roll) return;
    roll = Roll;
//    emit RollChanged("Roll",roll);
}

void Settings::setYaw(float Yaw)
{
    if(yaw == Yaw) return;
    yaw = Yaw;
//    emit YawChanged("Yaw",yaw);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->resize(1000,700);

    SerialSettingDialog::instance();
    connect(ui->actionConfigure_SerialPort, SIGNAL(triggered(bool)), SerialSettingDialog::instance(), SLOT(show()));
    connect(ui->actionEXIT,SIGNAL(triggered(bool)),this,SLOT(close()));

//    QList<QAction*> actions;
//    actions << ui->actionFLY;
//    actions << ui->actionSimulation;
//    QToolBar * toolBar = new QToolBar(this);
//    this->addToolBar(toolBar);
//    toolBar->setper

    using namespace Qt3D;
    using namespace Qt3D::Quick;

    View3D* view3D = new View3D;
    m_settings = new Settings(this);
    //View3D view3D;
    QQmlAspectEngine* engine = new QQmlAspectEngine(this);
    engine->aspectEngine()->registerAspect(new QRenderAspect);
    engine->aspectEngine()->registerAspect(new QInputAspect);

    QVariantMap data;
    data.insert(QStringLiteral("surface"),
                QVariant::fromValue(static_cast<QSurface*>(view3D)));
    data.insert(QStringLiteral("eventSource"),
                QVariant::fromValue(view3D));
    engine->aspectEngine()->setData(data);

    engine->qmlEngine()->rootContext()->setContextProperty("_settings",m_settings);
    engine->aspectEngine()->initialize();
    engine->setSource(QUrl("qrc:/qml/main.qml"));

    QQuickView *indicator = new QQuickView();
    indicator->rootContext()->setContextProperty("_settings",m_settings);
    indicator->setSource(QUrl("qrc:/qml/FlightDisplayView.qml"));

    QWidget *indicator_container = QWidget::createWindowContainer(indicator);
    indicator_container->setMinimumWidth(150);
    QWidget *view3D_container = QWidget::createWindowContainer(view3D);
    view3D_container->setMinimumWidth(150);

    QUrl url("qrc:/map/map.html");
    ui->webView->setUrl(url);

    QWidget* UAS_MenuView = new UASTabbedMenuView(this);

    ui->viewLayout->addWidget(view3D_container);
    ui->viewLayout->addWidget(indicator_container);
    ui->LeftLayout->addWidget(UAS_MenuView,5);
    ui->LeftLayout->addWidget(ui->pitchScrollBar);
    ui->LeftLayout->addWidget(ui->rollScrollBar);
    ui->LeftLayout->addWidget(ui->yawScrollBar);

    connect(m_settings,SIGNAL(PitchChanged(QString,float)),UAS_MenuView,SLOT(ReceivevalueChanged(QString,float)));
    connect(m_settings,SIGNAL(RollChanged(QString,float)),UAS_MenuView,SLOT(ReceivevalueChanged(QString,float)));
    connect(m_settings,SIGNAL(YawChanged(QString,float)),UAS_MenuView,SLOT(ReceivevalueChanged(QString,float)));

    LinkManager::instance();
    UASManager::instance();
    connect(UASManager::instance(), SIGNAL(UASCreated(UASInterface*)),
            this, SLOT(systemCreated(UASInterface*)));

    myTimer = new QTimer(this);
    myTimer->start(100);
    connect(myTimer, SIGNAL(timeout()), m_settings, SLOT(attitudeUpdate()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_rollScrollBar_sliderMoved(int position)
{
    m_settings->setRoll(position);
}

void MainWindow::on_yawScrollBar_sliderMoved(int position)
{
    m_settings->setYaw(position);
}

void MainWindow::on_pitchScrollBar_sliderMoved(int position)
{
    m_settings->setPitch(position);
}

void MainWindow::systemCreated(UASInterface *uas)
{
    connect(uas, SIGNAL(attitudeChanged(UASInterface*,double,double,double,quint64)),
            this, SLOT(attitudeChanged(UASInterface*,double,double,double,quint64)));
    uas->enableExtra1Transmission(10);
}

void MainWindow::attitudeChanged(UASInterface *uas, double roll, double pitch, double yaw, quint64 time)
{
    m_settings->setRoll(roll * 180/3.14);
    m_settings->setYaw(yaw * 180/3.14);
    m_settings->setPitch(pitch * 180/3.14);
//    qDebug() << pitch;
}

void Settings::attitudeUpdate()
{
    emit PitchChanged("Pitch", pitch);

    emit YawChanged("Yaw",yaw);
    emit RollChanged("Roll",roll);
}
