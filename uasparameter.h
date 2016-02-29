#ifndef UASPARAMETER_H
#define UASPARAMETER_H

#include <QWidget>

namespace Ui {
class UASParameter;
}

class UASParameter : public QWidget
{
    Q_OBJECT

public:
    explicit UASParameter(QWidget *parent = 0);
    ~UASParameter();

private:
    Ui::UASParameter *ui;
};

#endif // UASPARAMETER_H
