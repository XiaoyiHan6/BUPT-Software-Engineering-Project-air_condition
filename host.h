#ifndef HOST_H
#define HOST_H

#include <QWidget>
#include "server.h"
#include <QDialog>
#include <QThread>
#include<QVector>
#include<iostream>
#include<QTimer>
#include"customer.h"
class Server;
class Customer;

using namespace std;
class Host : public QObject {
    Q_OBJECT
public:
    int state;//  0停止 1启动
    int mode; // 1制热  0制冷
  //  double temp;  //缺省温度  即开机温度
    double lowestTmp;
    double highestTmp;//主机的温控范围 老师文档给的18~25
    double defTargetTmp;               //缺省目标温度
    QVector<Customer*> Cus;
    void Add();
    void Wind_to_Temp_Rate(); //改为一个在0.1度的变化时间里--计时器为0后反馈给从机更新面板的函数

  //  double Charge( double time_, int wind); // 计费函数

    void Dispatch(int no);
    void Print();  // 测试需要  打出所有房间的详单
    void Update();  // 刷新数据库

    Host();






    ~Host();


    //新加的东西：
    int port=6666;
    Server *S ;
    QTimer *host_t;//主机工作时间的计时变量
  //  void Initial();
    void Add2();

    void Del();
    int PowerNum[4]={0};//开关机次数

    void setmode(int mode_);
    void setdefTargetTmp(int defTargetTmp_);
    void setlowestTmp(int lowestTmp_);
    void sethighestTmp(int highestTmp_);
    bool flag=true;// 用于发送SetQjson2
    double sum_price[4]={0};//每个房间的总费用
    int socketlist_prem=0;
public slots:
    void Run();

};

#endif // HOST_H
