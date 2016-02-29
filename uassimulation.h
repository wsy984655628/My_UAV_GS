#ifndef UASSIMULATION_H
#define UASSIMULATION_H

#include <QWidget>

namespace Ui {
class UASSimulation;
}

class UASSimulation : public QWidget
{
    Q_OBJECT

public:
    explicit UASSimulation(QWidget *parent = 0);
    ~UASSimulation();

private:
    Ui::UASSimulation *ui;
};

#endif // UASSIMULATION_H
