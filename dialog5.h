#ifndef DIALOG5_H
#define DIALOG5_H

#include <QDialog>
#include"host.h"
namespace Ui {
class Dialog5;
}

class Dialog5 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog5(QWidget *parent = 0);
    ~Dialog5();
    Host *host;
    void display();
private slots:
    void on_pushButton_7_clicked();

private:
    Ui::Dialog5 *ui;
};

#endif // DIALOG5_H
