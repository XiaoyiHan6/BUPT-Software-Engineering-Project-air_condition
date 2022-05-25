#include "dialog9.h"
#include "ui_dialog9.h"
#include "dialog2.h"
#include "dialog1.h"
#include<QDebug>
#include"host.h"
#include <QDebug>
#include <QThread>
#include "mainwindow.h"
#include "server.h"

class Host;
Host host1;
Server SS;

Dialog9::Dialog9(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog9)
{
    ui->setupUi(this);
}

Dialog9::~Dialog9()
{
    delete ui;
}

void Dialog9::on_pushButton_clicked()//起键
{
        qDebug()<<"主机温控开始";
        host->host_t->start(6000);//主机调度计时开始
        qDebug()<<host->S->tcpClientSocketList.size();
        if(host->S->tcpClientSocketList.size()>=0&&host->S->tcpClientSocketList.size()<=4)
        host->Add();//将最初加入的客户端指针加入vector调度
        host->socketlist_prem=0;
        host->Wind_to_Temp_Rate(); //主机进行温控

}

void Dialog9::on_pushButton_2_clicked()//查看
{
    Dialog2 *log=new Dialog2(this);

//    this->host->terminate();
  //  this->host->wait();

    log->host=this->host;
    qDebug()<<host->mode;
    log->show();
    log->display();

}

void Dialog9::on_pushButton_3_clicked() //停机
{

    if(this->host->host_t->isActive())
    this->host->host_t->stop();
    if(this->host->Cus.size()>0){
        for(int i=0;i<this->host->Cus.size();i++)
            this->host->Cus[i]->t->stop();
    }
    this->host->S->tcpClientSocketList.clear();
    this->host->Cus.clear();

    qDebug()<<"关机成功";

}

void Dialog9::on_pushButton_4_clicked()//转到Dialog1配置
{
    Dialog1 *log=new Dialog1(this);
    log->host=this->host;
    log->show();
}

void Dialog9::on_pushButton_5_clicked()
{

    SS.Run(6666);
    host1.S=&SS;
    SS.host_server=&host1;
 //   host1.S->Run(host1.port);
    qDebug()<<"电源启动成功"<<host1.S->tcpClientSocketList.size();
    this->host=&host1;

}
