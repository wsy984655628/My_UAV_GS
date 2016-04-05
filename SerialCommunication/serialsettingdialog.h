#ifndef SERIALSETTINGDIALOG_H
#define SERIALSETTINGDIALOG_H

#include <QDialog>
#include <QtSerialPort/QSerialPort>
#include "serialconsole.h"

namespace Ui {
class SerialSettingDialog;
}

class QIntValidator;

class SerialSettingDialog : public QDialog
{
    Q_OBJECT

public:
    struct Settings {
        QString name;
        qint32 baudRate;
        QString stringBaudRate;
        QSerialPort::DataBits dataBits;
        QString stringDataBits;
        QSerialPort::Parity parity;
        QString stringParity;
        QSerialPort::StopBits stopBits;
        QString stringStopBits;
        QSerialPort::FlowControl flowControl;
        QString stringFlowControl;
    };

    explicit SerialSettingDialog(QWidget *parent = 0);
    static SerialSettingDialog* instance();
    ~SerialSettingDialog();

    Settings settings() const;
    QSerialPort* getSerial();

private slots:
    void showPortInfo(int idx);
    void apply();
    void checkCustomBaudRatePolicy(int idx);
    void checkCustomDevicePathPolicy(int idx);
// handle serial port
    void writeData(const QByteArray &data);
    void readData();
    void handleError(QSerialPort::SerialPortError error);

    void SendData(const char *data, qint64 len);

public slots:
    void openSerial();
    void closeSerial();

signals:
    bytesReceived(QByteArray data);

private:
    void fillPortsParameters();
    void fillPortsInfo();
    void updateSettings();
    void initConnections();

private:
    Ui::SerialSettingDialog *ui;
    Settings currentSettings;
    QIntValidator *intValidator;

//handle serial port
    QSerialPort *serial;
    SerialConsole *console;

};

#endif // SERIALSETTINGDIALOG_H
