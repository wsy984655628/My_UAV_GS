#include "uastabbedinfoview.h"
#include "ui_uastabbedinfoview.h"

UASTabbedInfoView::UASTabbedInfoView(QWidget *parent)
    :QWidget(parent),
        ui(new Ui::UASTabbedInfoView)
{
    ui->setupUi(this);
    quickView = new UASQuickView(this);
    compass = new UASCompass(this);


    ui->tabWidget->addTab(quickView,"Quick");
    ui->tabWidget->addTab(compass,"Compass");
}

UASTabbedInfoView::~UASTabbedInfoView()
{
    delete ui;
}
