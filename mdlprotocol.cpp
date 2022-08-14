#include "mdlprotocol.h"
//mdlprotocol or motor data link protocol are made to create lightwaight data to transfer inorder to
//increasing bandwith of link
#include <QDebug>

MDLProtocol::MDLProtocol():QObject()
{

}

void MDLProtocol::MDLDecode(QByteArray msg)
{
    Packet = new mdlpacket;
    Packet = reinterpret_cast<mdlpacket*>(&msg);
    qDebug()<<Packet->start;
}

void MDLProtocol::MDLEncode()
{

}
