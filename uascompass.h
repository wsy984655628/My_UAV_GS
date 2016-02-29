#ifndef UASCOMPASS_H
#define UASCOMPASS_H

#include <QWidget>

namespace Ui {
class UASCompass;
}

class UASCompass : public QWidget
{
    Q_OBJECT

public:
    explicit UASCompass(QWidget *parent = 0);
    ~UASCompass();

private:
    Ui::UASCompass *ui;
};

#endif // UASCOMPASS_H
