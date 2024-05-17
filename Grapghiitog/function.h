#ifndef FUNCTION_H 
#define FUNCTION_H

#include "graphvertex.h" // Подключаем заголовочный файл класса graphVertex
#include "graph.h" // Подключаем заголовочный файл класса Graph
#include "information.h" // Подключаем заголовочный файл класса ShowInfo
#include <matrica.h> // Подключаем заголовочный файл класса Adjacency
#include <weight.h> // Подключаем заголовочный файл класса GetWeight

#include <QDialog> // Подключаем класс QDialog для создания диалогового окна
#include <QtCore> // Подключаем модуль QtCore
#include <QtGui> // Подключаем модуль QtGui
#include <QGraphicsScene> // Подключаем класс QGraphicsScene для работы с графической сценой

namespace Ui {
class Dialog; // Объявляем класс Dialog внутри пространства имен Ui
}

// Класс Dialog, наследуемый от QDialog
class Dialog : public QDialog
{
    Q_OBJECT // Макрос для использования сигналов и слотов

public:
    Dialog(QWidget *parent = nullptr); // Конструктор класса
    ~Dialog(); // Деструктор класса

private slots:
    void on_btnAddVertex_clicked(); // Слот для обработки нажатия кнопки "Add Vertex"
    void on_btnAdj_clicked(); // Слот для обработки нажатия кнопки "Adj"
    void on_btnAddEdge_clicked(); // Слот для обработки нажатия кнопки "Add Edge"
    void on_btnDelete_clicked(); // Слот для обработки нажатия кнопки "Delete"
    void on_btnBFS_clicked(); // Слот для обработки нажатия кнопки "BFS"
    void on_btnDFS_clicked(); // Слот для обработки нажатия кнопки "DFS"
    void on_btnDijkstra_clicked(); // Слот для обработки нажатия кнопки "Dijkstra"

    void on_graphicsView_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint);

private:
    Ui::Dialog *ui; // Указатель на объект интерфейса

    Adjacency *adj; // Указатель на объект класса Adjacency

    QGraphicsScene * scene; // Указатель на объект графической сцены

    Graph graph; // Объект графа

    graphVertex* vert; // Указатель на объект вершины графа

    QVector<graphVertex*> vertices; // Вектор вершин графа

    Edge* edge; // Указатель на объект ребра графа

    QVector<Edge*> edges; // Вектор ребер графа

    QQueue<graphVertex*> for_draw; // Очередь вершин для отрисовки
};

#endif // FUNCTION_H 
