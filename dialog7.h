#ifndef DIALOG7_H
#define DIALOG7_H

#include <QDialog>
#include"host.h"
namespace Ui {
class Dialog7;
}

class Dialog7 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog7(QWidget *parent = 0);
    ~Dialog7();
    Host *host;
    void display();
private slots:
    void on_pushButton_7_clicked();
private:
    Ui::Dialog7 *ui;
};

#endif // DIALOG7_H
