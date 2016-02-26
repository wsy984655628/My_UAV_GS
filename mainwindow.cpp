#include "mainwindow.h"
#include "ui_mainwindow.h"
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
}
void Settings::setPitch(float Pitch)
{
    if(pitch == Pitch) return;
    pitch = Pitch;
    emit PitchChanged();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    using namespace Qt3D;
    using namespace Qt3D::Quick;

    View3D* view3D = new View3D;
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

    engine->qmlEngine()->rootContext()->setContextProperty("_settings",&m_settings);

    engine->aspectEngine()->initialize();
    engine->setSource(QUrl("qrc:/qml/main.qml"));

//    QVBoxLayout* l = qobject_cast<QVBoxLayout*>( ui->centralwidget->layout( ) );
//    l->insertWidget(1,QWidget::createWindowContainer(view3D));

//    QQuickView *view = new QQuickView();
//    view->setSource(QUrl("qrc:/qml/FlightDisplayView.qml"));
//    l->insertWidget(0,QWidget::createWindowContainer(view));

    QQuickView *indicator = new QQuickView();
    indicator->setSource(QUrl("qrc:/qml/FlightDisplayView.qml"));

    QWidget *indicator_container = QWidget::createWindowContainer(indicator);
    indicator_container->setFixedSize(300,300);
    QWidget *view3D_container = QWidget::createWindowContainer(view3D);
    view3D_container->setFixedSize(300,300);

    QUrl url("qrc:/map/map.html");
    ui->webView->setUrl(url);
//    QGridLayout* mainLayout = qobject_cast<QGridLayout*>( ui->centralwidget->layout( ) );
//    mainLayout->addWidget(indicator_container,0,1);
//    mainLayout->addWidget(view3D_container,0,0);
//    mainLayout->addWidget(ui->webView,0,2);
    QHBoxLayout* mainLayout = qobject_cast<QHBoxLayout*>( ui->centralwidget->layout( ) );
    QVBoxLayout* LeftLayout = new QVBoxLayout;
    QHBoxLayout* ViewLayout = new QHBoxLayout;
    QGridLayout* groupLayout = new QGridLayout;

    ViewLayout->addWidget(view3D_container);
    ViewLayout->addWidget(indicator_container);
    LeftLayout->addLayout(ViewLayout);
    LeftLayout->addWidget(ui->groupBox);
    mainLayout->addLayout(LeftLayout);
    mainLayout->addWidget(ui->webView);

    groupLayout->addWidget(ui->horizontalScrollBar);
    ui->groupBox->setLayout(groupLayout);
    


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalScrollBar_sliderMoved(int position)
{
    m_settings.setPitch(position);
}
