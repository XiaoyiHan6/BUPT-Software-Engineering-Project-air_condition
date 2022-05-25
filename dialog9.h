#ifndef DIALOG9_H
#define DIALOG9_H

#include <QDialog>
#include"host.h"
namespace Ui {
class Dialog9;
}

class Dialog9 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog9(QWidget *parent = 0);
    ~Dialog9();
    Host *host;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::Dialog9 *ui;
};

#endif // DIALOG9_H
