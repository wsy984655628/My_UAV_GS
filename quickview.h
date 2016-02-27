#ifndef QUICKVIEW_H
#define QUICKVIEW_H

#include <QWidget>
//#include <QList>


class QuickView : public QWidget
{
    Q_OBJECT
public:
    explicit QuickView(QWidget *parent = 0);
    ~QuickView();
//    void addSource(MAVLinkDecoder *decoder);
private:
    Interface *uas;

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
    Ui::Form ui;
    void resizeEvent(QResizeEvent *evt);

public slots:
    void valueChanged(const int uasid, const QString& name, const QString& unit, const QVariant& value,const quint64 msecs);
    void actionTriggered(bool checked);
    void actionTriggered();
    void updateTimerTick();
    void selectDialogClosed();
    void valueEnabled(QString value);
    void valueDisabled(QString value);
    void columnActionTriggered();

private slots:
    void _activeVehicleChanged(Vehicle* vehicle);

signals:

public slots:
};

#endif // QUICKVIEW_H
