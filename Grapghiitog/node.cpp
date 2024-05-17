#include "node.h" // Подключаем заголовочный файл ребра
#include "graphvertex.h" // Подключаем заголовочный файл вершины графа

#include <qmath.h> // Подключаем математические функции
#include <QPainter> // Подключаем для рисования
#include <QGraphicsSceneMouseEvent> // Подключаем для обработки событий мыши
#include "weight.h" // Подключаем диалоговое окно для ввода веса

// Конструктор класса Edge
Edge::Edge(graphVertex *sourceNode, graphVertex *destNode)
    : arrowSize(10) // Инициализируем размер стрелки
{
    setFlag(ItemIsSelectable); // Делаем ребро выбираемым
    source = sourceNode; // Запоминаем исходную вершину
    dest = destNode; // Запоминаем конечную вершину
    // Добавляем ребро в списки ребер исходной и конечной вершин
    source->addEdge(this);
    dest->addEdge(this);
    adjust(); // Выравниваем ребро
}

// Деструктор класса Edge
Edge::~Edge()
{
    // Удаляем ребро из списков ребер исходной и конечной вершин
    source->removeEdge(this);
    dest->removeEdge(this);
    // Удаляем ребро из графа
    int node1 = source->getNum(), node2 = dest->getNum();
    graph->eraseEdge(node1, node2);
}

// Метод для получения исходной вершины
graphVertex *Edge::sourceNode() const
{
    return source;
}

// Метод для получения конечной вершины
graphVertex *Edge::destNode() const
{
    return dest;
}

// Метод для установки веса ребра
void Edge::setContent(int num)
{
    content = QString::number(num); // Преобразуем число в строку
}

// Метод для выравнивания ребра
void Edge::adjust()
{
    if (!source || !dest) // Если исходная или конечная вершина не установлена, выходим
        return;

    QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0)); // Создаем линию между вершинами
    qreal length = line.length(); // Получаем длину линии

    prepareGeometryChange(); // Подготавливаем изменение геометрии

    // Если длина линии больше 20, рассчитываем смещение для стрелок
    if (length > qreal(20.)) {
        QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
        sourcePoint = line.p1() + edgeOffset; // Рассчитываем координаты начала стрелки у исходной вершины
        destPoint = line.p2() - edgeOffset; // Рассчитываем координаты конца стрелки у конечной вершины
    } else { // Если линия короткая, стрелки рисуем в одной точке
        sourcePoint = destPoint = line.p1();
    }
}

// Метод для установки графа, которому принадлежит ребро
void Edge::setGraph(Graph *graph)
{
    this->graph = graph;
}

// Метод для получения ограничивающего прямоугольника ребра
QRectF Edge::boundingRect() const
{
    if (!source || !dest) // Если исходная или конечная вершина не установлена, возвращаем пустой прямоугольник
        return QRectF();

    qreal penWidth = 5; // Толщина линии ребра
    qreal extra = (penWidth + arrowSize) / 2.0; // Дополнительное пространство для стрелок

    // Возвращаем прямоугольник, который включает линию и стрелки
    return QRectF(sourcePoint,
                  QSizeF(destPoint.x() - sourcePoint.x(), destPoint.y() - sourcePoint.y()))
        .normalized().adjusted(-extra, -extra, extra, extra);
}

// Метод для рисования ребра
void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!source || !dest) // Если исходная или конечная вершина не установлена, выходим
        return;

    QLineF line(sourcePoint, destPoint); // Создаем линию между вершинами
    if (qFuzzyCompare(line.length(), qreal(0.))) // Если длина линии равна 0, выходим
        return;
    // Устанавливаем цвет линии в зависимости от того, нажато ли ребро
    if (!_pressed) painter->setPen(QPen(QColor(0, 0, 0), 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    else painter->setPen(QPen(QColor(0, 0, 0), 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line); // Рисуем линию
    painter->drawText((sourcePoint*0.8+destPoint)/2, content); // Рисуем вес ребра

    // Рассчитываем угол наклона линии
    double angle = std::atan2(-line.dy(), line.dx());

    // Рассчитываем координаты точек для стрелок
    QPointF sourceArrowP1 = sourcePoint + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                                  cos(angle + M_PI / 3) * arrowSize);
    QPointF sourceArrowP2 = sourcePoint + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                                  cos(angle + M_PI - M_PI / 3) * arrowSize);
    QPointF destArrowP1 = destPoint + QPointF(sin(angle - M_PI / 3) * arrowSize,
                                              cos(angle - M_PI / 3) * arrowSize);
    QPointF destArrowP2 = destPoint + QPointF(sin(angle - M_PI + M_PI / 3) * arrowSize,
                                              cos(angle - M_PI + M_PI / 3) * arrowSize);

    painter->setBrush(Qt::black); // Устанавливаем черный цвет для заливки
    // Рисуем стрелки
    painter->drawPolygon(QPolygonF() << line.p1() << sourceArrowP1 << sourceArrowP2);
    painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
}

// Обработчик нажатия кнопки мыши на ребре
void Edge::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::RightButton){ // Если нажата правая кнопка мыши
        int vert1 = source->getNum(); // Получаем индекс исходной вершины
        int vert2 = dest->getNum(); // Получаем индекс конечной вершины
        GetWeight gw; int result; // Создаем диалоговое окно для ввода веса
        if (gw.exec()) result = gw.weight; // Если пользователь ввел вес, сохраняем его
        // Обновляем вес ребра в графе
        graph->eraseEdge(vert1, vert2);
        graph->InsertEdge(vert1, vert2, result);
        content = QString::number(result); // Обновляем вес ребра в объекте Edge
    }
    _pressed = true; // Помечаем ребро как нажатое
    update(); // Перерисовываем ребро
    QGraphicsItem::mousePressEvent(event); // Вызываем обработчик нажатия кнопки мыши родительского класса
}

// Обработчик отпускания кнопки мыши на ребре
void Edge::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    _pressed = false; // Снимаем пометку "нажато"
    update(); // Перерисовываем ребро
    QGraphicsItem::mouseReleaseEvent(event); // Вызываем обработчик отпускания кнопки мыши родительского класса
}
