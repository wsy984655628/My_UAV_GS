#include "uascompass.h"
#include "ui_uascompass.h"

UASCompass::UASCompass(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UASCompass)
{
    ui->setupUi(this);
}

UASCompass::~UASCompass()
{
    delete ui;
}
