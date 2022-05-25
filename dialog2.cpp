#include "dialog2.h"
#include "ui_dialog2.h"
#include "dialog9.h"
#include "dialog3.h"
#include "dialog7.h"
#include "dialog5.h"
#include "dialog8.h"
#include"host.h"
#include<QString>
#include<QTimer>
#include<QTime>
#include<QDateTime>

Dialog2::Dialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog2)
{
    ui->setupUi(this);
    QTimer *timer =new QTimer(this);
    //在界面显示时间
    connect(timer,SIGNAL(timeout()),this,SLOT(showTime()));
            timer->start(500);//启动定时器


}

Dialog2::~Dialog2()
{
    delete ui;
}



void Dialog2::on_pushButton_7_clicked()
{


    this->hide();

}

void Dialog2::on_pushButton_3_clicked()
{
    Dialog8 *log=new Dialog8(this);
   // this->hide();
    log->host=this->host;
    log->show();
    log->display();
}

void Dialog2::on_pushButton_2_clicked()
{
    Dialog5 *log=new Dialog5(this);
    //this->hide();
    log->host=this->host;
    log->show();
    log->display();
}

void Dialog2::on_pushButton_clicked()
{
    Dialog7 *log=new Dialog7(this);
    //this->hide();
    log->host=this->host;
    log->show();
    log->display();
}

void Dialog2::on_pushButton_4_clicked()
{
    Dialog3 *log=new Dialog3(this);
    //this->hide();
    log->host=this->host;
    log->show();
}



void Dialog2::display(){

    ui->label_2->setText(QString::number(this->host->mode));
    ui->label_4->setText(QString::number(this->host->defTargetTmp));
    ui->label_6->setText(QString::number(this->host->highestTmp));
    ui->label_8->setText(QString::number(this->host->lowestTmp));

}

void Dialog2::showTime(){

    QDateTime timer=QDateTime::currentDateTime();//当前时间
    QString txTime=timer.toString("hh:mm:ss");
    ui->lcdNumber->display(txTime);//LCD时间
}

