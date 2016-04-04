#include "uastabbedmenuview.h"
#include "ui_uastabbedmenuview.h"
#include <QDebug>


UASTabbedMenuView::UASTabbedMenuView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UASTabbedMenuView)
{
    ui->setupUi(this);

    infoview = new UASTabbedInfoView(this);
    contral = new UASContral(this);
    parameter = new UASParameter(this);
    simu = new UASSimulation(this);

    ui->tabWidget->setTabPosition(QTabWidget::South);
    ui->tabWidget->addTab(infoview,"Info View");
    ui->tabWidget->addTab(contral,"Contral");
    ui->tabWidget->addTab(parameter,"Parameter Edit");
    ui->tabWidget->addTab(simu,"Simulation");
//    connect(this,SIGNAL(valueChanged(QString,float)),infoview,SLOT(receivevalueChanged(QString,float)));
}

UASTabbedMenuView::~UASTabbedMenuView()
{
    delete ui;
}

void UASTabbedMenuView::ReceivevalueChanged(const QString name, const float variant)
{
    emit valueChanged(name,variant);
//    qDebug()<< name << variant;
}
