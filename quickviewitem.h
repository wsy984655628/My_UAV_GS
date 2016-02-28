#ifndef QUICKVIEWITEM_H
#define QUICKVIEWITEM_H

#include <QWidget>

class QuickViewItem : public QWidget
{
    Q_OBJECT
public:
    explicit QuickViewItem(QWidget *parent = 0);
    virtual void setValue(double value) = 0;
    virtual void setTitle(QString title) = 0;
    virtual int minValuePixelSize() = 0;
    virtual void setValuePixelSize(int size) = 0;

signals:

public slots:
};

#endif // QUICKVIEWITEM_H
