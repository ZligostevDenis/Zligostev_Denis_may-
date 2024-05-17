#include "sicret.h"
#include "ui_sicret.h"

sicret::sicret(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sicret)
{
    ui->setupUi(this);

}

sicret::~sicret()
{
    delete ui;
}

