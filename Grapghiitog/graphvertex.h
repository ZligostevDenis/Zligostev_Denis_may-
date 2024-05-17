#ifndef GRAPHVERTEX_H
#define GRAPHVERTEX_H

// Включаем необходимые библиотеки
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>

#include "node.h"
// Определение константы размера узла
static const int RADIUS = 20;

// Класс вершины графа, наследующийся от класса QGraphicsItem
class graphVertex : public QGraphicsItem
{
    // Объявляем дружественные функции из класса Edge (ребер графа)
    friend Edge::Edge(graphVertex *sourceVert, graphVertex *destVert);
    friend Edge::~Edge();
public:
    // Конструктор вершины графа
    graphVertex(int);
    // Деструктор вершины графа
    ~graphVertex();
    // Получение списка ребер, соединенных с данной вершиной
    QList<Edge *> edges() const;
    // Возвращает прямоугольник, ограничивающий вершину
    QRectF boundingRect() const override;
    // Возвращает путь рисования вершины
    QPainterPath shape() const override;
    // Отрисовка вершины
    void paint(QPainter * painter, const QStyleOptionGraphicsItem *option, QWidget* widget) override;
    // Проверка нажатия на вершину
    bool pressed() const;
    // Установка флага нажатия на вершину
    void setPressed(bool pressed);
    // Получение содержимого вершины (метки)
    QString getContent();
    // Установка графа, к которому принадлежит вершина
    void setGraph(Graph*);
    // Получение номера вершины
    int getNum();
protected:
    // Обработка изменений состояния вершины
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    // Обработка события нажатия мыши на вершину
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    // Обработка события отпускания мыши на вершине
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    // Добавление ребра к вершине
    void addEdge(Edge *edge);
    // Удаление ребра из вершины
    void removeEdge(Edge *edge);
private:
    // Список ребер, соединенных с данной вершиной
    QList<Edge *> edgeList;

    // Флаг нажатия на вершину
    bool _pressed;
    // Группа графических элементов, представляющая вершину
    QGraphicsItemGroup *drawing;
    // Граф, к которому принадлежит вершина
    Graph *graph;
    // Номер вершины
    int num = 0;
    // Метка вершины (содержимое)
    QString content = "V";


};
#endif // GRAPHVERTEX_H
