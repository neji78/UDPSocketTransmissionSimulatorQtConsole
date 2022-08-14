#ifndef CONNECTION_H
#define CONNECTION_H

#include <QUdpSocket>
#include <QString>
#include <QTime>
#include <QThread>
#include "CRC.h"

#pragma pack(1)

// Data Structures
struct Hover
{
    uint16_t voltage;
    int16_t current;
    uint16_t rpm;
    int16_t esc_temp;
    int16_t motor_temp;
    int16_t battery_temp;
};

struct Cruise
{
    uint16_t voltage;
    int16_t current;
    uint16_t rpm;
    int32_t esc_temp;
    int16_t motor_temp;
    int16_t battery_temp;
};

struct Eng
{
    uint8_t ST;
    struct Hover ESC[8];
    struct Cruise esc_cr;
    uint8_t valid[7];
    uint8_t seq;
    uint8_t crc;

};

void initialize();
void DataGenerate(struct Eng* Vehicle, int i);
void Write();


QUdpSocket* Client;
QHostAddress add;
QTime tik;
QThread* child;


#endif // CONNECTION_H
