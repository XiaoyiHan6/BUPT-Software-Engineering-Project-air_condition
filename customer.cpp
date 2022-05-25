#include"customer.h"
#include<QTimer>
#include<QTime>
#include<QDebug>
double Customer:: JudgeWind_Kwh(int wind){  //这是每秒用的瓦数
    switch (wind) {
    case 0:
        return 0.0125;

    case 1:
        return 0.0167;
    case 2:
        return 0.02083;
    }
}
void Customer::info(){
    if(!this->satisfied()&&(this->isServed)){
        if(targetTmp>=this->lowestTmp&&targetTmp<=this->highestTmp){
            time_+=Feedback(); //每服务0.1度的时间就加入从机的总服务时间
            Kwh+=Feedback()*JudgeWind_Kwh(windSpeed);  //每服务0.1度后算一次瓦数，有效避免用户临时改风速的情况
            fee=Kwh;

            if(mode==1){//制热
                this->roomTmp=this->roomTmp+0.1;

            }
            else if(mode==0){//制冷
                this->roomTmp=this->roomTmp-0.1;
            }
            qDebug()<<"info_roomTmp"<<this->roomTmp<<"房号："<<this->roomNum;

            this->socket_cus->SetQjson2(isServed,roomNum,roomTmp,Kwh,fee);
        }

    }


}
Customer::Customer(){
    t=new QTimer(this);
    connect(t,SIGNAL(timeout()),this, SLOT(info()) );
}

void Customer::settargetTmp(double Tmp){
    this->targetTmp=Tmp;
}


void Customer:: setdefRoomTmp(double Tmp){
    this->roomTmp=Tmp;
}

void Customer::setroomNum(int no){
    this->roomNum=no;
}

void Customer::setwindSpeed(int speed){
    this->windSpeed=speed;
}

void Customer::setpower(bool power){
    this->power=power;
}

void Customer::setmode(int mode){
    this->mode=mode;
}

int Customer:: Feedback(){// 计算每变化0.1度的时间给主机 由主机调用此函数后发给从机

 switch(this->windSpeed){
    case 0:
        return 18;//一度3分钟 则0.1度18s   ，这个到时候可以改
     case 1:
        return 12; //一度2分钟 0.1度12s
     case 2:
        return 6;
 }
}

bool Customer::satisfied(){//给主机判断当前从机是否达到目标
    if(targetTmp>=this->lowestTmp&&targetTmp<=this->highestTmp){
        if(mode==0){//制冷
          //  qDebug()<<"targetTmp_satisfied"<<this->targetTmp;
            if( this->targetTmp>=this->roomTmp)
                return true;
            else return false;
        }
        else if(mode==1){//制热
          //  qDebug()<<"targetTmp_satisfied"<<this->targetTmp;

            if( this->targetTmp<=this->roomTmp)
                return true;
            else return false;
        }
    }
    else return false;


}

Customer::~Customer(){}

