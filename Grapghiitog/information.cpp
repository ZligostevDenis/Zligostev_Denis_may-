#include "information.h" // Подключаем заголовочный файл диалогового окна
#include "ui_information.h" // Подключаем файл с описанием интерфейса

// Конструктор класса ShowInfo
ShowInfo::ShowInfo(QWidget *parent) :
    QDialog(parent), // Вызываем конструктор родительского класса QDialog
    ui(new Ui::ShowInfo) // Создаем объект интерфейса Ui::ShowInfo
{
    ui->setupUi(this); // Инициализируем интерфейс
}

// Деструктор класса ShowInfo
ShowInfo::~ShowInfo()
{
    delete ui; // Удаляем объект интерфейса
}

// Устанавливает текст в метку label
void ShowInfo::setInfo(QString res) {
    ui->label->setText(res); // Устанавливаем текст res в метку label
}

