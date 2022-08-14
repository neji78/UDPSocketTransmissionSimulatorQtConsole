#ifndef CONNECTION_H
#define CONNECTION_H

#include <QUdpSocket>
#include <QString>
#include <QTime>
#include <QThread>
#include "CRC.h"

#pragma pack(1)

// Data Structures


void initialize();
void DataGenerate(struct Eng* Vehicle, int i);
void Write();


QUdpSocket* Client;
QHostAddress add;
QTime tik;
QThread* child;


#endif // CONNECTION_H
