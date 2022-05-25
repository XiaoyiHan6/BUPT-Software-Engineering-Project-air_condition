#ifndef DIALOG2_H
#define DIALOG2_H
#include <QLabel>
#include <QDialog>
#include"host.h"
namespace Ui {
class Dialog2;
}

class Dialog2 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog2(QWidget *parent = 0);
    ~Dialog2();
    Host *host;
    void display();

private slots:

    void on_pushButton_7_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void showTime();//显示时间

private:
    Ui::Dialog2 *ui;
    QLabel Lable_2;
    QLabel Lable_4;
    QLabel Lable_6;
    QLabel Lable_8;
};

#endif // DIALOG2_H
