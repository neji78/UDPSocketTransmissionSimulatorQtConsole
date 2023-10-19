#include <QCoreApplication>

#include "connection.h"
#include <QDebug>
#include <iostream>
#include <QtMath>
#include <stdlib.h>
#include <time.h>
#include <QElapsedTimer>


#define PORT     8080
#define MAXLINE 1024
using namespace std;
QElapsedTimer Timer;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    child = QThread::currentThread()->create(&Write);
    child->start();
    Timer.start();
    qDebug()  << "running...";
    return a.exec();
}

void DataGenerate(struct Eng* Vehicle, int i)
{
    Vehicle->ESC[i].current = (uint16_t)((Timer.elapsed()/1000)+ 1500);
    Vehicle->ESC[i].voltage = (uint16_t)(tik.currentTime().msec()%300);
    Vehicle->ESC[i].rpm = (uint16_t)(rand()%4500);

    Vehicle->ESC[i].battery_temp = (uint16_t)(tik.currentTime().msec()%190);
    Vehicle->ESC[i].esc_temp = (uint16_t)(tik.currentTime().msec()%150);
    Vehicle->ESC[i].motor_temp = (uint16_t)(tik.currentTime().msec()%60);


}
void Write()
{
    // setting udp client
    add.setAddress("127.0.0.1");
    qDebug() << "setting ip address: 127.0.0.1";
    Client = new QUdpSocket();
    struct Eng* S5M = new struct Eng;
    qDebug() << "creating client socket";
    memset(S5M,0,sizeof(struct Eng));
    int seq = 0;
    srand (time(NULL));
    qDebug() << "sendding packet ...";
    printf("|%12s|%12s|%12s|%12s|%12s|%12s|%12s|\n", "Packet Num#","Current","Voltage","RPM","Battery Temp","Esc Temp","Motor Temp");
    printf("\n");
    while(1){
        S5M->ST = 0x55;
        for(int j = 0;j < 8;j++) {
            DataGenerate(S5M,j);
        }
        for(int i = 0;i < 7;i++) {
            S5M->valid[i] = 0xff;
        }
        S5M->seq = seq;
        S5M->crc = Fast_CRC_Cal8Bits(0x00, 119, (uint8_t *)S5M);
        int i = 0;
        printf("|%12s|%12s|%12s|%12s|%12s|%12s|%12s|\n",QString::number(seq).toStdString().data(),QString::number(S5M->ESC[i].current).toStdString().data(),
               QString::number(S5M->ESC[i].voltage).toStdString().data(),QString::number(S5M->ESC[i].rpm).toStdString().data(),
               QString::number(S5M->ESC[i].battery_temp).toStdString().data(),QString::number(S5M->ESC[i].esc_temp).toStdString().data(),
               QString::number(S5M->ESC[i].motor_temp).toStdString().data()
               );
        seq++;
        Client->writeDatagram((char*)S5M,sizeof(*S5M),add,8080);
        child->msleep(250);
    }
}

