#ifndef UASCONTRAL_H
#define UASCONTRAL_H

#include <QWidget>

namespace Ui {
class UASContral;
}

class UASContral : public QWidget
{
    Q_OBJECT

public:
    explicit UASContral(QWidget *parent = 0);
    ~UASContral();

private:
    Ui::UASContral *ui;
};

#endif // UASCONTRAL_H
