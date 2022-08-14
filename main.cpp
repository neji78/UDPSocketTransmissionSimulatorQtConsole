#include <QCoreApplication>

#include "Connection.h"
#include <QDebug>
#include <iostream>
#include <QtMath>
#include <stdlib.h>
#include <time.h>
#include <QElapsedTimer>
#include "mdlprotocol.h"


#define PORT     8080
#define MAXLINE 1024
using namespace std;
QElapsedTimer Timer;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    child = QThread::currentThread()->create(&Write);
    qDebug()  << "running...";
    child->start();
    Timer.start();
    return a.exec();
}

void Write()
{
    MDLProtocol* MDL = new MDLProtocol;
    // setting udp client
    add.setAddress("127.0.0.1");
    qDebug() << "setting ip address: 127.0.0.1";
    Client = new QUdpSocket();
    qDebug() << "creating client socket";;
    int seq = 0;
    srand (time(NULL));
    while(1){

        MDL->Packet->start = 0x05; //lsb
        MDL->Packet->seq = seq; //msb

        MDL->Packet->firstmotor_id = rand()%16;
        MDL->Packet->firstchan_id = rand()%16;
        MDL->Packet->firstdata = rand()%100;

        MDL->Packet->secondmotor_id = rand()%16;
        MDL->Packet->secondchan_id = rand()%16;
        MDL->Packet->seconddata = rand()%100;

        MDL->Packet->crc = Fast_CRC_Cal8Bits(0x00, 7, (uint8_t *)MDL->Packet);


        qDebug() << "firstdata: " + QString::number(MDL->Packet->seconddata);
        seq++;
        Client->writeDatagram((char*)MDL->Packet,sizeof(*MDL->Packet),add,8080);
        child->msleep(250);
    }
}

