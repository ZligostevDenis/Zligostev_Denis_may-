#include "point.h" // Подключение заголовочного файла класса Point

// Конструктор класса Point
Point::Point(int x, int y, unsigned int number, int activeZone)
{
    Number = number; // Присвоение номера вершины
    X = x; // Присвоение координаты X
    Y = y; // Присвоение координаты Y

    // Создание графического представления вершины (круг):
    point = new QGraphicsEllipseItem(X - 30, Y - 30, 60, 60);
    point->setBrush(QColor(0, 0, 0)); // Установка цвета заливки круга
    point->setPen(QPen(QColor(0, 0, 0))); // Установка цвета границы круга

    // Создание текстового элемента для отображения номера вершины:
    nameOfTop = new QGraphicsTextItem(QString::number(Number));

    // Установка позиции текстового элемента в зависимости от длины номера вершины:
    if (Number >= 10) {
        nameOfTop->setPos(X - 9, Y - 10);
    } else {
        nameOfTop->setPos(X - 6, Y - 10);
    }

    // Создание зоны вокруг вершины, в которой нельзя создавать другие вершины:
    zone = new QGraphicsEllipseItem(X - 25, Y - 25, 50, 50);
    zone->setBrush(Qt::NoBrush); // Установка прозрачной заливки зоны

    // Установка видимости границы зоны в зависимости от параметра activeZone:
    if (activeZone) {
        zone->setPen(QPen(Qt::black)); // Граница зоны видна
    } else {
        zone->setPen(QPen(Qt::NoPen)); // Граница зоны не видна
    }
}

// Деструктор класса Point
Point::~Point()
{
    delete point; // Удаление графического представления вершины
    delete nameOfTop; // Удаление текстового элемента
    delete zone; // Удаление зоны
}
