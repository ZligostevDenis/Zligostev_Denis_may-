#ifndef AUTORISATION_H
#define AUTORISATION_H

#include <QDialog>
#include "mainwindow.h"
#include "sicret.h"
namespace Ui {
class Autorisation;
}

class Autorisation : public QDialog
{
    Q_OBJECT

public:
    explicit Autorisation(QWidget *parent = nullptr);
    ~Autorisation();


private slots:
    void on_pushButton_clicked();

private:
    Ui::Autorisation *ui;
    MainWindow *window;
    sicret *sicretwindow;
};

#endif // AUTORISATION_H
