#ifndef UASTABBEDINFOVIEW_H
#define UASTABBEDINFOVIEW_H

#include <QWidget>
#include <uasdockwidget.h>
#include <uasquickview.h>

namespace Ui {
class UASTabbedInfoView;
}

class UASTabbedInfoView : public UASDockWidget
{
    Q_OBJECT

public:
    explicit UASTabbedInfoView(const QString& title,QAction* action ,QWidget *parent = 0);
    ~UASTabbedInfoView();

private:
    Ui::UASTabbedInfoView *ui;
    UASQuickView *quickView;
};

#endif // UASTABBEDINFOVIEW_H
