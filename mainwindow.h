#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void PitchChanged(void);
    void RollChanged(void);
    void YawChanged(void);
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


private slots:
    void on_rollScrollBar_sliderMoved(int position);

    void on_yawScrollBar_sliderMoved(int position);

    void on_pitchScrollBar_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
    Settings *m_settings;
};

#endif // MAINWINDOW_H
