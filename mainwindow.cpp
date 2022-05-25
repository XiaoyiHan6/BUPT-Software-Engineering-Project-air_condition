#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog1.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Dialog1 *log=new Dialog1(this);
    this->hide();




    log->show();

}
