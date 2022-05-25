#include "host.h"
#include<QDebug>
#include<QTimer>
#include<QTime>
#include<fstream>
#include<iomanip>
Host::Host(){
    Cus.empty();
    host_t=new QTimer(this);
    connect(host_t,SIGNAL(timeout()),this, SLOT(Run()) );

}

Host::~Host(){

}

void Host::Add() {  //调用Server里的tcpClientSocketList，将初始建立连接的客户端房间信息加入容器中
    //因为一旦建立连接，除非客户端关机断开连接，否则tcpClientSocketList不会删除当前队列中的信息，无法正确调度
    //初始只选择tcpClientSocketList里的最多前三个加入
    qDebug()<<"Add-list"<<this->S->tcpClientSocketList.size();
    for(int i=0;i<this->S->tcpClientSocketList.size();i++){
        //this->PowerNum[S->tcpClientSocketList[i]->C->roomNum]+=1;
         if(Cus.size()==3){
             S->tcpClientSocketList[i]->C->isServed=false;//则第四个被挂起
             qDebug()<<S->tcpClientSocketList[i]->C->roomNum<<"号房间被挂起";
             S->tcpClientSocketList[i]->SetQjson2(S->tcpClientSocketList[i]->C->isServed,S->tcpClientSocketList[i]->C->roomNum,S->tcpClientSocketList[i]->C->roomTmp,S->tcpClientSocketList[i]->C->Kwh,S->tcpClientSocketList[i]->C->fee);
             break;
         }

         else{
            S->tcpClientSocketList[i]->C->isServed=true;  //最初的加入便开始服务
            this->Cus.push_back(S->tcpClientSocketList[i]->C);

         }

    }

}
void Host::Add2(){ //判断服务队列是否availiable 如果空闲则加入新来的从机
    int j=0;bool flagg=true;
    qDebug()<<"Add2_list"<<this->S->tcpClientSocketList.size();
    qDebug()<<"Add2_cus前"<<Cus.size();
    for(int i=0;i<this->S->tcpClientSocketList.size();i++,flagg=true){
        qDebug()<< "前socketlist_prem"<<this->socketlist_prem;
        if (!(this->S->tcpClientSocketList.size()>this->socketlist_prem)) {//如果tcpClientSocketList.size比原来的size大的话表明有新从机来连接
            this->socketlist_prem=this->S->tcpClientSocketList.size();
            flagg=false;
            qDebug()<< "后socketlist_prem"<<this->socketlist_prem;

        }

        int count=0;
        for(int j=0;j<Cus.size();j++){
            if(Cus[j]->roomNum==this->S->tcpClientSocketList[i]->C->roomNum){
                count++;
            }
        }
        if(count!=0)
         flagg=false;


        if(flagg&&Cus.size()<3){//  ==3的情况留给Run()里面来处理
            if(!S->tcpClientSocketList[i]->C->satisfied()){
                S->tcpClientSocketList[i]->C->isServed=true;
                S->tcpClientSocketList[i]->C->t->start(S->tcpClientSocketList[i]->C->Feedback()*1000);//计时开始
                qDebug()<<S->tcpClientSocketList[i]->C->roomNum<<"加入服务队列_Add2中";
                this->Cus.push_back(S->tcpClientSocketList[i]->C);
                this->S->tcpClientSocketList[i]->SetQjson2(S->tcpClientSocketList[i]->C->isServed,S->tcpClientSocketList[i]->C->roomNum,S->tcpClientSocketList[i]->C->roomTmp,S->tcpClientSocketList[i]->C->Kwh,S->tcpClientSocketList[i]->C->fee);//被挂起到一度后可以调度
             //   this->PowerNum[S->tcpClientSocketList[i]->C->roomNum]+=1;
                this->socketlist_prem+=1;
            }

        }
        else{
            if(Cus.size()==3&&flagg){
                qDebug()<<"Add2的Dispatch"<<i<<"号";
                this->socketlist_prem+=1;
                this->Dispatch(i);
            }
        }
    }
    qDebug()<<"Add2_cus后"<<Cus.size();
}


void Host::Wind_to_Temp_Rate(){ //由从机传来的风速和当前从机房内温度 进行 温度计算及控制 返回从机每分钟降
    //薇薇： 按他们的意思是每过一度算一次费用，所以这个地方返回的是一度所用的时间（这个是有改变的）你看我理解的对不对
    //papa: 这个在主机里面用计时器--，到0后才发包给从机
    qDebug()<<"Wind_to_Temp_Rate Cus.size"<<Cus.size();
    if(Cus.size()>0){
        for(int i=0;i<Cus.size();i++){
             Cus[i]->t->start(Cus[i]->Feedback()*1000);
        }
    }


}

void Host::Print(){
    ofstream outfile;
    outfile.open("host.txt",ios::app);
    if(!outfile){
        qDebug() << "文件不能打开" <<endl;
    }
    else{
        outfile<<"房间号"<<setw(10)<< "目标温度"<<setw(10)<<"当前温度"<<setw(10)<<"风速"<<setw(10)<<"费用"<<setw(10)<<"状态"<<endl;
        outfile<<endl;
        for(int i=0;i<this->S->tcpClientSocketList.size();i++){
            outfile<<S->tcpClientSocketList[i]->C->roomNum<<setw(10)<<S->tcpClientSocketList[i]->C->targetTmp<<setw(10)<<S->tcpClientSocketList[i]->C->roomTmp<<setw(11)<<S->tcpClientSocketList[i]->C->windSpeed<<setw(11)<<S->tcpClientSocketList[i]->C->fee<<setw(10)<<S->tcpClientSocketList[i]->C->isServed<<endl;

        }
        outfile<<endl;
        outfile.close();
    }


}

void Host::Update(){} // 刷新数据库

void Host::Del(){
    QVector<Customer*>::iterator it1;
    qDebug()<<"Del Cus.size"<<Cus.size();
    if(Cus.size()>0){
        it1=Cus.begin();
        for(;it1!=Cus.end();){
            qDebug()<<"Del_satisfied()"<<(*it1)->satisfied();
            if((*it1)->satisfied()){
               (*it1)->isServed=false;
                (*it1)->Satisfy=true;
                (*it1)->t->stop();
                (*it1)->socket_cus->SetQjson2((*it1)->isServed,(*it1)->roomNum,(*it1)->roomTmp,(*it1)->Kwh,(*it1)->fee);
                it1=Cus.erase(it1);
                qDebug()<<"Del_成功房间号："<<(*it1)->roomNum;


            }
            else it1++;
        }
    }

}
/*调度策略  优先级+服务时间替换(时间片)   */
//先判断风速，替换最低的，若是最低的都相等，则替换最低当中服务时间最长的
void Host::Dispatch(int no) {
    QVector<Customer*>::iterator it1,it2,it3;
    QVector<Customer*> Cus2;
    qDebug()<<"Dispatch_Cus"<<Cus.size();
    if(Cus.size()>0){
        it1 = Cus.begin();
        int tepnum=0,tepnum2=0;
        int min_temp = Cus[0]->windSpeed;
        qDebug()<<"找风速前";
        for (int i = 0; i < Cus.size()&&it1!=Cus.end(); i++,it1++) {
            if (Cus[i]->windSpeed < min_temp) {
                min_temp = Cus[i]->windSpeed;  //找出最小风速
                tepnum = i;
                it2 = it1;//最小风速的迭代器
            }

        }
        qDebug()<<"Cus2加入前";
        for (int i = 0; i < Cus.size(); i++){
            if(Cus[i]->windSpeed==min_temp){
                Cus2.push_back(Cus[i]);
            }
        }
        qDebug()<<"进入找最长服务时间前";
        if(Cus2.size()>1){                               
            int  max_time = Cus2[0]->time_;
            it1=Cus2.begin();
            for (int i = 0; i < Cus2.size()&&it1!=Cus2.end(); i++,it1++){
                if (Cus2[i]->time_ >= max_time) {
                    max_time = Cus2[i]->time_;  //找出最长服务时间
                    tepnum2 = i;
                    it3 = it1;
                }
            }
            qDebug()<<"重找下标前"; //bug 出在这下面
             QVector<Customer*>::iterator itt,itt2;
             itt=Cus.begin();
             int time_temp;
            for(int jj=0 ; jj < Cus.size()&&itt!=Cus.end();jj++,itt++){
                qDebug()<<"time_"<<Cus[jj]->time_<<Cus[jj]->roomNum<<"号";
                qDebug()<<"Cus2wind"<<Cus2[tepnum2]->windSpeed;
                if(Cus[jj]->windSpeed==Cus2[tepnum2]->windSpeed){
                    if(max_time==Cus[jj]->time_){
                        time_temp=jj;
                        itt2=itt;
                        qDebug()<<"time_"<<Cus[jj]->time_<<Cus[jj]->roomNum<<"号";
                    }

                }
            }


            Cus[time_temp]->isServed=false;
            qDebug()<<Cus[time_temp]->roomNum<<"号房间被挂—Dispatch";
            Cus[time_temp]->time_=0;
            Cus[time_temp]->socket_cus->SetQjson2(Cus[time_temp]->isServed,Cus[time_temp]->roomNum,Cus[time_temp]->roomTmp,Cus[time_temp]->Kwh,Cus[time_temp]->fee);
            Cus[time_temp]->t->stop();
            itt2 = Cus.erase(itt2);
            S->tcpClientSocketList[no]->C->isServed=true;
            this->Cus.push_back(S->tcpClientSocketList[no]->C);
            S->tcpClientSocketList[no]->C->t->start(S->tcpClientSocketList[no]->C->Feedback()*1000);
            S->tcpClientSocketList[no]->SetQjson2(S->tcpClientSocketList[no]->C->isServed,S->tcpClientSocketList[no]->C->roomNum,S->tcpClientSocketList[no]->C->roomTmp,S->tcpClientSocketList[no]->C->Kwh,S->tcpClientSocketList[no]->C->fee);

        }
        else{
            Cus[tepnum]->isServed=false;
            Cus[tepnum]->socket_cus->SetQjson2(Cus[tepnum]->isServed,Cus[tepnum]->roomNum,Cus[tepnum]->roomTmp,Cus[tepnum]->Kwh,Cus[tepnum]->fee);
            qDebug()<<Cus[tepnum]->roomNum<<"号房间被挂—Dispatch";
            Cus[tepnum]->time_=0;
            Cus[tepnum]->t->stop();
            it2 = Cus.erase(it2);
            S->tcpClientSocketList[no]->C->isServed=true;
            this->Cus.push_back(S->tcpClientSocketList[no]->C);
            S->tcpClientSocketList[no]->C->t->start(S->tcpClientSocketList[no]->C->Feedback()*1000);//计时开始
            S->tcpClientSocketList[no]->SetQjson2(S->tcpClientSocketList[no]->C->isServed,S->tcpClientSocketList[no]->C->roomNum,S->tcpClientSocketList[no]->C->roomTmp,S->tcpClientSocketList[no]->C->Kwh,S->tcpClientSocketList[no]->C->fee);
        }

    }


}
void Host::Run(){
        if(this->S->tcpClientSocketList.size()>0&&this->S->tcpClientSocketList.size()<=4){
            this->Add2();//对于Cus.size<3的情况 直接加入调度队列 以及 新来的也能直接调度
            //需要进行判断是否isSatisfied的情况 还是放在解析 或者调度时候判断？
            this->Print();
            this->Del();//服务完的就剔除服务队列
            if(Cus.size()==3&&this->S->tcpClientSocketList.size()==4){
                for(int i=0;i<this->S->tcpClientSocketList.size();i++){

                    if(this->S->tcpClientSocketList[i]->C->flag){
                        qDebug()<<S->tcpClientSocketList[i]->C->roomNum<<"加入调度";
                        this->S->tcpClientSocketList[i]->C->flag=false;
                        this->Dispatch(i);
                        this->S->tcpClientSocketList[i]->SetQjson2(S->tcpClientSocketList[i]->C->isServed,S->tcpClientSocketList[i]->C->roomNum,S->tcpClientSocketList[i]->C->roomTmp,S->tcpClientSocketList[i]->C->Kwh,S->tcpClientSocketList[i]->C->fee);//被挂起到一度后可以调度
                    }

                }
            }

        }

}
void Host::setmode(int mode_){
    this->mode=mode_;
}

void Host::setdefTargetTmp(int defTargetTmp_){
    this->defTargetTmp=defTargetTmp_;
}
void Host::setlowestTmp(int lowestTmp_){
    this->lowestTmp=lowestTmp_;
}

void Host::sethighestTmp(int highestTmp_){
    this->highestTmp=highestTmp_;
}
