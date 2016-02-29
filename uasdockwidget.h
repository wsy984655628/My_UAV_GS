#ifndef UASDOCKWIDGET_H
#define UASDOCKWIDGET_H

#include <QWidget>
#include <QDockWidget>
#include <QAction>

class UASDockWidget : public QWidget
{
    Q_OBJECT

public:
    UASDockWidget(const QString& title, QAction* action, QWidget* parent = 0);

    void loadSettings(void);
    void saveSettings(void);

    void closeEvent(QCloseEvent * event);

protected:
    QString             _title;
    QAction*            _action;
    static const char*  _settingsGroup;
};

#endif // UASDOCKWIDGET_H
