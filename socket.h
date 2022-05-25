#ifndef SOCKET_H
#define SOCKET_H

#include <QTcpSocket>
#include <QObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <string>
#include<iostream>
#include"customer.h"
#include"host.h"
class Host;
class Customer;
using namespace std;

class TcpClientSocket : public QTcpSocket
{
    Q_OBJECT
public:
    TcpClientSocket(QObject *parent=0);
    ~TcpClientSocket();
    bool WriteData( const char *data, qint64 len );
    bool SetQjson1(int mode,bool isServed,double lowestTmp,double highestTmp,double defTargetTmp,double roomTmp);
    bool SetQjson2(bool isServed,int roomNum,double roomTmp,double Kwh,double fee); //用于回传这边增或减0.1度的信号量
    bool QBtoJ();
    QByteArray getbyte();
    Customer *C;
    void InitialC();
    Host *host_socket;
signals:
    void disconnected(int);
protected slots:
    void dataReceived();
  //  void slotDisconnected();
private:
    QByteArray byte;
    QJsonObject message;

};

#endif // SOCKET_H
