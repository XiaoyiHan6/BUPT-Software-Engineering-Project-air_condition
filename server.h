#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QObject>
#include <QMap>

#include "socket.h"
#include"host.h"
class TcpClientSocket;
class Host;
class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server(QObject *parent=0,int port=0);
    ~Server();
    QList<TcpClientSocket*> tcpClientSocketList;

    void	Run	( quint16 port );
   // QMap<int,int> Power_Num;//socket号对应的开关机次数
    Host *host_server;
signals:
    void updateServer(QString);
public slots:
  //  void updateClients (QString,int);
    void slotDisconnected(int);
protected:
    void incomingConnection(int socketDescriptor);
private:
    int port;


};

#endif // SERVER_H
