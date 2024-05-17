#ifndef GRAPH_H
#define GRAPH_H

// Подключаем библиотеки QQueue и QVector из Qt
#include <QQueue>
#include <QVector>
#include <QDebug>

// Класс графа
class Graph {
private:
    // Список вершин
    QVector<int> vertexList;

    // Матрица смежности
    QVector<QVector<int>> adjMatrix;

    // Максимальный размер графа
    int maxSize;

    // Очередь вершин
    QQueue<int> VertsQueue;

    // Список меток вершин
    QVector<int> labelList;

public:
    // Конструктор с параметром размера графа
    Graph(const int& size);

    // Конструктор по умолчанию
    Graph();

    // Метод для вывода матрицы смежности (используется для отладки)
    void showAdj();

    // Метод для получения матрицы смежности
    QVector<QVector<int>> getAdj();

    // Метод для проверки пуст ли граф
    bool isEmpty();

    // Метод для проверки того, заполнен ли граф
    bool isFull();

    // Метод для получения позиции вершины по ее значению
    int GetVertPos(const int&);

    // Метод для получения количества вершин в графе
    int GetAmountVerts();

    // Метод для добавления вершины в граф
    bool insertVertex(int&);

    // Метод для получения количества ребер в графе
    int GetAmountEdges();

    // Метод для получения веса ребра
    int GetWeight(const int&, const int&);

    // Метод для получения индекса веса ребра
    int getWeightInd(const int&, const int&);

    // Метод для удаления вершины из графа
    void eraseVertex(const int& vert);

    // Метод для удаления ребра из графа
    void eraseEdge(const int& vert, const int& vert2);

    // Метод для добавления ребра в граф
    void InsertEdge(const int& vertex1, const int& vertex2, const int& weight = 1);

    // Метод для получения списка соседей вершины
    QVector<int> GetNbrs(const int&);

    // Метод для получения списка индексов соседей вершины
    QVector<int> getNbrsInd(const int& vert_index);

    // Метод для получения списка вершин
    QVector<int> getVertexList();

    // Метод для выполнения обхода в ширину (BFS)
    void BFS(int& startVertex, QVector<bool> visitedVerts, QString&);

    // Метод для выполнения обхода в глубину (DFS)
    void DFS(int& startVertex, QVector<bool> &visitedVerts, QString&);

    // Метод для выполнения алгоритма Дейкстры
    void Dijkstra(int& startVertex, QString&);

    // Метод для проверки, были ли посещены все вершины
    bool AllVisited(QVector<bool>& visitedVerts);

    // Метод для заполнения меток вершин
    void FillLabels(int& startVertex);
};

#endif // GRAPH_H
