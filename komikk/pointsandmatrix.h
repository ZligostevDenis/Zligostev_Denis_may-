#ifndef POINTSANDMATRIX_H // Проверка, не был ли этот файл уже подключен
#define POINTSANDMATRIX_H

#include "point.h" // Подключаем заголовочный файл класса Point
#include "SalesmansMethod.h" // Подключаем заголовочный файл класса SalesmansMethod

#include <vector> // Подключаем для работы с векторами
#include <QObject> // Подключаем класс QObject для использования сигналов и слотов
#include <functional> // Подключаем для работы с функциональными объектами
#include <ctime> // Подключаем для работы со временем
#include <random> // Подключаем для генерации случайных чисел

// Структура, описывающая ребро графа
struct Way
{
    QGraphicsLineItem* line = nullptr; // Линия, соединяющая две вершины
    QGraphicsTextItem* text = nullptr; // Текст с длиной ребра, отображаемый на линии
    int size = -1; // Длина ребра (по умолчанию -1, что означает отсутствие ребра)
};

// Класс PointsAndMatrix, наследуемый от QObject
class PointsAndMatrix : public QObject
{
    Q_OBJECT // Макрос для использования сигналов и слотов

public:
    std::vector<Point*> Points; // Вектор вершин графа
    Way** WaysMatrix; // Матрица смежности графа, хранящая информацию о ребрах

    int activeZones = 0; // Радиус зоны вокруг вершины, в которой нельзя создавать другие вершины

    // Конструктор класса
    explicit PointsAndMatrix(QObject *parent = Q_NULLPTR);

    ~PointsAndMatrix(); // Деструктор класса

signals:
    // Сигналы для удаления элементов со сцены
    void signalDeleteItem_Line(int index_i, int index_j); // Сигнал для удаления линии
    void signalDeleteItem_Point(int index); // Сигнал для удаления точки

    void signalSendMatrixSize(int size); // Сигнал для отправки размера матрицы

public:
    // Методы для работы с графом:
    int addPoint(int x, int y); // Добавление вершины с координатами (x, y)
    void addLine(int firstTop, int secondTop, int size); // Добавление ребра между вершинами firstTop и secondTop с длиной size
    void deleteLine(int index_i, int index_j); // Удаление ребра
    int deletePoint(int index); // Удаление вершины
    void deleteAll(); // Удаление всех вершин и ребер
    void coutMatrix(); // Вывод матрицы смежности в консоль (для отладки)

    // Методы для изменения цвета элементов графа:
    void setLineColor(int firstTop, int secondTop, int chose); // Установка цвета линии
    void setPointColor(int firstTop, int chose); // Установка цвета вершины
    void setAllPointsOneColor(int chose); // Установка одного цвета для всех вершин
    void setWaySize(int firstTop, int secondTop, int size); // Установка длины ребра
    void setZones(int arg); // Установка радиуса зоны вокруг вершин
    void setAllLinesOneColor(int chose); // Установка одного цвета для всех линий

    // Методы для анализа графа:
    int degreeOfTop(int numbOfTop); // Получение степени вершины
    int gamilton(int k, int size, int* path, int* c, int** a, int v0); // Алгоритм поиска гамильтонова цикла
    bool isHamiltonianGraph(int **ptr, int size); // Проверка, является ли граф гамильтоновым
    bool HamiltonianGraph(int index1); // Проверка, существует ли гамильтонов цикл, начинающийся с вершины index1
    bool HamiltonianGraph(int index1, int index2); // Проверка, существует ли гамильтонов цикл, проходящий через вершины index1 и index2
    void ActivateSalesmansMethod(); // Запуск метода коммивояжера
};

#endif // POINTSANDMATRIX_H // Завершение блока условного включения
