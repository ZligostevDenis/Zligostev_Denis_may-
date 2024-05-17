#include "graphvertex.h"

#include <QFontDatabase> // Подключаем для работы со шрифтами

// Конструктор класса graphVertex
graphVertex::graphVertex(int num) {
    this->num = num; // Устанавливаем номер вершины
    _pressed = false; // Изначально вершина не нажата
    // Устанавливаем флаги для вершины:
    setFlag(ItemIsSelectable);  // Вершина может быть выбрана
    setFlag(ItemIsMovable); // Вершина может быть перемещена
    setFlag(ItemSendsGeometryChanges); // Вершина сообщает об изменениях геометрии
}

// Деструктор класса graphVertex
graphVertex::~graphVertex() {
    // Удаляем все ребра, связанные с этой вершиной
    while (!edgeList.isEmpty())
        delete edgeList.takeFirst();
    graph->eraseVertex(num); // Удаляем вершину из графа
}

// Возвращает ограничивающий прямоугольник вершины
QRectF graphVertex::boundingRect() const {
    return shape().boundingRect(); // Возвращаем ограничивающий прямоугольник фигуры вершины
}

// Возвращает true, если вершина нажата, иначе false
bool graphVertex::pressed() const {
    return _pressed;
}

// Устанавливает состояние нажатия вершины
void graphVertex::setPressed(bool pressed) {
    _pressed = pressed;
    update(); // Перерисовываем вершину
}

// Возвращает текст, отображаемый внутри вершины
QString graphVertex::getContent() {
    return content;
}

// Устанавливает граф, которому принадлежит вершина
void graphVertex::setGraph(Graph *graph) {
    this->graph = graph;
}

// Возвращает номер вершины
int graphVertex::getNum() {
    return num;
}

// Возвращает фигуру вершины (круг)
QPainterPath graphVertex::shape() const {
    QPainterPath path;
    path.addEllipse(-RADIUS, -RADIUS, 2 * RADIUS, 2 * RADIUS); // Создаем эллипс с центром в (0, 0) и радиусом RADIUS
    return path;
}

// Рисует вершину на сцене
void graphVertex::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget* widget) {
    QBrush brush(Qt::green); // Создаем кисть синего цвета
    if (pressed()) brush.setColor(QColor(152, 255, 152)); // Если вершина нажата, меняем цвет на светло зеленый
    else brush.setColor(QColor(255, 255, 255)); // Иначе цвет белый
    painter->setBrush(brush); // Устанавливаем кисть
    painter->setPen(QPen(pressed() ? QColor(0,0, 0) : QColor(0, 0, 0), 2)); // Устанавливаем цвет и толщину пера в зависимости от состояния нажатия
    painter->drawEllipse(-RADIUS, -RADIUS, 2 * RADIUS, 2 * RADIUS); // Рисуем круг
    content = QString::number(num); // Формируем текст для отображения номера вершины
    painter->drawText(boundingRect(), Qt::AlignCenter, content); // Рисуем текст по центру вершины
}

// Обрабатывает изменения состояния вершины
QVariant graphVertex::itemChange(GraphicsItemChange change, const QVariant &value) {
    switch (change) {
    case ItemPositionHasChanged: // Если изменилась позиция вершины
        foreach (Edge *edge, edgeList) // Для каждого ребра, связанного с вершиной
            edge->adjust(); // Корректируем положение ребра
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value); // Возвращаем результат обработки изменения
}

// Обработчик нажатия кнопки мыши на вершине
void graphVertex::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    _pressed = true; // Устанавливаем состояние нажатия
    update(); // Перерисовываем вершину
    QGraphicsItem::mousePressEvent(event); // Вызываем обработчик нажатия родительского класса
}

// Обработчик отпускания кнопки мыши на вершине
void graphVertex::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    _pressed = false; // Сбрасываем состояние нажатия
    update(); // Перерисовываем вершину
    QGraphicsItem::mouseReleaseEvent(event); // Вызываем обработчик отпускания родительского класса
}

// Добавляет ребро к вершине
void graphVertex::addEdge(Edge *edge) {
    edgeList << edge; // Добавляем ребро в список ребер вершины
    edge->adjust(); // Корректируем положение ребра
}

// Удаляет ребро из вершины
void graphVertex::removeEdge(Edge *edge) {
    edgeList.removeOne(edge); // Удаляем ребро из списка ребер вершины
}
