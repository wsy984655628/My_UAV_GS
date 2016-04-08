
#include "uas.h"
#include "uasmanager.h"
#include "my_gs.h"
#include "comm/gsmavlink.h"
#include "comm/linkmanager.h"

#include <QList>
#include <QMessageBox>
#include <QTimer>
#include <QSettings>
#include <iostream>
#include <QDesktopServices>

#include <cmath>
#include <qmath.h>

#include <QDebug>
#include "SerialCommunication/serialsettingdialog.h"

UAS::UAS(MAVLINKProtocol* protocol, int id) : UASInterface(),
   uasId(id),
   unknownPackets(),

   name(""),
   type(-1),
   autopilot(-1),
   base_mode(-1),
   // custom_mode not initialized
   custom_mode(-1),
   status(-1),

   onboardTimeOffset(0),

   attitudeStamped(false),
   lastAttitude(0),

   batteryVoltage(12.6),

   roll(0.0),
   pitch(0.0),
   yaw(0.0),
   groundSpeed(0.0),
   throttle(0),
   altitudeAMSL(0.0),
   altitudeRelative(0.0),

   // The protected members.
   lastNonNullTime(0)
{
   Q_UNUSED(protocol);

   for (unsigned int i = 0; i<255;++i)
   {
       componentID[i] = -1;
       componentMulti[i] = false;
   }

   systemId = My_GS::defaultSystemId;
   componentId = My_GS::defaultComponentId;

   m_heartbeatsEnabled = true;
   QTimer *heartbeattimer = new QTimer(this);
   connect(heartbeattimer,SIGNAL(timeout()),this, SLOT(sendHeartbeat()));
   heartbeattimer->start(MAVLINK_HEARTBEAT_DEFAULT_RATE * 1000);
}

/**
* Saves the settings of name, airframe, autopilot type and battery specifications
* by calling writeSettings.
*/
UAS::~UAS()
{
}


int UAS::getUASID() const
{
   return uasId;
}

void UAS::receiveMessage( mavlink_message_t message)
{
   if (message.sysid == uasId && (!attitudeStamped || (attitudeStamped && (lastAttitude != 0)) || message.msgid == MAVLINK_MSG_ID_ATTITUDE))
   {
       switch (message.msgid)
       {
       case MAVLINK_MSG_ID_HEARTBEAT:
       {
           emit heartbeat(this);
//           qDebug() << "heartbeat";
           mavlink_heartbeat_t state;
           mavlink_msg_heartbeat_decode(&message, &state);

           // Send the base_mode and system_status values to the plotter. This uses the ground time
           // so the Ground Time checkbox must be ticked for these values to display
           quint64 time = getUnixTime();
           QString name = QString("M%1:HEARTBEAT.%2").arg(message.sysid);
           emit valueChanged(uasId, name.arg("base_mode"), "bits", state.base_mode, time);
           emit valueChanged(uasId, name.arg("custom_mode"), "bits", state.custom_mode, time);
           emit valueChanged(uasId, name.arg("system_status"), "-", state.system_status, time);
           }
           break;

       case MAVLINK_MSG_ID_SYS_STATUS:
       {
           qDebug() << "sys status receive";
           mavlink_sys_status_t state;
           mavlink_msg_sys_status_decode(&message, &state);
           quint64 time = getUnixTime();

           setBatteryVoltage(state.voltage_battery);
           emit batteryChanged(this,getBatteryVoltage(), time);
           qDebug() << getBatteryVoltage();

       }
           break;

       case MAVLINK_MSG_ID_ATTITUDE:
       {
           mavlink_attitude_t attitude;
           mavlink_msg_attitude_decode(&message, &attitude);
           quint64 time = getUnixReferenceTime(attitude.time_boot_ms);

           lastAttitude = time;
           setRoll(My_GS::limitAngleToPMPIf(attitude.roll));
           setPitch(My_GS::limitAngleToPMPIf(attitude.pitch));
           setYaw(My_GS::limitAngleToPMPIf(attitude.yaw));

           emit attitudeChanged(this, getRoll(), getPitch(), getYaw(), time);
           emit attitudeRotationRatesChanged(uasId, attitude.rollspeed, attitude.pitchspeed, attitude.yawspeed, time);

           QString name = QString("M%1:GCS Status.%2").arg(message.sysid);
           emit valueChanged(uasId,name.arg("Roll"),"deg",QVariant(getRoll() * (180.0/M_PI)),time);
           emit valueChanged(uasId,name.arg("Pitch"),"deg",QVariant(getPitch() * (180.0/M_PI)),time);
           emit valueChanged(uasId,name.arg("Yaw"),"deg",QVariant(getYaw() * (180.0/M_PI)),time);
//           qDebug() << getRoll();
       }
           break;

       case MAVLINK_MSG_ID_ATTITUDE_QUATERNION:
       {
           qDebug() << "msg receive";
       }
           break;

       case MAVLINK_MSG_ID_VFR_HUD:
       {
           mavlink_vfr_hud_t hud;
           quint64 time = getUnixTime();

           // Display updated values
           setThrottle(hud.throttle);
           setGroundSpeed(hud.groundspeed);
           setAltitudeAMSL(hud.alt);

           emit thrustChanged(this, getThrottle()/100.0);
           emit speedChanged(this, getGroundSpeed(), time);
           emit altitudeChanged(this,getAltitudeAMSL(), getAltitudeRelative(), time);
       }break;

       default:
       {
           if (!unknownPackets.contains(message.msgid))
           {
               unknownPackets.append(message.msgid);
#ifdef QT_DEBUG // Remove these messages from the release build
               QString errString = tr("UNABLE TO DECODE MESSAGE NUMBER %1").arg(message.msgid);
               emit textMessageReceived(uasId, message.compid, 255, errString);
#endif
//               QLOG_INFO() << "Unable to decode message from system " << message.sysid
//                           << " with message id:" << message.msgid;
           }
       }
           break;
       }
   }
   emit mavlinkMessageRecieved(message);
}

quint64 UAS::getUnixReferenceTime(quint64 time)
{
   // Same as getUnixTime, but does not react to attitudeStamped mode
   if (time == 0)
   {
       //        QLOG_DEBUG() << "XNEW time:" <<My_GS::groundTimeMilliseconds();
       return My_GS::groundTimeMilliseconds();
   }
   // Check if time is smaller than 40 years,
   // assuming no system without Unix timestamp
   // runs longer than 40 years continuously without
   // reboot. In worst case this will add/subtract the
   // communication delay between GCS and MAV,
   // it will never alter the timestamp in a safety
   // critical way.
   //
   // Calculation:
   // 40 years
   // 365 days
   // 24 hours
   // 60 minutes
   // 60 seconds
   // 1000 milliseconds
   // 1000 microseconds
#ifndef _MSC_VER
   else if (time < 1261440000000000LLU)
#else
   else if (time < 1261440000000000)
#endif
   {
       //        QLOG_DEBUG() << "GEN time:" << time/1000 + onboardTimeOffset;
       if (onboardTimeOffset == 0)
       {
           onboardTimeOffset = My_GS::groundTimeMilliseconds() - time/1000;
       }
       return time/1000 + onboardTimeOffset;
   }
   else
   {
       // Time is not zero and larger than 40 years -> has to be
       // a Unix epoch timestamp. Do nothing.
       return time/1000;
   }
}

quint64 UAS::getUnixTimeFromMs(quint64 time)
{
   return getUnixTime(time*1000);
}

quint64 UAS::getUnixTime(quint64 time)
{
   quint64 ret = 0;
   if (attitudeStamped)
   {
       ret = lastAttitude;
   }

   if (time == 0)
   {
       ret = My_GS::groundTimeMilliseconds();
   }
   // Check if time is smaller than 40 years,
   // assuming no system without Unix timestamp
   // runs longer than 40 years continuously without
   // reboot. In worst case this will add/subtract the
   // communication delay between GCS and MAV,
   // it will never alter the timestamp in a safety
   // critical way.
   //
   // Calculation:
   // 40 years
   // 365 days
   // 24 hours
   // 60 minutes
   // 60 seconds
   // 1000 milliseconds
   // 1000 microseconds
#ifndef _MSC_VER
   else if (time < 1261440000000000LLU)
#else
   else if (time < 1261440000000000)
#endif
   {
       //        QLOG_DEBUG() << "GEN time:" << time/1000 + onboardTimeOffset;
       if (onboardTimeOffset == 0 || time < (lastNonNullTime - 100))
       {
           lastNonNullTime = time;
           onboardTimeOffset = My_GS::groundTimeMilliseconds() - time/1000;
       }
       if (time > lastNonNullTime) lastNonNullTime = time;

       ret = time/1000 + onboardTimeOffset;
   }
   else
   {
       // Time is not zero and larger than 40 years -> has to be
       // a Unix epoch timestamp. Do nothing.
       ret = time/1000;
   }

   return ret;
}

void UAS::valueChangedRec(const int uasId, const QString& name, const QString& unit, const QVariant& value, const quint64 msec)
{
   emit valueChanged(uasId,name,unit,value,msec);
}


void UAS::sendMessage(mavlink_message_t message)
{
    if(!LinkManager::instance())
        return;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    int len = mavlink_msg_to_send_buffer(buffer, &message);
    static uint8_t messageKeys[256] = MAVLINK_MESSAGE_CRCS;
    mavlink_finalize_message_chan(&message, systemId, componentId,0, message.len, messageKeys[message.msgid]);

    SerialSettingDialog::instance()->getSerial()->write((const char*)buffer, len);
}

void UAS::sendHeartbeat()
{
    if(m_heartbeatsEnabled)
    {
        mavlink_message_t beat;
        mavlink_msg_heartbeat_pack(getSystemId(), getComponentId(),&beat, MAV_TYPE_GCS, MAV_AUTOPILOT_INVALID, MAV_MODE_MANUAL_ARMED, 0, MAV_STATE_ACTIVE);
        sendMessage(beat);
    }
}

void UAS::enableExtra1Transmission(int rate)
{
    mavlink_message_t msg;
    mavlink_request_data_stream_t stream;
    stream.req_stream_id = MAV_DATA_STREAM_EXTRA1;
    stream.req_message_rate = rate;
    stream.start_stop = (rate) ? 1 : 0;
    stream.target_system = uasId;
    stream.target_component = 0;
    mavlink_msg_request_data_stream_encode(systemId, componentId, &msg, &stream);
    sendMessage(msg);
    sendMessage(msg);
    qDebug() << "enableExtra1";
}
