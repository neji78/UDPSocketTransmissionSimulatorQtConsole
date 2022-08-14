#ifndef MDLPROTOCOL_H
#define MDLPROTOCOL_H
#include "iostream"
#include <QObject>
#include <QByteArray>
#pragma(1)
enum warningID{
    WARNING1,
    WARNING2
};
enum errorID{
    ERROR1,
    ERROR2
};
enum reserveID{
    RES1,
    RES2,
    RES3,
    RES4,
    RES5,
};

enum channelID{
    VOLTAGE,
    CURRENT,
    RPM,
    ESC_TEMP,
    MOTOR_TEMP,
    BATTERY_TEMP,
    SUPPLY_VOLT,
    errorID,
    warningID,
};
enum hoverID{
    HOVER1,
    HOVER2,
    HOVER3,
    HOVER4,
    HOVER5,
    HOVER6,
    HOVER7,
    HOVER8

};
enum cruiseID{
    CRUISE1
};
enum moduleID{
    MODULE1,
    MODULE2,
    MODULE3,
    MODULE4,
    MODULE5,
    MODULE6
};

enum motorID{
    GENERAL,
    hoverID,
    cruiseID,
    moduleID
};
typedef struct __attribute__((packed)){
    uint8_t start :4;
    uint8_t seq   :4;
    uint8_t firstchan_id :4;
    uint8_t firstmotor_id :4;
    uint16_t firstdata;
    uint8_t secondchan_id :4;
    uint8_t secondmotor_id :4;
    uint16_t seconddata;
    uint8_t crc;
}mdlpacket;


class MDLProtocol:public QObject
{
    Q_OBJECT
public:
    channelID chan;
    motorID motor;
    mdlpacket* Packet = new mdlpacket;
    MDLProtocol();

public slots:
    void MDLDecode(QByteArray msg);
    void MDLEncode();

signals:
    void update();

};

#endif // MDLPROTOCOL_H
