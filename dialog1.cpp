#include "dialog1.h"
#include "ui_dialog1.h"
#include "dialog9.h"
#include "mainwindow.h"

#include <QMessageBox>
#include <QHostInfo>
#include"host.h"
#include "server.h"
#include<QTime>

Dialog1::Dialog1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog1)
{
    ui->setupUi(this);
  //  mainLayout->addWidget(defTargetTmpLineEdit,2,1);
    //connect(this,SIGNAL(key_hit()),SLOT(on_plainTextEdit_textChanged()));
}

Dialog1::~Dialog1()
{
    delete ui;
}

void Dialog1::on_commandLinkButton_clicked()
{
    MainWindow *log=new MainWindow(this);
    this->hide();
    log->show();
}


double Dialog1::on_plainTextEdit_textChanged(){

   defTargetTmp=ui->plainTextEdit->toPlainText();
   double defTargetTmp1=defTargetTmp.toDouble();
   return defTargetTmp1;
}


int Dialog1::on_plainTextEdit_2_textChanged()
{

    mode=ui->plainTextEdit_2->toPlainText();
    int mode1=mode.toInt();
    return mode1;
}

double Dialog1::on_plainTextEdit_4_textChanged()
{
    lowestTmp=ui->plainTextEdit_4->toPlainText();
    double lowestTmp1=lowestTmp.toDouble();
    if(lowestTmp1>=18&&lowestTmp1<=25)
    return  lowestTmp1;

}

double Dialog1::on_plainTextEdit_3_textChanged()
{

    highestTmp=ui->plainTextEdit_3->toPlainText();
    double highestTmp1=highestTmp.toDouble();
    if(highestTmp1>=18&&highestTmp1<=25)
    return  highestTmp1;
}

void Dialog1::on_pushButton_clicked()
{

   // Dialog9 *log=new Dialog9(this);

    this->hide();
    host->setmode(this->on_plainTextEdit_2_textChanged());
    host->setdefTargetTmp(this->on_plainTextEdit_textChanged());
    host->setlowestTmp(this->on_plainTextEdit_4_textChanged());
    host->sethighestTmp(this->on_plainTextEdit_3_textChanged());
    qDebug()<<"host.mode"<<host->mode<<" "<<"defTargetTmp"<<host->defTargetTmp;
    qDebug()<<host->S->tcpClientSocketList.size();
    //host->Add();//将最初加入的客户端指针加入vector调度





}

