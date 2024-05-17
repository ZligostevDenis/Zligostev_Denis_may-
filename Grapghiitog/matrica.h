#ifndef MATRICA_H  
#define MATRICA_H

#include <QWidget> // Подключаем класс QWidget для создания виджета
#include "graph.h" // Подключаем заголовочный файл класса Graph
namespace Ui {
class Adjacency; // Объявляем класс Adjacency внутри пространства имен Ui
}

// Класс Adjacency, наследуемый от QWidget
class Adjacency : public QWidget
{
    Q_OBJECT // Макрос для использования сигналов и слотов

public:
    explicit Adjacency(QWidget *parent = nullptr); // Конструктор класса
    ~Adjacency(); // Деструктор класса
    void setAdj(QVector<QVector<int>>); // Метод для установки матрицы смежности
    void setSize(int); // Метод для установки размера матрицы
    void rebuild(QVector<QString>); // Метод для перестроения матрицы
    void setGraph(Graph*); // Метод для установки графа

private:
    Ui::Adjacency *ui; // Указатель на объект интерфейса
    QVector<QVector<int>> adj; // Матрица смежности
    int size; // Размер матрицы
    Graph *graph; // Указатель на объект графа
};

#endif // MATRICA_H 
