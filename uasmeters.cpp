#include "uasmeters.h"
#include "ui_uasmeters.h"
#include <QDebug>

UASMeters::UASMeters(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UASMeters)
{
    ui->setupUi(this);

    uasPropertyCount = 0;

    if(uasPropertyValueMap.size() == 0)
    {
        creatDial("Pitch");
        creatDial("Roll");
        creatCompass("Yaw");
//        creatDial("Yaw");
        creatDial("Speed");
        creatDial("Alttitude");
        creatDial("Throtte");
    }
    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &UASMeters::updateTimerTick);
    updateTimer->start(10);
}

void UASMeters::creatDial(QString str)
{
    QVBoxLayout *layout = new QVBoxLayout();

    QLabel *label = new QLabel();
    label->setText(str);
    label->setAlignment(Qt::AlignCenter);
    QFont font = label->font();
    font.setPixelSize(20);
    label->setFont(font);

    QwtDial *dial = new QwtDial();
    dial->setTracking( true );
    dial->setFocusPolicy(Qt::StrongFocus);

    QColor needleColor(Qt::red);
    switch (uasPropertyCount) {
    case 0:
        {
            dial->setOrigin(135.0);
            dial->setScaleArc(0.0,270.0);
            dial->setScaleMaxMinor(4);
            dial->setScaleMaxMajor(10);
            dial->setScale(-90.0,90.0);
            break;
        }
    case 1:
        {
            dial->setOrigin(135.0);
            dial->setScaleArc(0.0,270.0);
            dial->setScaleMaxMinor(4);
            dial->setScaleMaxMajor(10);
            dial->setScale(-60.0,60.0);
            break;
        }
    case 2:
        {
            dial->setOrigin(135.0);
            dial->setScaleArc(0.0,270.0);
            dial->setScaleMaxMinor(4);
            dial->setScaleMaxMajor(10);
            dial->setScale(0.0,80.0);
            break;
        }
    case 3:
        {
            dial->setOrigin(135.0);
            dial->setScaleArc(0.0,270.0);
            dial->setScaleMaxMinor(4);
            dial->setScaleMaxMajor(10);
            dial->setScale(0.0,100.0);
            break;
        }
    case 4:
        {
            dial->setOrigin(135.0);
            dial->setScaleArc(0.0,270.0);
            dial->setScaleMaxMinor(4);
            dial->setScaleMaxMajor(10);
            dial->setScale(0.0,100.0);
            break;
        }
    default:
        break;
    }

    QwtDialSimpleNeedle *needle = new QwtDialSimpleNeedle(
                QwtDialSimpleNeedle::Arrow,true,needleColor,QColor(Qt::gray).light(130));
    dial->setNeedle(needle);

    const QColor base( QColor( Qt::darkGray ).dark( 150 ) );
    QPalette palette;
    palette.setColor(QPalette::Base,base);
    palette.setColor( QPalette::Mid, base.dark( 110 ) );
    palette.setColor( QPalette::Text, base.dark( 200 ).light( 800 ) );
    dial->setPalette(palette);

    dial->setReadOnly(true);
    layout->addWidget(dial);
    layout->addWidget(label);
    ui->gridLayout->addLayout(layout,uasPropertyCount / 3,uasPropertyCount % 3);
    uasPropertyCount++;

    uasPropertyToDialMap[str] = dial;
    uasPropertyValueMap[str] = 0.0;
}

void UASMeters::creatCompass(QString str)
{
    QVBoxLayout *layout = new QVBoxLayout();

    QLabel *label = new QLabel();
    label->setText(str);
    label->setAlignment(Qt::AlignCenter);
    QFont font = label->font();
    font.setPixelSize(20);
    label->setFont(font);

    QwtCompass* compass = new QwtCompass();
    compass->setLineWidth(4);
    compass->setFrameShadow(QwtCompass::Raised);

    QwtCompassScaleDraw *scaleDraw = new QwtCompassScaleDraw();
    scaleDraw->enableComponent( QwtAbstractScaleDraw::Ticks, true );
    scaleDraw->enableComponent( QwtAbstractScaleDraw::Labels, true );
    scaleDraw->enableComponent( QwtAbstractScaleDraw::Backbone, true );
    scaleDraw->setTickLength( QwtScaleDiv::MinorTick, 0 );
    scaleDraw->setTickLength( QwtScaleDiv::MediumTick, 0 );
    scaleDraw->setTickLength( QwtScaleDiv::MajorTick, 3 );

    compass->setScaleDraw( scaleDraw );

    compass->setNeedle( new QwtCompassMagnetNeedle(
        QwtCompassMagnetNeedle::TriangleStyle, Qt::white, Qt::red ) );

    const QColor base( QColor( Qt::darkGray ).dark( 150 ) );
    QPalette palette;
    palette.setColor(QPalette::Base,base);
    palette.setColor( QPalette::Mid, base.dark( 110 ) );
    palette.setColor( QPalette::Text, base.dark( 200 ).light( 800 ) );
    compass->setPalette(palette);
    compass->setValue( 0.0 );
    compass->setReadOnly(true);

    layout->addWidget(compass);
    layout->addWidget(label);
    ui->gridLayout->addLayout(layout,uasPropertyCount / 3,uasPropertyCount % 3);
    uasPropertyCount++;

    uasPropertyToComMap[str] = compass;
    uasPropertyValueMap[str] = 0.0;
}

UASMeters::~UASMeters()
{
    delete ui;
}

void UASMeters::updateTimerTick()
{
    for(QMap<QString,QwtDial*>::const_iterator i = uasPropertyToDialMap.constBegin(); i != uasPropertyToDialMap.constEnd(); i++)
    {
        if(uasPropertyValueMap.contains(i.key()))
        {
            i.value()->setValue(uasPropertyValueMap[i.key()]);
        }
    }
    for(QMap<QString,QwtCompass*>::const_iterator i = uasPropertyToComMap.constBegin(); i != uasPropertyToComMap.constEnd(); i++)
    {
        if(uasPropertyValueMap.contains(i.key()))
        {
            i.value()->setValue(uasPropertyValueMap[i.key()]);
        }
    }
}

void UASMeters::valueChanged(const QString name, const float variant)
{
    uasPropertyValueMap[name] = variant;
//    qDebug() << variant;
}
