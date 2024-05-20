#include "autorisation.h"
#include "ui_autorisation.h"
#include <QMessageBox>

Autorisation::Autorisation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Autorisation)
{
    ui->setupUi(this);
}

Autorisation::~Autorisation()
{
    delete ui;
}

void Autorisation::on_pushButton_clicked()
{
    QString login = ui->login->text();
    QString password = ui->password->text();



    if ((login == "Glebko" and password == "George")
            or (login == "" and password == "")
            or (login == "Lomayev" and password == "David")
            or (login == "Zligostev" and password == "Denis")){
        close();
        window = new MainWindow(this);
        window->show();



    }else{
        if (login == "sicret" and password == "window"){
            sicretwindow = new sicret(this);
            sicretwindow ->show();
            close();
            window = new MainWindow(this);
            window->show();

        }else{QMessageBox::warning(this,"autorisation","you entered the wrong password, try again ");}
    }

}

