#include "server.h"
#include<QDebug>
#include <QHostAddress>
#include"customer.h"
Server::Server(QObject *parent,int port)
    :QTcpServer(parent)
{

    tcpClientSocketList.empty();


}

void Server::Run( quint16 port ){      //这个地方合图形的时候需要改和上面的构造函数合并 就是端口的设置是从窗口手动输入
    if(this->listen(QHostAddress::Any, port) ){

     }
     else   qDebug()<<"Server listen failed !" ;

}
void Server::incomingConnection(int socketDescriptor)
{
     qDebug()<< "incomingConnection():"<<socketDescriptor ;
    TcpClientSocket *tcpClientSocket=new TcpClientSocket(this);
    tcpClientSocket->setSocketDescriptor(socketDescriptor);

    tcpClientSocket->host_socket=this->host_server;

    tcpClientSocket->InitialC();//初始化一个客户

    connect(tcpClientSocket,SIGNAL(disconnected(int)),this,SLOT(slotDisconnected(int)));

    tcpClientSocketList.append(tcpClientSocket);
    qDebug()<<"server_listsize"<<tcpClientSocketList.size();

    //Power_Num[socketDescriptor]=1;




}
void Server::slotDisconnected(int descriptor)
{
    qDebug()<<"descriptor号"<<descriptor<<"list_size"<<tcpClientSocketList.count();
    int tem=-1;
    for(int i=0;i<tcpClientSocketList.count();i++)
    {
        TcpClientSocket *item = tcpClientSocketList.at(i);

        if(item->socketDescriptor()==descriptor)
        {
            if(this->host_server->Cus.size()>0){  //解决没服务完就临时关机的情况 需要从调度队列移除
                QVector<Customer*>::iterator it1;
                it1=host_server->Cus.begin();
                for(;it1!=host_server->Cus.end();){
                    if((*it1)->room_ip.contains((item)->C->roomNum)){
                        (item)->C->t->stop();
                        (item)->C->tt.start();//关机时间
                        (item)->C->tt.currentTime();
                        (item)->C->endtime=(item)->C->tt.currentTime().toString();
                        qDebug()<<"server_Cus删除成功";
                        it1=host_server->Cus.erase(it1);
                    }
                    else it1++;
                }


            }
            qDebug()<<"sever_disconnect_tem"<<tem;
            item->disconnectFromHost();

            tcpClientSocketList.removeAt(i);

            qDebug()<<"调用slotDisconnected_server";
            return;
        }
    }

    return;
}

Server::~Server()
{
    qDeleteAll( tcpClientSocketList );
    tcpClientSocketList.clear();
}
