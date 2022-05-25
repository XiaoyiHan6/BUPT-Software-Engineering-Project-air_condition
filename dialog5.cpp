#include "dialog5.h"
#include "ui_dialog5.h"
#include "dialog2.h"

Dialog5::Dialog5(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog5)
{
    ui->setupUi(this);
}

Dialog5::~Dialog5()
{
    delete ui;
}

void Dialog5::on_pushButton_7_clicked()
{
    //Dialog2 *log=new Dialog2(this);
    this->hide();
    //log->show();
}

void Dialog5::display()
{
    for(int i=0;i<host->S->tcpClientSocketList.size();i++)
    {
        switch(host->S->tcpClientSocketList[i]->C->roomNum)
        {
           case 0:
            ui->textEdit_2->setText(QString::number(this->host->PowerNum[0]));
            ui->textEdit_3->setText(this->host->S->tcpClientSocketList[i]->C->starttime);
            ui->textEdit_5->setText(QString::number(this->host->S->tcpClientSocketList[i]->C->Kwh));
            break;
          case 1:
            ui->textEdit_6->setText(QString::number(this->host->PowerNum[1]));
            ui->textEdit_7->setText(this->host->S->tcpClientSocketList[i]->C->starttime);
            ui->textEdit_8->setText(QString::number(this->host->S->tcpClientSocketList[i]->C->Kwh));
            break;
          case 2:
            ui->textEdit_10->setText(QString::number(this->host->PowerNum[2]));
            ui->textEdit_11->setText(this->host->S->tcpClientSocketList[i]->C->starttime);
            ui->textEdit_12->setText(QString::number(this->host->S->tcpClientSocketList[i]->C->Kwh));
            break;
          case 3:
            ui->textEdit_14->setText(QString::number(this->host->PowerNum[3]));
            ui->textEdit_15->setText(this->host->S->tcpClientSocketList[i]->C->starttime);
            ui->textEdit_16->setText(QString::number(this->host->S->tcpClientSocketList[i]->C->Kwh));
            break;
        }
    }
}
