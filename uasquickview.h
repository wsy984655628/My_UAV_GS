#ifndef UASQUICKVIEW_H
#define UASQUICKVIEW_H

#include <QWidget>
#include <QMap>
#include <QVBoxLayout>
#include <QTimer>

#include <uasinterface.h>
#include <quickviewitem.h>
#include <mainwindow.h>

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

    UASInterface * uas;

protected:
    Ui::UASQuickView *ui;

public slots:
    void valueChanged(const QString name, const float variant);
    void updateTimerTick();
    void valueEnabled(QString value);

    void addUAS(UASInterface* uas);
    void attitudeChanged(UASInterface* uas, double roll, double pitch, double yaw, quint64 time);

};

#endif // UASQUICKVIEW_H
