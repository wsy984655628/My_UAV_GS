#ifndef UASQUICKVIEW_H
#define UASQUICKVIEW_H

#include <QWidget>
#include <QMap>
#include <QVBoxLayout>
#include <QTimer>

#include <uasinterface.h>
#include <quickviewitem.h>

namespace Ui {
class UASQuickView;
}

class UASQuickView : public QWidget
{
    Q_OBJECT

public:
    explicit UASQuickView(QWidget *parent = 0);
    ~UASQuickView();
//    void addSource(MAVLinkDecoder *decoder);
private:
//    UASInterface *uas;

    QList<QString> uasEnabledPropertyList;
    QMap<QString,double> uasPropertyValueMap;
    QMap<QString,QuickViewItem*> uasPropertyToLabelMap;
    QTimer *updateTimer;

    int m_columnCount;

    QList<QVBoxLayout*> m_verticalLayoutList;
    void sortItems(int columncount);
    QList<int> m_verticalLayoutItemCount;
    int m_currentColumn;
    QMap<QString,int> m_PropertyToLayoutIndexMap;

protected:
    Ui::UASQuickView *ui;
//    void resizeEvent(QResizeEvent *evt);

public slots:
    void valueChanged(const QString& name, const QVariant& variant);
//    void actionTriggered(bool checked);
//    void actionTriggered();
    void updateTimerTick();
//    void selectDialogClosed();
    void valueEnabled(QString value);
//    void valueDisabled(QString value);
//    void columnActionTriggered();

private slots:
//    void _activeVehicleChanged(Vehicle* vehicle);
};

#endif // UASQUICKVIEW_H
