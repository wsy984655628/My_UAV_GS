#include "uastabbedinfoview.h"
#include "ui_uastabbedinfoview.h"

UASTabbedInfoView::UASTabbedInfoView(const QString& title,QAction* action ,QWidget *parent)
    : UASDockWidget(title, action, parent),
        ui(new Ui::UASTabbedInfoView)
{
    ui->setupUi(this);
    quickView = new UASQuickView(this);
    ui->tabWidget->addTab(quickView,"Quick");
    loadSettings();
}

UASTabbedInfoView::~UASTabbedInfoView()
{
    delete ui;
}
