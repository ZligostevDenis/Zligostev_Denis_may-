#ifndef PAINTSCENE_H // Проверка, не был ли этот файл уже подключен
#define PAINTSCENE_H

#include <QGraphicsScene> // Подключаем класс QGraphicsScene для работы с графической сценой
#include <QGraphicsSceneMouseEvent> // Подключаем класс для обработки событий мыши на сцене
#include <QPointF> // Подключаем класс QPointF для работы с координатами точек

#include <QDebug> // Подключаем для отладки

#include "pointsandmatrix.h" // Подключаем заголовочный файл класса PointsAndMatrix

// Класс PaintScene, наследуемый от QGraphicsScene
class PaintScene : public QGraphicsScene
{
    Q_OBJECT // Макрос для использования сигналов и слотов

public:
    explicit PaintScene(QGraphicsScene* parent = 0); // Конструктор класса

    ~PaintScene(); // Деструктор класса

signals:
    // Сигнал для передачи указателя на объект PointsAndMatrix
    void signalGetPtrMatrix(PointsAndMatrix*& out_ptrMatrix);

private:
    // Указатель на объект PointsAndMatrix
    PointsAndMatrix* ptrMatrix = nullptr;

    // Состояние кнопок мыши
    Qt::MouseButtons mouseButtonsState;

    // Указатели на первую и последнюю точки (не используются в коде)
    // Point *firstPoint = nullptr;
    // Point *lastPoint = nullptr;

public:
    // Обработчик события нажатия кнопки мыши на сцене
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    // Методы для добавления элементов на сцену
    // addItem_Point - добавляет точку (номер вершины numb)
    void addItem_Point(int numb)
    {
        addItem(ptrMatrix->Points[numb]->zone); // Добавление зоны точки
        addItem(ptrMatrix->Points[numb]->point); // Добавление графического представления точки
        addItem(ptrMatrix->Points[numb]->nameOfTop); // Добавление текстовой метки вершины
    }

    // addItem_Line - добавляет линию (ребро) между вершинами firstTop и secondTop
    void addItem_Line(int firstTop, int secondTop)
    {
        ptrMatrix->WaysMatrix[firstTop][secondTop].line->setZValue(-1); // Установка z-индекса линии
        addItem(ptrMatrix->WaysMatrix[firstTop][secondTop].line); // Добавление линии
        addItem(ptrMatrix->WaysMatrix[firstTop][secondTop].text); // Добавление текстовой метки ребра
    }

    // Слоты для удаления элементов со сцены
public slots:
    // deleteItem_Line - удаляет линию (ребро) между вершинами firstTop и secondTop
    void deleteItem_Line(int firstTop, int secondTop)
    {
        removeItem(ptrMatrix->WaysMatrix[firstTop][secondTop].line); // Удаление линии
        removeItem(ptrMatrix->WaysMatrix[firstTop][secondTop].text); // Удаление текстовой метки
    }

    // deleteItem_Point - удаляет точку (вершину) с индексом index
    void deleteItem_Point(int index)
    {
        removeItem(ptrMatrix->Points[index]->nameOfTop); // Удаление текстовой метки
        removeItem(ptrMatrix->Points[index]->point); // Удаление графического представления
        removeItem(ptrMatrix->Points[index]->zone); // Удаление зоны
    }
};

#endif // PAINTSCENE_H // Завершение блока условного включения
