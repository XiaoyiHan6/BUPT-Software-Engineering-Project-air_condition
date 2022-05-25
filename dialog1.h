#ifndef DIALOG1_H
#define DIALOG1_H

#include <QDialog>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QTextEdit>
#include<QString>
#include <conio.h>
#include<QPlainTextEdit>
#include"host.h"
namespace Ui {
class Dialog1;
}

class Dialog1 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog1(QWidget *parent = 0);
    ~Dialog1();
    QLineEdit *defTargetTmpLineEdit;
    QGridLayout *mainLayout;
    Host *host;

private slots:

    void on_commandLinkButton_clicked();

    void on_pushButton_clicked();
    double on_plainTextEdit_3_textChanged();
    int on_plainTextEdit_2_textChanged();
    double on_plainTextEdit_4_textChanged();
    double on_plainTextEdit_textChanged();

private:
    Ui::Dialog1 *ui;
    QPlainTextEdit * plainTextEdit;
    QPlainTextEdit * plainTextEdit_2;
    QPlainTextEdit * plainTextEdit_3;
    QPlainTextEdit * plainTextEdit_4;
    QString  defTargetTmp;
    QString  mode;
    QString lowestTmp;
    QString  highestTmp;
};

#endif // DIALOG1_H
