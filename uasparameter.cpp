#include "uasparameter.h"
#include "ui_uasparameter.h"

UASParameter::UASParameter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UASParameter)
{
    ui->setupUi(this);
}

UASParameter::~UASParameter()
{
    delete ui;
}
