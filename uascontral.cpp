#include "uascontral.h"
#include "ui_uascontral.h"

UASContral::UASContral(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UASContral)
{
    ui->setupUi(this);
}

UASContral::~UASContral()
{
    delete ui;
}
