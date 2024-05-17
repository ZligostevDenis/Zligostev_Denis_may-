#ifndef NODE_H 
#define NODE_H

#include <QGraphicsItem> // Подключаем класс QGraphicsItem для создания графических элементов
#include "graph.h" // Подключаем заголовочный файл класса Graph
class graphVertex; // Объявляем класс graphVertex

// Класс Edge, наследуемый от QGraphicsItem
class Edge : public QGraphicsItem
{
public:
    Edge(graphVertex *sourceVert, graphVertex *destVert); // Конструктор класса

    ~Edge() override; // Деструктор класса
    graphVertex *sourceNode() const; // Метод для получения начальной вершины ребра
    graphVertex *destNode() const; // Метод для получения конечной вершины ребра
    void setContent(int); // Метод для установки содержимого ребра
    void adjust(); // Метод для корректировки положения ребра
    void setGraph(Graph*); // Метод для установки графа

protected:
    QRectF boundingRect() const override; // Метод для получения ограничивающего прямоугольника ребра
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override; // Метод для отрисовки ребра
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override; // Метод для обработки нажатия кнопки мыши на ребре
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override; // Метод для обработки отпускания кнопки мыши на ребре

private:
    graphVertex *source, *dest; // Указатели на начальную и конечную вершины ребра
    bool _pressed; // Флаг, указывающий, нажато ли ребро

    QPointF sourcePoint; // Координаты начальной точки ребра
    QPointF destPoint; // Координаты конечной точки ребра
    qreal arrowSize; // Размер стрелки ребра
    Graph *graph; // Указатель на объект графа
    QGraphicsItemGroup drawing; // Группа графических элементов, составляющих ребро

    QString content = "weight"; // Содержимое ребра (по умолчанию "weight")
};

#endif // NODE_H 
