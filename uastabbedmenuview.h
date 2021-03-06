#ifndef UASTABBEDMENUVIEW_H
#define UASTABBEDMENUVIEW_H

#include <QWidget>
#include "uastabbedinfoview.h"
#include "uascontral.h"
#include "uasparameter.h"
#include "uassimulation.h"

namespace Ui {
class UASTabbedMenuView;
}

class UASTabbedMenuView : public QWidget
{
    Q_OBJECT

public:
    explicit UASTabbedMenuView(QWidget *parent = 0);
    ~UASTabbedMenuView();

private:
    Ui::UASTabbedMenuView *ui;
    UASTabbedInfoView *infoview;
    UASContral *contral;
    UASParameter *parameter;
    UASSimulation *simu;

public slots:
     void ReceivevalueChanged(const QString name, const float variant);
signals:
     void valueChanged(QString name, float variant);
};

#endif // UASTABBEDMENUVIEW_H
