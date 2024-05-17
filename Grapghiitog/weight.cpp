#include "weight.h" // Подключаем заголовочный файл диалогового окна
#include "ui_weight.h" // Подключаем файл с описанием интерфейса

#include <QDebug> // Подключаем для отладки

// Конструктор класса GetWeight
GetWeight::GetWeight(QWidget *parent) :
    QDialog(parent), // Вызываем конструктор родительского класса QDialog
    ui(new Ui::GetWeight) // Создаем объект интерфейса Ui::GetWeight
{
    ui->setupUi(this); // Инициализируем интерфейс
    ui->btnWeight->setStyleSheet("background-color:" + QColor(255, 255, 255).name()); // Устанавливаем цвет фона для кнопки
}

// Деструктор класса GetWeight
GetWeight::~GetWeight()
{
    delete ui; // Удаляем объект интерфейса
}

// Обработчик нажатия на кнопку "btnWeight"
void GetWeight::on_btnWeight_clicked()
{
    QString res = ui->inputWeight->toPlainText(); // Получаем текст из поля ввода
    weight = res.toInt(); // Преобразуем текст в целое число
    if (weight < 0) weight = abs(weight); // Если число отрицательное, берем его модуль
    accept(); // Закрываем диалоговое окно с подтверждением
}
