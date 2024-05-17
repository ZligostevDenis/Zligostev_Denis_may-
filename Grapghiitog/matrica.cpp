#include "matrica.h" // Подключаем заголовочный файл для класса Adjacency
#include "ui_matrica.h" // Подключаем заголовочный файл для интерфейса Adjacency

#include <QDebug> // Подключаем для отладки

// Конструктор класса Adjacency
Adjacency::Adjacency(QWidget *parent) :
    QWidget(parent), // Вызываем конструктор родительского класса QWidget
    ui(new Ui::Adjacency) // Создаем объект интерфейса Ui::Adjacency
{
    ui->setupUi(this); // Инициализируем интерфейс
}

// Деструктор класса Adjacency
Adjacency::~Adjacency()
{
    delete ui; // Удаляем объект интерфейса
}

// Метод для установки матрицы смежности
void Adjacency::setAdj(QVector<QVector<int>> adj)
{
    this->adj = adj; // Сохраняем матрицу смежности
}

// Метод для установки размера графа
void Adjacency::setSize(int size)
{
    this->size = size; // Сохраняем размер графа
}

// Метод для перестроения таблицы смежности
void Adjacency::rebuild(QVector<QString> verts)
{
    QStringList names; // Создаем список имен вершин
    for (int i = 0; i < size; ++i ) { // Перебираем все вершины
        names << "№" + verts[i]; // Добавляем имя вершины в список
    }
    ui->tableAdj->setRowCount(size); // Устанавливаем количество строк в таблице
    ui->tableAdj->setColumnCount(size); // Устанавливаем количество столбцов в таблице
    ui->tableAdj->setVerticalHeaderLabels(names); // Устанавливаем имена строк
    ui->tableAdj->setHorizontalHeaderLabels(names); // Устанавливаем имена столбцов
    for (int i=0; i<size; ++i){ // Перебираем строки матрицы смежности
        for(int j=0; j<size; ++j){ // Перебираем столбцы матрицы смежности
            QTableWidgetItem *itm = new QTableWidgetItem(QString::number(adj[i][j])); // Создаем элемент таблицы со значением из матрицы смежности
            ui->tableAdj->setItem(i, j, itm); // Устанавливаем элемент в таблицу
            ui->tableAdj->item(i, j)->setFlags(Qt::NoItemFlags); // Делаем элемент таблицы нередактируемым
        }
    }
}

// Метод для установки объекта графа
void Adjacency::setGraph(Graph * graph)
{
    this->graph = graph; // Сохраняем объект графа
}
