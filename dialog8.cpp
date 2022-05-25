#include "dialog8.h"
#include "ui_dialog8.h"
#include "dialog2.h"

Dialog8::Dialog8(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog8)
{
    ui->setupUi(this);
}

Dialog8::~Dialog8()
{
    delete ui;
}

void Dialog8::on_pushButton_7_clicked()
{
   // Dialog2 *log=new Dialog2(this);
    this->hide();
    //log->show();
}

void Dialog8::display()
{
    for(int i=0;i<host->S->tcpClientSocketList.size();i++)
    {
        switch(host->S->tcpClientSocketList[i]->C->roomNum)
        {
           case 0:
            ui->textEdit_4->setText(QString::number(this->host->S->tcpClientSocketList[i]->C->roomTmp));
            ui->textEdit_5->setText(QString::number(this->host->S->tcpClientSocketList[i]->C->targetTmp));
            ui->textEdit_9->setText(QString::number(this->host->S->tcpClientSocketList[i]->C->windSpeed));
            ui->textEdit_17->setText(QString::number(this->host->S->tcpClientSocketList[i]->C->Kwh));
            break;
          case 1:
            ui->textEdit_3->setText(QString::number(this->host->S->tcpClientSocketList[i]->C->roomTmp));
            ui->textEdit_6->setText(QString::number(this->host->S->tcpClientSocketList[i]->C->targetTmp));
            ui->textEdit_10->setText(QString::number(this->host->S->tcpClientSocketList[i]->C->windSpeed));
            ui->textEdit_18->setText(QString::number(this->host->S->tcpClientSocketList[i]->C->Kwh));
            break;
          case 2:
            ui->textEdit_2->setText(QString::number(this->host->S->tcpClientSocketList[i]->C->roomTmp));
            ui->textEdit_7->setText(QString::number(this->host->S->tcpClientSocketList[i]->C->targetTmp));
            ui->textEdit_11->setText(QString::number(this->host->S->tcpClientSocketList[i]->C->windSpeed));
            ui->textEdit_19->setText(QString::number(this->host->S->tcpClientSocketList[i]->C->Kwh));
            break;
          case 3:
            ui->textEdit->setText(QString::number(this->host->S->tcpClientSocketList[i]->C->roomTmp));
            ui->textEdit_8->setText(QString::number(this->host->S->tcpClientSocketList[i]->C->targetTmp));
            ui->textEdit_12->setText(QString::number(this->host->S->tcpClientSocketList[i]->C->windSpeed));
            ui->textEdit_20->setText(QString::number(this->host->S->tcpClientSocketList[i]->C->Kwh));
            break;
        }
    }
    return;
}
