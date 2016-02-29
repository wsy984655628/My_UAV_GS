#ifndef UASTABBEDINFOVIEW_H
#define UASTABBEDINFOVIEW_H

#include <QWidget>
#include <uasquickview.h>
#include <uascompass.h>

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
    UASCompass *compass;
};

#endif // UASTABBEDINFOVIEW_H
