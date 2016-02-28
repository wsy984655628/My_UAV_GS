#include "quickviewtextitem.h"
#include <QVBoxLayout>
#include <QDebug>

QuickViewTextItem::QuickViewTextItem(QWidget *parent) : QuickViewItem(parent)
{
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->setSizeConstraint(QLayout::SetMinimumSize);

    titleLabel = new QLabel(this);
    titleLabel->setAlignment(Qt::AlignHCenter);
    titleLabel->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    titleLabel->setObjectName(QString::fromUtf8("title"));
    QFont titlefont = titleLabel->font();
    titlefont.setPixelSize(this->height() / 4.0);
    titleLabel->setFont(titlefont);
    layout->addWidget(titleLabel);

    valueLabel = new QLabel(this);
    valueLabel->setAlignment(Qt::AlignHCenter);
    valueLabel->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    valueLabel->setObjectName(QString::fromUtf8("value"));
    QFont valuefont = valueLabel->font();
    valuefont.setPixelSize(this->height() / 2.0);
    valueLabel->setFont(valuefont);
    layout->addWidget(valueLabel);

    layout->addSpacerItem(new QSpacerItem(10, 0 ,QSizePolicy::Minimum, QSizePolicy::Expanding));
    this->setLayout(layout);
}

void QuickViewTextItem::setValue(double value)
{
    if(value < 10 && value > -10)
    {
        valueLabel->setText(QString::number(value,'f',4));
    }
    else if (value < 100 && value > -100)
    {
        valueLabel->setText(QString::number(value,'f',3));
    }
    else if (value < 1000 && value > -1000)
    {
        valueLabel->setText(QString::number(value,'f',2));
    }
    else if (value < 10000 && value > -10000)
    {
        valueLabel->setText(QString::number(value,'f',1));
    }
    else
    {
        valueLabel->setText(QString::number(value,'f',0));
    }
}

void QuickViewTextItem::setTitle(QString title)
{
    if ((title.indexOf(".")) != -1 && title.indexOf(":") != -1)
    {
        titleLabel->setText(title.mid(title.indexOf(".") + 1));
    }
    else
    {
        titleLabel->setText(title);
    }
}

int QuickViewTextItem::minValuePixelSize()
{
    QFont valuefont = valueLabel->font();
    QFont titlefont = titleLabel->font();
    valuefont.setPixelSize(this->height());
    titlefont.setPixelSize(valuefont.pixelSize() * 0.75);

//    QFontMetrics metrics(valuefont);
    return valuefont.pixelSize();
}

void QuickViewTextItem::setValuePixelSize(int size)
{
    QFont valuefont = valueLabel->font();
    QFont titlefont = titleLabel->font();
    valuefont.setPixelSize(size);
    titlefont.setPixelSize(valuefont.pixelSize() * 0.75);
    valueLabel->setFont(valuefont);
    titleLabel->setFont(titlefont);
    update();
}
