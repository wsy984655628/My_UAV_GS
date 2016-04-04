#include "uastabbedinfoview.h"
#include "ui_uastabbedinfoview.h"
#include "mainwindow.h"
#include <QDebug>

UASTabbedInfoView::UASTabbedInfoView(QWidget *parent)
    :QWidget(parent),
        ui(new Ui::UASTabbedInfoView)
{
    ui->setupUi(this);
    quickView = new UASQuickView(this);
    meters = new UASMeters(this);

    ui->tabWidget->addTab(quickView,"Quick");
    ui->tabWidget->addTab(meters,"Meters");

//    connect(this,SIGNAL(valueChanged(QString,float)),quickView,SLOT(valueChanged(QString,float)));
//    connect(this,SIGNAL(valueChanged(QString,float)),meters,SLOT(valueChanged(QString,float)));
}

UASTabbedInfoView::~UASTabbedInfoView()
{
    delete ui;
}

void UASTabbedInfoView::receivevalueChanged(const QString name, const float variant)
{
    emit valueChanged(name,variant);
//    qDebug() << name << variant;
}
