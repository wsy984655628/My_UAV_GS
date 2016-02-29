#include "uassimulation.h"
#include "ui_uassimulation.h"

UASSimulation::UASSimulation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UASSimulation)
{
    ui->setupUi(this);
}

UASSimulation::~UASSimulation()
{
    delete ui;
}
