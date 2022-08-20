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
void Write(int freq,int motid);

QTime tik;
QThread* child[3];


#endif // CONNECTION_H
