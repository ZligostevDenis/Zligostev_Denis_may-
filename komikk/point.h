#ifndef POINT_H // Проверка, не был ли этот файл уже подключен
#define POINT_H

#include <QGraphicsItem> // Подключаем класс QGraphicsItem для работы с графическими элементами
#include <QGraphicsEllipseItem> // Подключаем класс для создания эллипсов
#include <QGraphicsTextItem> // Подключаем класс для создания текстовых элементов
#include <QGraphicsLineItem> // Подключаем класс для создания линий
#include <QBrush> // Подключаем класс для работы с кистями
#include <QPen> // Подключаем класс для работы с перьями
#include <QColor> // Подключаем класс для работы с цветами
#include <QFont> // Подключаем класс для работы со шрифтами
#include <QString> // Подключаем класс для работы со строками

#include <QDebug> // Подключаем для отладки

// Класс, описывающий вершину графа
class Point
{
public:
    unsigned int Number; // Номер вершины
    int X = 0, Y = 0; // Координаты вершины

    // Графические элементы, связанные с вершиной:
    QGraphicsEllipseItem* zone = nullptr; // Круг, обозначающий зону, в которой нельзя создавать другие вершины
    QGraphicsEllipseItem* point = nullptr; // Круг, отображающий саму вершину графа
    QGraphicsTextItem* nameOfTop = nullptr; // Текст с номером вершины, размещенный в центре круга

    // Конструктор класса
    Point(int x, int y, unsigned int number, int activeZone);

    ~Point(); // Деструктор класса
};

#endif // POINT_H // Завершение блока условного включения
