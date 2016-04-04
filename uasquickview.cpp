#include "uasquickview.h"
#include "quickviewtextitem.h"
#include "ui_uasquickview.h"
#include "mainwindow.h"

#include <QGroupBox>
#include <QDebug>

UASQuickView::UASQuickView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UASQuickView)
{
    m_columnCount = 2;
    m_currentColumn = 0;
    ui->setupUi(this);

    ui->horizontalLayout->setMargin(0);
    m_verticalLayoutList.append(new QVBoxLayout());
    ui->horizontalLayout->addLayout(m_verticalLayoutList[0]);

    QGroupBox* group = new QGroupBox(this);
    QGridLayout* grid = new QGridLayout(this);

    group->setLayout(ui->horizontalLayout);
    grid->addWidget(group,0,0);

    if (uasPropertyValueMap.size() == 0)
    {
        valueEnabled("Roll");
        valueEnabled("Pitch");
        valueEnabled("Yaw");
        valueEnabled("Height");
        valueEnabled("distToWaypoint");
        valueEnabled("groundSpeed");
    }
    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &UASQuickView::updateTimerTick);
    updateTimer->start(100);

    connect(UASManager::instance(), SIGNAL(UASCreated(UASInterface*)), this, SLOT(addUAS(UASInterface*)));

}

UASQuickView::~UASQuickView()
{
    delete ui;
}

void UASQuickView::valueEnabled(QString value)
{
    QuickViewItem *item = new QuickViewTextItem(this);
    item->setTitle(value);
    m_verticalLayoutList[m_currentColumn]->addWidget(item);
    m_PropertyToLayoutIndexMap[value] = m_currentColumn;
    m_currentColumn++;
    if (m_currentColumn >= m_columnCount - 1)
    {
        m_currentColumn = 0;
    }

    uasPropertyToLabelMap[value] = item;
    uasEnabledPropertyList.append(value);

    if(!uasPropertyValueMap.contains(value))
    {
        uasPropertyValueMap[value] = 0;
    }
    item->show();
    sortItems(m_columnCount);
}

void UASQuickView::sortItems(int columncount)
{
    QList<QWidget*> itemlist;
    for(QMap<QString,QuickViewItem*>::const_iterator i = uasPropertyToLabelMap.constBegin(); i!= uasPropertyToLabelMap.constEnd();i++)
    {
        m_verticalLayoutList[m_PropertyToLayoutIndexMap[i.key()]]->removeWidget(i.value());
        m_PropertyToLayoutIndexMap.remove(i.key());
        itemlist.append(i.value());
    }

    for(int i = 0; i < m_verticalLayoutList.size(); i++)
    {
        ui->horizontalLayout->removeItem(m_verticalLayoutList[i]);
        m_verticalLayoutList[i]->deleteLater();
    }
    m_verticalLayoutList.clear();

    for (int i = 0; i < columncount; i++ )
    {
        QVBoxLayout * layout = new QVBoxLayout();
        ui->horizontalLayout->addLayout(layout);
        m_verticalLayoutList.append(layout);
        layout->setMargin(0);
    }

    int currcol = 0;
    for(int i = 0; i < itemlist.size(); i++)
    {
        m_verticalLayoutList[currcol]->addWidget(itemlist[i]);
        currcol++;
        if (currcol >= columncount)
        {
            currcol = 0;
        }
    }
    m_currentColumn = currcol;
    QApplication::processEvents();
}

void UASQuickView::updateTimerTick()
{
    for (QMap<QString,QuickViewItem*>::const_iterator i = uasPropertyToLabelMap.constBegin(); i != uasPropertyToLabelMap.constEnd(); i++)
    {
        if(uasPropertyValueMap.contains(i.key()))
        {
            i.value()->setValue(uasPropertyValueMap[i.key()]);
        }
    }
    for (QMap<QString,QuickViewItem*>::const_iterator i = uasPropertyToLabelMap.constBegin();i!=uasPropertyToLabelMap.constEnd();i++)
    {
        i.value()->setValuePixelSize(30);
    }
}

void UASQuickView::valueChanged(const QString name, const float variant)
{
    uasPropertyValueMap[name] = variant;
//    qDebug() << name << variant;
}

void UASQuickView::addUAS(UASInterface *uas)
{
    if(uas)
    {
        this->uas = uas;
        connect(uas, SIGNAL(attitudeChanged(UASInterface*,double,double,double,quint64)),
                this, SLOT(attitudeChanged(UASInterface*,double,double,double,quint64)));
    }
}

void UASQuickView::attitudeChanged(UASInterface *uas, double roll, double pitch, double yaw, quint64 time)
{
    uasPropertyValueMap["Pitch"] = pitch * 180 / 3.14;
}
