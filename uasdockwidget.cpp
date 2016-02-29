#include "uasdockwidget.h"

#include <QCloseEvent>
#include <QSettings>

const char*  UASDockWidget::_settingsGroup = "DockWidgets";

UASDockWidget::UASDockWidget(const QString& title, QAction* action, QWidget* parent)
    : QWidget(parent)
    ,_title(title)
    ,_action(action)
{
    if (action){
        setWindowTitle(title);
        setWindowFlags(Qt::Tool);

        loadSettings();
    }
}

void UASDockWidget::closeEvent(QCloseEvent *event)
{
    if(_action) {
        saveSettings();
        event->ignore();
        _action->trigger();
    }
}

void UASDockWidget::loadSettings(void)
{
    if(_action){
        QSettings settings;

        settings.beginGroup(_settingsGroup);
        if (settings.contains(_title)){
            restoreGeometry(settings.value(_title).toByteArray());
        }
    }
}

void UASDockWidget::saveSettings(void)
{
    if(_action)
    {
        QSettings settings;

        settings.beginGroup(_settingsGroup);
        settings.setValue(_title, saveGeometry());
    }
}
