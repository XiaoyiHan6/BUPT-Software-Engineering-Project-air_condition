#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <QTimer>
#include <QTime>
#include<QMap>
#include"socket.h"
class TcpClientSocket;
class Customer: public QObject{
    Q_OBJECT
 public:
    int roomNum; //房间号
    double roomTmp; //室温
    double targetTmp;//目标温度
    int windSpeed;//风速 （0，1，2三选一，分别代表低、中、高档）
    bool power=false;//开机 0为关机 1为开机
    bool isServed=false;//服务状态 （true代表服务，false挂起）
    int mode;//模式  制冷0  制热1
    double defRoomTmp ;//缺省室温 此值代表从机启动时的那个室温，和从机//不工作时最终趋于的那个温度是一个值
    double lowestTmp;                  //允许设置目标温度的最低温度
    double highestTmp;
    double defTargetTmp;
    double Kwh=0;//消耗能量
    double fee=0;//金额
    double count=0; //每次接受从机每达到增加1度后 用于从机每变化一度来计费 因为从机每次变0.1度都要向主机反馈一次，所以整个数只管++0.1度
    QTimer *t; // 每个房间有自己的计时器 就是增或减0.1度的倒计时时间
    Customer();
    QTime tt;

    int time_=0;//主机负责记录每个从机的服务时间到从机副本
    QMap<int,int> room_ip;
    double JudgeWind_Kwh(int wind);
    bool flag=false;//用于判断被挂起时每次+0.1度 后是否到达1度

    void settargetTmp(double Tmp);
    void setdefRoomTmp(double Tmp);
    void setroomNum(int);
    void setwindSpeed(int);
    void setpower(bool);
    void setmode(int);

    int Feedback();// 计算每变化0.1度的时间交给主机 由主机调用此函数后发给从机
    bool satisfied();//给主机判断当前从机是否达到目标
    QString starttime;//开始运行时间
    QString endtime;//关机时间
    ~Customer();

    //新加的：
    TcpClientSocket *socket_cus;
    bool Satisfy=false;
public slots:
    void info();

};





#endif // CUSTOMER_H

