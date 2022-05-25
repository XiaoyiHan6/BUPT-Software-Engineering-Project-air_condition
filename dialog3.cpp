#include "dialog3.h"
#include "ui_dialog3.h"
#include "dialog2.h"

Dialog3::Dialog3(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog3)
{
    ui->setupUi(this);
}

Dialog3::~Dialog3()
{
    delete ui;
}

void Dialog3::on_pushButton_7_clicked()
{
    this->hide();
    //log->show();
}
