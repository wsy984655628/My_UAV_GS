#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Settings: public QObject
{
    Q_OBJECT
    Q_PROPERTY(float Pitch READ Pitch WRITE setPitch NOTIFY PitchChanged)

public:
    explicit Settings(QObject* parent = Q_NULLPTR);
    float Pitch(void){return pitch;}
    void setPitch(float Pitch);
signals:
    void PitchChanged(void);
protected:
    float pitch;
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
    void on_horizontalScrollBar_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
    Settings m_settings;
};

#endif // MAINWINDOW_H
