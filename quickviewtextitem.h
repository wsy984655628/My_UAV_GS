#ifndef QUICKVIEWTEXTITEM_H
#define QUICKVIEWTEXTITEM_H

#include "quickviewitem.h"
#include <QLabel>
#include <QSpacerItem>

class QuickViewTextItem : public QuickViewItem
{
public:
    QuickViewTextItem(QWidget *parent=0);
    void setValue(double value);
    void setTitle(QString title);
    int minValuePixelSize();
    void setValuePixelSize(int size);
protected:
//    void resizeEvent(QResizeEvent *event);
private:
    QLabel *titleLabel;
    QLabel *valueLabel;
};

#endif // QUICKVIEWTEXTITEM_H
