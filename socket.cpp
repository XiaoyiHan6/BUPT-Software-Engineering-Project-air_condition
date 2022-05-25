#include "socket.h"
#include<QDebug>
#include<QMap>
#include<QTime>
TcpClientSocket::TcpClientSocket(QObject *parent)
{
    connect(this,SIGNAL(readyRead()),this,SLOT(dataReceived()));

 //   connect(this,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));
}
TcpClientSocket::~TcpClientSocket(){
     qDebug()<< "~TcpClientSocket" ;
    close();
}

bool TcpClientSocket::SetQjson1(int mode,bool isServed,double lowestTmp,double highestTmp,double defTargetTmp,double roomTmp)
{
    message.insert("isServed", isServed);
    message.insert("mode", mode);
    message.insert("lowestTmp", lowestTmp);
    message.insert("highestTmp", highestTmp);
    message.insert("targetTmp", defTargetTmp);
    message.insert("roomTmp", roomTmp);
    QJsonDocument document;
    document.setObject(message);
    byte= document.toJson(QJsonDocument::Compact);
    if( 0 >= WriteData(byte.data(), strlen(byte.data()) + 1) )
        qDebug()<< "TcpClientSocket::WriteData() SetQjson1 write data failed !" ;
    else
         qDebug()<< "SetQjson1 send  data: %s", byte.data();
}
bool TcpClientSocket::SetQjson2(bool isServed,int roomNum,double roomTmp,double Kwh,double fee){
    message.insert("isServed", isServed);

    message.insert("roomTmp", roomTmp);
    message.insert("Kwh", Kwh);
    message.insert("fee", fee);
    message.insert("roomNum", roomNum);
    QJsonDocument document;
    document.setObject(message);
    byte= document.toJson(QJsonDocument::Compact);
    if( 0 >= WriteData(byte.data(), strlen(byte.data()) + 1) )
         qDebug()<< "TcpClientSocket::WriteData() SetQjson2 write data failed !" ;
    else
         qDebug()<< "SetQjson2 send  data: %s"<< byte.data();
}
 bool TcpClientSocket::QBtoJ()
 {
     QJsonParseError json_error;
     QJsonDocument parse_doucment = QJsonDocument::fromJson(byte, &json_error);
     qDebug()<<byte;
     int windSpeed,roomNum,mode;
     double roomTmp,targetTmp,defRoomTmp;
     bool power,isServed;
     if(json_error.error == QJsonParseError::NoError)
     {
         if(parse_doucment.isObject())
         {
             message = parse_doucment.object();
             if(message.contains("windSpeed"))
             {
                 QJsonValue version_value = message.take("windSpeed");

                     int wind_temp= version_value.toVariant().toInt();
                     if(wind_temp==0||wind_temp==1||wind_temp==2)
                         windSpeed=wind_temp;

             }
             if(message.contains("roomNum"))
             {
                 QJsonValue version_value = message.take("roomNum");

                     int roomNum_temp = version_value.toVariant().toInt();
                     if(roomNum_temp==0||roomNum_temp==1||roomNum_temp==2||roomNum_temp==3)
                         roomNum=roomNum_temp;

            }
             if(message.contains("roomTmp"))
            {
                 QJsonValue version_value = message.take("roomTmp");
                 if(version_value.isDouble ())
                 {
                      roomTmp = version_value.toDouble();
                 }
            }
             if(message.contains("targetTmp"))
            {
                 QJsonValue version_value = message.take("targetTmp");
                 if(version_value.isDouble ())
                 {
                      targetTmp = version_value.toDouble();
                 }
            }
             if(message.contains("mode"))
            {
                 QJsonValue version_value = message.take("mode");

                    int   mode_temp = version_value.toVariant().toInt();
                    if(mode_temp==0||mode_temp==1)
                        mode=mode_temp;

            }
             if(message.contains("power"))
            {
                 QJsonValue version_value = message.take("power");
                 if(version_value.isBool ())
                 {
                      power = version_value.toBool();
                 }

            }
             if(message.contains("isServed"))
            {
                 QJsonValue version_value = message.take("isServed");
                 if(version_value.isBool ())
                 {
                      isServed = version_value.toBool();
                 }
            }
             if(message.contains("defRoomTmp"))
            {
                 QJsonValue version_value = message.take("defRoomTmp");
                 if(version_value.isDouble ())
                 {
                      defRoomTmp = version_value.toDouble();
                 }
            }
             //找到当前Cus2从机副本所对应的相同的ip,把解析出来的值赋值到找到的从机中
            if(power==true&&(this->C->power==false)){
               this->C->roomNum=roomNum;
               C->room_ip.insert(roomNum,this->socketDescriptor());
               this->host_socket->PowerNum[roomNum]+=1;
               qDebug()<<"roomTmp"<<roomTmp;
               qDebug()<<"roomNum"<<roomNum;
               this->C->roomTmp=roomTmp;
               this->C->windSpeed=windSpeed;
               this->C->targetTmp=targetTmp;
               this->C->power=power;
               qDebug()<<"targetTmp_setqjson1"<<targetTmp;
               //this->C->room_ip.insert(socketDescriptor,roomNum);
               //读入配置文件mode

               SetQjson1(this->C->mode,false,this->C->lowestTmp,this->C->highestTmp,this->C->defTargetTmp,roomTmp);

            }
            else{
                if(power==false){//解析到power要关机了
                    qDebug()<<"从机"<<roomNum<<"关机";
                    this->C->power=power;
                    this->C->t->stop();
                    emit disconnected(this->socketDescriptor());
                }
                else{
                    if(this->C->isServed==false){
                        //这里要加 当有新请求来时，也能将它从挂起队列中唤醒
                        if(this->C->windSpeed!=windSpeed){
                            int min_weend=host_socket->Cus[0]->windSpeed;
                            int count_weed=0,tempnum=0,tempnum1=0;
                            for(int i=1;i<this->host_socket->Cus.size();i++){
                                if(host_socket->Cus[i]->windSpeed<min_weend){
                                    min_weend=host_socket->Cus[i]->windSpeed;
                                    tempnum=i;
                                }
                            }
                            for(int i=0;i<this->host_socket->S->tcpClientSocketList.size();i++){
                                if(this->C->roomNum==this->host_socket->S->tcpClientSocketList[i]->C->roomNum){
                                     tempnum1=i;
                                     qDebug()<<"变化请求的房间"<<this->C->roomNum<<"号";
                                }

                            }
                            if(min_weend==this->C->windSpeed){
                                for(int i=0;i<this->host_socket->Cus.size();i++){
                                    if((i!=tempnum)&&windSpeed>=host_socket->Cus[i]->windSpeed){
                                        count_weed++;
                                    }

                                }
                                if(count_weed>0) this->host_socket->Dispatch(tempnum1);
                            }
                            else{
                                if(windSpeed>this->C->windSpeed){
                                    this->host_socket->Dispatch(tempnum1);
                                }

                            }
                        }

                        else{
                            this->C->count+=0.1;
                            qDebug()<<"count_"<<this->C->count<<"房号"<<this->C->roomNum;

                            if(this->C->count>=1){
                                this->C->count=0;
                                this->C->flag=true;
                            }
                        }

                    }

                    this->C->windSpeed=windSpeed;  //传来风速

                    this->C->targetTmp=targetTmp; //传来目标温度
                    this->C->roomTmp=roomTmp;
                    if(roomTmp==0) this->C->roomTmp=defRoomTmp;
                }


            }

        }
     }
 }

 QByteArray  TcpClientSocket::getbyte()
 {
     return byte;
 }


void TcpClientSocket::dataReceived()
{
    byte.resize( bytesAvailable());
    byte= readAll();
    if( byte.size() <= 0 ) {
         qDebug()<<"TcpClientSocket::dataReceived() read data failed !" ;
        return;
    }
    qDebug()<< "receive data: %s"<<byte.data() ;
    QBtoJ();

    //printf( "please input message: " );

   // QString str="get"; int i=1; int b=2
   // SetQjson(str,i,b);
/*    if( 0 >= WriteData(byte.data(), strlen(byte.data()) + 1) )
        printf( "TcpClientSocket::WriteData() write data failed !\n" );
    else
        printf( "send    data: %s\n", byte.data());*/


}
bool TcpClientSocket::WriteData( const char *data, qint64 len )
{
    if( NULL == data || len <= 0 )
        return false;
    qint64 ret = write( byte );
    if( 0 >= ret )
        return false;

  //  waitForBytesWritten(1000);                  // why ?

   // waitForReadyRead(1000);                     // why ?

    return true;
}

void TcpClientSocket::InitialC(){
    this->C=new Customer();
    C->socket_cus=this;
    C->power=false;
    //C->defRoomTmp=this->host_socket->defTargetTmp;
    C->mode=this->host_socket->mode;
    C->lowestTmp=this->host_socket->lowestTmp;
    C-> highestTmp=this->host_socket->highestTmp;
    C->defTargetTmp=this->host_socket->defTargetTmp;
    C->tt.start();//连接起始时间
    C->tt.currentTime();
    C->starttime=C->tt.currentTime().toString();
    C->flag=false;


}
