#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "SerialCommunication/serialsettingdialog.h"
#include "comm/linkmanager.h"
#include "uas/uasmanager.h"

class Settings: public QObject
{
    Q_OBJECT
    Q_PROPERTY(float Pitch READ Pitch WRITE setPitch NOTIFY PitchChanged)
    Q_PROPERTY(float Roll READ Roll WRITE setRoll NOTIFY RollChanged)
    Q_PROPERTY(float Yaw READ Yaw WRITE setYaw NOTIFY YawChanged)

public:
    explicit Settings(QObject* parent = Q_NULLPTR);
    float Pitch(void){return pitch;}
    float Roll(void) {return roll;}
    float Yaw(void) {return yaw;}

    void setPitch(float Pitch);
    void setRoll(float Roll);
    void setYaw(float Yaw);
signals:
    void PitchChanged(QString name,float variant);
    void RollChanged(QString name,float variant);
    void YawChanged(QString name,float variant);

public slots:
    void attitudeUpdate();

protected:
    float pitch;
    float roll;
    float yaw;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Settings *m_settings;


private slots:
    void on_rollScrollBar_sliderMoved(int position);

    void on_yawScrollBar_sliderMoved(int position);

    void on_pitchScrollBar_sliderMoved(int position);

    void systemCreated(UASInterface* uas);
    void attitudeChanged(UASInterface* uas, double roll, double pitch, double yaw, quint64 time);

private:
    Ui::MainWindow *ui;
    SerialSettingDialog *serial;
    QTimer* myTimer;


};

#endif // MAINWINDOW_H
