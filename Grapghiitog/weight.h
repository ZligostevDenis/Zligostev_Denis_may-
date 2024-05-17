#ifndef WEIGHT_H 
#define WEIGHT_H

#include <QDialog> // Подключаем класс QDialog для создания диалогового окна

namespace Ui {
class GetWeight; // Объявляем класс GetWeight внутри пространства имен Ui
}

// Класс GetWeight, наследуемый от QDialog
class GetWeight : public QDialog
{
    Q_OBJECT // Макрос для использования сигналов и слотов

public:
    explicit GetWeight(QWidget *parent = nullptr); // Конструктор класса
    ~GetWeight(); // Деструктор класса

    int weight = 1; // Вес ребра (по умолчанию 1)

signals:
    void sendWeight(QString); // Сигнал для отправки веса ребра

private slots:
    void on_btnWeight_clicked(); // Слот для обработки нажатия кнопки "btnWeight"

private:
    Ui::GetWeight *ui; // Указатель на объект интерфейса
};

#endif // WEIGHT_H 
