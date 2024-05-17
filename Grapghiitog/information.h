#ifndef INFORMATION_H 
#define INFORMATION_H

#include <QDialog> // Подключаем класс QDialog для создания диалогового окна

namespace Ui {
class ShowInfo; // Объявляем класс ShowInfo внутри пространства имен Ui
}

// Класс ShowInfo, наследуемый от QDialog
class ShowInfo : public QDialog
{
    Q_OBJECT // Макрос для использования сигналов и слотов

public:
    explicit ShowInfo(QWidget *parent = nullptr); // Конструктор класса
    ~ShowInfo(); // Деструктор класса
    void setInfo(QString); // Метод для установки информации в диалоговом окне

private:
    Ui::ShowInfo *ui; // Указатель на объект интерфейса
};

#endif // INFORMATION_H 
