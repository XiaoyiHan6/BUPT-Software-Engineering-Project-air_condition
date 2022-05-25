#include "dialog7.h"
#include "ui_dialog7.h"
#include "dialog2.h"

Dialog7::Dialog7(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog7)
{
    ui->setupUi(this);
}

Dialog7::~Dialog7()
{
    delete ui;
}

void Dialog7::on_pushButton_7_clicked()
{

    this->hide();
    //log->show();
}

void Dialog7::display()
{
    for(int i=0;i<host->S->tcpClientSocketList.size();i++)
    {

       switch(host->S->tcpClientSocketList[i]->C->roomNum)
        {
                  case 0:
                   ui->lineEdit->setText(QString::number(this->host->S->tcpClientSocketList[i]->C->Kwh));
                   break;
                  case 1:
                   ui->lineEdit_2->setText(QString::number(this->host->S->tcpClientSocketList[i]->C->Kwh));
                   break;
                  case 2:
                   ui->lineEdit_3->setText(QString::number(this->host->S->tcpClientSocketList[i]->C->Kwh));
                   break;
                  case 3:
                   ui->lineEdit_4->setText(QString::number(this->host->S->tcpClientSocketList[i]->C->Kwh));
                   break;
        }
    }
    return;
}
