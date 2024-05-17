#ifndef SALESMANSMETHOD_H // Проверка, не был ли этот файл уже подключен
#define SALESMANSMETHOD_H

#include <vector> // Подключаем для работы с векторами

// Класс для решения задачи коммивояжера
class SalesmansMethod
{
public:
    // Структура, представляющая ребро графа
    struct Edge
    {
        int firstTop; // Номер первой вершины ребра
        int secondTop; // Номер второй вершины ребра

        // Конструктор структуры
        Edge(int I, int J) : firstTop(I), secondTop(J)
        {

        }
    };

private:
    // Вспомогательный класс для хранения информации о нулевых элементах матрицы
    class Zero
    {
    public:
        int quantity; // Количество нулей в строке/столбце
        int i; // Индекс строки
        int j; // Индекс столбца

        // Конструктор класса
        Zero(int Q, int I, int J) : quantity{ Q }, i{ I }, j{ J }
        {
        }
        ~Zero() // Деструктор класса
        {
        }
    };

private:
    // Матрица расстояний между городами
    int **array = nullptr; // Исходная матрица
    int **arraySecond = nullptr; // Вспомогательная матрица

    // Размеры матриц
    const int firstSizeArr; // Начальный размер матрицы
    int sizeArr; // Текущий размер матрицы
    int sizeArrSecond;

    // Вспомогательные массивы для хранения индексов минимальных элементов в строках и столбцах
    int *di = nullptr, *dj = nullptr; // Для исходной матрицы
    int *diSecond = nullptr, *djSecond = nullptr; // Для вспомогательной матрицы

    // Суммы минимальных элементов в строках и столбцах
    int di_sum, dj_sum;

    // Массив ребер, из которых будет формироваться кратчайший путь
    std::vector<Edge> *Ways = nullptr;
    int HWays; // Длина текущего пути (количество ребер)

    // Длины путей:
    int H_current; // Длина текущего пути
    int H_0; // Длина пути при исключении ребра
    int H_1; // Длина пути при включении ребра

    // Массив для хранения информации о нулевых элементах матрицы
    std::vector<Zero> zerosArray;
public:
    // Конструктор класса
    SalesmansMethod(int **arr, int size, std::vector<Edge> *&ways);

    // Методы для работы с матрицей:
    int findMinElemColumn(int j, int currI = -1); // Поиск минимального элемента в столбце j (исключая строку currI)
    int findMinElemRow(int i, int currJ = -1); // Поиск минимального элемента в строке i (исключая столбец currJ)
    void findDi(); // Вычисление массива di (индексы минимальных элементов в строках)
    void findDj(); // Вычисление массива dj (индексы минимальных элементов в столбцах)
    void reduceMatrix(); // Редукция матрицы (вычитание минимальных элементов)
    void findZeros(); // Поиск нулевых элементов в матрице
    void findZeros1(); // Поиск нулевых элементов в матрице (альтернативный метод)
    int findBiggerZero(); // Поиск нулевого элемента с наибольшей оценкой
    void exclusionSimilarEdge(int indexI, int indexJ, bool choseArr); // Исключение ребер, инцидентных вершинам indexI и indexJ
    void edgesExclusion(int indexI, int indexJ); // Исключение ребра (indexI, indexJ)
    void chooseMatrix(int chose); // Выбор матрицы для дальнейшей работы
    void mainFunction(); // Основная функция алгоритма

    ~SalesmansMethod(); // Деструктор класса
};

#endif // SALESMANSMETHOD_H // Завершение блока условного включения
