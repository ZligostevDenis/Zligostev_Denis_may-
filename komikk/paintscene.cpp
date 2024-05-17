#include "paintscene.h" // Подключение заголовочного файла класса PaintScene

// Конструктор класса PaintScene
PaintScene::PaintScene(QGraphicsScene *parent) : QGraphicsScene(parent){} // Тело конструктора

// Деструктор класса PaintScene
PaintScene::~PaintScene(){}// Тело деструктора

// Метод обработки события нажатия кнопки мыши
void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // Обработка нажатия левой кнопки мыши (добавление вершины)
    if (event->button() == Qt::LeftButton)
    {
        // Проверка, нет ли уже элемента сцены в месте клика
        if (items(QPointF(event->scenePos().x(), event->scenePos().y())).size() == 0)
        {
            // Получение указателя на объект PointsAndMatrix (если он еще не получен)
            if (ptrMatrix == nullptr) {
                emit signalGetPtrMatrix(ptrMatrix);
            }

            // Добавление новой вершины в контейнер и получение ее индекса:
            int buffNumbOfCreatedPoint = ptrMatrix->addPoint(event->scenePos().x(), event->scenePos().y());

            // Отрисовка новой вершины на сцене:
            addItem_Point(buffNumbOfCreatedPoint);

            // Создание и отрисовка ребер от новой вершины ко всем предыдущим вершинам:
            for (int i = 0; i < buffNumbOfCreatedPoint; i++)
            {
                addItem_Line(i, buffNumbOfCreatedPoint);
            }

            // Вывод отладочной информации о состоянии матрицы смежности графа:
            qDebug() << "\n";
            QDebug aaa = qDebug();
            aaa << "    ";
            for (int i = 0; i < ptrMatrix->Points.size(); i++)
            {
                aaa << i << " ";
            }
            aaa << "\n";
            qDebug() = aaa;
            for (int i = 0; i < ptrMatrix->Points.size(); i++)
            {
                for (int j = 0; j < ptrMatrix->Points.size(); j++)
                {
                    if (j == 0) {
                        aaa << i << " ";
                    }
                    aaa << ptrMatrix->WaysMatrix[i][j].size << " ";
                }
                aaa << "\n";
                qDebug() = aaa;
            }
        }
    }

    // Обработка нажатия правой кнопки мыши (удаление вершины с индексом 0)
    if (event->button() == Qt::RightButton)
    {
        ptrMatrix->deletePoint(0);
    }

    // Обработка нажатия средней кнопки мыши (удаление всех элементов графа)
    if (event->button() == Qt::MiddleButton)
    {
        ptrMatrix->deleteAll();
    }
}
