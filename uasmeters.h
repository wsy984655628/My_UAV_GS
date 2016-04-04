#ifndef UASMETERS_H
#define UASMETERS_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QMap>
#include <qwt_compass.h>
#include <qwt_dial.h>
#include <qwt_dial_needle.h>


namespace Ui {
class UASMeters;
}

class UASMeters : public QWidget
{
    Q_OBJECT

public:
    explicit UASMeters(QWidget *parent = 0);
    ~UASMeters();
    void creatDial(QString str);
    void creatCompass(QString str);

private:
    Ui::UASMeters *ui;

    QTimer* updateTimer;

    QMap<QString, double>    uasPropertyValueMap;
    QMap<QString, QwtDial*>  uasPropertyToDialMap;
    QMap<QString, QwtCompass*> uasPropertyToComMap;
    int uasPropertyCount;

private slots:
    void valueChanged(const QString name, const float variant);
    void updateTimerTick();

};

#endif // UASMETERS_H
