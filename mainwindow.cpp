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
    emit PitchChanged();
}

void Settings::setRoll(float Roll)
{
    if(roll == Roll) return;
    roll = Roll;
    emit RollChanged();
}

void Settings::setYaw(float Yaw)
{
    if(yaw == Yaw) return;
    yaw = Yaw;
    emit YawChanged();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
    indicator_container->setFixedSize(300,300);
    QWidget *view3D_container = QWidget::createWindowContainer(view3D);
    view3D_container->setFixedSize(300,300);

    QUrl url("qrc:/map/map.html");
    ui->webView->setUrl(url);

    QHBoxLayout* mainLayout = qobject_cast<QHBoxLayout*>( ui->centralwidget->layout( ) );
    QVBoxLayout* LeftLayout = new QVBoxLayout;
    QHBoxLayout* ViewLayout = new QHBoxLayout;

//    QWidget* UAS_InfoView = new UASTabbedInfoView(this);
//    QWidget* UAS_InfoView = new UASQuickView(this);

    QWidget* test = new UASTabbedMenuView(this);

    ViewLayout->addWidget(view3D_container);
    ViewLayout->addWidget(indicator_container);
    LeftLayout->addLayout(ViewLayout);
    mainLayout->addLayout(LeftLayout);
    mainLayout->addWidget(ui->webView);
//    LeftLayout->addWidget(UAS_InfoView);
    LeftLayout->addWidget(test);
    LeftLayout->addWidget(ui->pitchScrollBar);
    LeftLayout->addWidget(ui->rollScrollBar);
    LeftLayout->addWidget(ui->yawScrollBar);
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
