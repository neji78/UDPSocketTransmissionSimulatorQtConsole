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

    child[0] = QThread::currentThread()->create(&Write,10,0);
    child[1] = QThread::currentThread()->create(&Write,100,1);
    child[2] = QThread::currentThread()->create(&Write,500,4);
    qDebug()  << "thread "<<child[0]->currentThreadId()<<"created";
    qDebug()  << "thread "<<child[1]->currentThreadId()<<"created";
    qDebug()  << "thread "<<child[2]->currentThreadId()<<"created";
    child[0]->start();
    child[1]->start();
    child[2]->start();
    Timer.start();
    return a.exec();
}

void Write(int freq,int motid)
{
    MDLProtocol* MDL = new MDLProtocol;
    // setting udp client
    QHostAddress add;
    add.setAddress("127.0.0.1");
    qDebug() << "setting ip address: 127.0.0.1";
    QUdpSocket* Client = new QUdpSocket();
    qDebug() << "creating client socket";;
    int seq = 0;
    srand (time(NULL));
    while(1){

        MDL->Packet->start = 0x05; //lsb
        MDL->Packet->seq = seq; //msb

        MDL->Packet->firstmotor_id = motid;
        MDL->Packet->firstchan_id = 2;
        MDL->Packet->firstdata = rand()%4000;

        MDL->Packet->secondmotor_id = motid + 2;
        MDL->Packet->secondchan_id = 3;
        MDL->Packet->seconddata = rand()%500;

        MDL->Packet->crc = Fast_CRC_Cal8Bits(0x00, 7, (uint8_t *)MDL->Packet);


        qDebug() << "thread "<<QThread::currentThreadId()<< "sending data";
        seq++;
        Client->writeDatagram((char*)MDL->Packet,sizeof(*MDL->Packet),add,8080);
        QThread::currentThread()->msleep(freq);
    }
}

