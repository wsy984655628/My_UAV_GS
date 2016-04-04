#ifndef UASTABBEDINFOVIEW_H
#define UASTABBEDINFOVIEW_H

#include <QWidget>
#include <uasquickview.h>
#include <uascompass.h>
#include "uasmeters.h"

namespace Ui {
class UASTabbedInfoView;
}

class UASTabbedInfoView : public QWidget
{
    Q_OBJECT

public:
    explicit UASTabbedInfoView(QWidget *parent = 0);
    ~UASTabbedInfoView();

private:
    Ui::UASTabbedInfoView *ui;
    UASQuickView *quickView;
    UASMeters *meters;
public slots:
    void receivevalueChanged(const QString name, const float variant);
signals:
    void valueChanged(QString name,float variant);
};

#endif // UASTABBEDINFOVIEW_H
