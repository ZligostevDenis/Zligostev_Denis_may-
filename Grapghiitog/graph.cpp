#include "graph.h"

// Конструктор класса Graph с заданным размером
Graph::Graph(const int &size) {
    this->labelList = QVector<int>(size); // Создаем вектор меток вершин размером size
    this->maxSize = size; // Запоминаем максимальный размер графа
    this->adjMatrix = QVector<QVector<int>>(size, QVector<int>(size)); // Создаем матрицу смежности размером size x size
    // Инициализируем матрицу смежности нулями
    for (int i = 0; i < this->maxSize; ++i) {
        for (int j = 0; j < this->maxSize; ++j) this->adjMatrix[i][j] = 0;
    };
}

// Конструктор класса Graph по умолчанию с размером 10
Graph::Graph() : Graph(10) {}

// Проверка, пустой ли граф
inline bool Graph::isEmpty() { return this->vertexList.size() == 0; };

// Проверка, полный ли граф
inline bool Graph::isFull() { return this->vertexList.size() == this->maxSize;};

// Поиск индекса вершины в списке вершин
inline int Graph::GetVertPos(const int& v) {
    for (int i = 0; i < this->vertexList.size(); ++i) {
        if (this->vertexList[i] == v) return i; // Если вершина найдена, возвращаем ее индекс
    }
    return -1; // Если вершина не найдена, возвращаем -1
};

// Возвращает количество вершин в графе
inline int Graph::GetAmountVerts() { return this->vertexList.size(); };

// Добавление вершины в граф
bool Graph::insertVertex(int& vert) {
    if (this->isFull()) { // Если граф полный, выводим сообщение об ошибке и возвращаем false
        qDebug() << "Невозможно добавить вершину.";
        return false;
    };
    if (this->GetVertPos(vert) == -1) { // Если вершина еще не добавлена в граф
        this->vertexList.push_back(vert); // Добавляем вершину в список вершин
        return true;
    }
    qDebug() << vertexList; // Выводим список вершин
    return false; // Если вершина уже есть в графе, возвращаем false
};

// Возвращает количество ребер в графе
int Graph::GetAmountEdges() {
    int amount = 0;
    if (!this->isEmpty()){ // Если граф не пустой
        // Подсчитываем количество ненулевых элементов в матрице смежности
        for (int i = 0; i < this->vertexList.size(); ++i) {
            for (int j = 0; j < this->vertexList.size(); ++j) if (this->adjMatrix[i][j] != 0) amount++;
        }
    }
    return amount;
};

// Возвращает вес ребра между двумя вершинами
inline int Graph::GetWeight(const int& v1, const int& v2) {
    if (this->isEmpty()) return 0; // Если граф пустой, возвращаем 0

    int v1_p = this->GetVertPos(v1); // Получаем индекс первой вершины
    int v2_p = this->GetVertPos(v2); // Получаем индекс второй вершины

    // Если одной из вершин нет в графе, выводим сообщение об ошибке и возвращаем 0
    if (v1_p == -1 || v2_p == -1) {
        qDebug() << "Одного или двух узлов в графе нет";
        return 0;
    };

    return this->adjMatrix[v1_p][v2_p]; // Возвращаем вес ребра
};

// Возвращает список соседних вершин для заданной вершины
QVector<int> Graph::GetNbrs(const int& vertex) {
    QVector<int> nbrsList; // Создаем список соседних вершин
    int pos = this->GetVertPos(vertex); // Получаем индекс заданной вершины
    if (pos != -1) { // Если вершина найдена в графе
        // Добавляем в список все вершины, для которых есть ребро из заданной вершины
        for (int i = 0; i < this->vertexList.size(); ++i) {
            if (this->adjMatrix[pos][i] != 0) nbrsList.push_back(this->vertexList[i]);
        }
    }
    return nbrsList;
}

// Возвращает список индексов соседних вершин для заданного индекса вершины
QVector<int> Graph::getNbrsInd(const int &vert_index) {
    QVector<int> nbrs_ind; // Создаем список индексов соседних вершин
    // Добавляем в список все индексы, для которых есть ребро из заданного индекса
    for (int j = 0; j < this->adjMatrix.size(); ++j) {
        if (this->adjMatrix[vert_index][j]) nbrs_ind.push_back(j);
    }
    return nbrs_ind;
}

// Возвращает список вершин графа
QVector<int> Graph::getVertexList() {
    return this->vertexList;
}

// Обход графа в ширину (BFS)
void Graph::BFS(int &startVertex, QVector<bool>visitedVerts, QString &res) {
    // Если вершина еще не посещена
    if (visitedVerts[this->GetVertPos(startVertex)] == false) {
        this->VertsQueue.push_back(startVertex); // Добавляем вершину в очередь
        res += "Вершина " + QString::number(startVertex) + " посещена \n" ; // Добавляем информацию о посещении вершины в результат
        visitedVerts[this->GetVertPos(startVertex)] = true; // Помечаем вершину как посещенную
    }
    QVector<int> neighbors = this->GetNbrs(startVertex); // Получаем список соседних вершин
    this->VertsQueue.pop_front(); // Удаляем текущую вершину из очереди
    // Добавляем в очередь все непосещенные соседние вершины
    for (int i = 0; i < neighbors.size(); ++i) {
        if (!visitedVerts[this->GetVertPos(neighbors[i])]) {
            this->VertsQueue.push_back(neighbors[i]);
            visitedVerts[this->GetVertPos(neighbors[i])] = true;
            res += "Вершина " + QString::number(neighbors[i]) + " посещена\n";
        }
    }
    if (this->VertsQueue.empty()) return; // Если очередь пуста, завершаем обход

    BFS(VertsQueue.front(), visitedVerts, res); // Рекурсивно вызываем BFS для следующей вершины в очереди
}

// Обход графа в глубину (DFS)
void Graph::DFS(int &startVertex, QVector<bool>& visitedVerts, QString &res) {
    res+= "Вершина " + QString::number(startVertex) + " посещена\n"; // Добавляем информацию о посещении вершины в результат
    visitedVerts[this->GetVertPos(startVertex)] = true; // Помечаем вершину как посещенную
    QVector<int> neighbors = this->GetNbrs(startVertex); // Получаем список соседних вершин
    // Рекурсивно вызываем DFS для каждой непосещенной соседней вершины
    for (int i = 0; i < neighbors.size(); ++i){
        if (!visitedVerts[this->GetVertPos(neighbors[i])])
            this->DFS(neighbors[i], visitedVerts, res);
    };
}
void Graph::Dijkstra(int &startVertex, QString &res) {
    // Проверка на отрицательные веса
    for (int i = 0; i < vertexList.size(); i++)
        for (int j = 0; j < vertexList.size(); j++)
            if (adjMatrix[i][j] < 0) // Если найден отрицательный вес, алгоритм не работает, выходим из функции
                return;

    // Проверка существования начальной вершины
    if (GetVertPos(startVertex) == -1) // Если начальной вершины нет в графе, выходим из функции
        return;

    // Инициализация вектора посещенных вершин
    QVector<bool> visitedVerts(vertexList.size());
    for (auto it = visitedVerts.begin(); it!=visitedVerts.end(); ++it) *it = false; // Изначально все вершины не посещены

    // Инициализация меток вершин
    this->FillLabels(startVertex); // Устанавливаем метки: 0 для начальной вершины, бесконечность для остальных
    int curSrc = startVertex; // Текущая вершина, от которой ищем пути
    QVector<int> neighbors; // Вектор для хранения соседей текущей вершины

    // Основной цикл алгоритма Дейкстры
    while (!this->AllVisited(visitedVerts)){ // Пока не все вершины посещены
        neighbors = this->GetNbrs(curSrc); // Получаем список соседей текущей вершины
        int startLabel = labelList[GetVertPos(curSrc)]; // Получаем метку текущей вершины

        int* minNeighbor_ptr = nullptr; // Указатель на соседа с минимальной меткой
        int minW = 999999; // Инициализация минимальной метки

        // Перебираем всех соседей текущей вершины
        for (int i = 0; i < neighbors.size(); ++i){
            int weight = this->GetWeight(curSrc, neighbors[i]); // Получаем вес ребра до соседа
            int nIndex = this->GetVertPos(neighbors[i]); // Получаем индекс соседа
            int nextLabel = labelList[nIndex]; // Получаем метку соседа

            // Обновление метки соседа, если найден более короткий путь
            if (startLabel + weight < nextLabel) labelList[nIndex] = startLabel + weight;

            // Поиск соседа с минимальной меткой среди непосещенных
            if (!visitedVerts[nIndex] && minW > labelList[nIndex]) {
                minW = labelList[nIndex];
                minNeighbor_ptr = &neighbors[i];
            };
        };

        visitedVerts[GetVertPos(curSrc)] = true; // Помечаем текущую вершину как посещенную
        if (minNeighbor_ptr != nullptr) curSrc = *minNeighbor_ptr; // Переходим к соседу с минимальной меткой
    };

    // Формирование строки с результатами
    for (int i = 0; i < vertexList.size(); ++i) {
        if (i != GetVertPos(startVertex)){ // Для каждой вершины, кроме начальной
            res+= "Минимальное расстояние от вершины " + QString::number(startVertex)
                   + " до вершины "  + QString::number(vertexList[i]) + " равно "
                   + QString::number(labelList[GetVertPos(vertexList[i])]) + "\n";
        }
    };
}

// Проверка, все ли вершины посещены
bool Graph::AllVisited(QVector<bool> &visitedVerts) {
    bool flag = true;
    for (int i = 0; i < this->vertexList.size(); i++)
        if (visitedVerts[i] != true) // Если найдена непосещенная вершина, устанавливаем флаг в false
            flag = false;
    return flag;
}

// Инициализация меток вершин
void Graph::FillLabels(int &startVertex) {
    for (int i = 0, size = vertexList.size(); i < size; ++i)
        labelList[i] = 999999; // Устанавливаем метки всех вершин в бесконечность
    int pos = GetVertPos(startVertex);
    labelList[pos] = 0; // Устанавливаем метку начальной вершины в 0
};

// Вставка ребра в граф
void Graph::InsertEdge(const int& vertex1, const int& vertex2, const int& weight) {
    if (GetVertPos(vertex1) != (-1) && this->GetVertPos(vertex2) != (-1)) { // Если обе вершины существуют
        int vertPos1 = GetVertPos(vertex1); // Получаем индекс первой вершины
        int vertPos2 = GetVertPos(vertex2); // Получаем индекс второй вершины

        if (this->adjMatrix[vertPos1][vertPos2] != 0) { // Если ребро уже существует
            qDebug() << "Ребро между вершинами уже есть";
            return;
        }
        else this->adjMatrix[vertPos1][vertPos2] = weight; // Иначе устанавливаем вес ребра

    }
    else {
        qDebug() << "Обеих вершин (или одной из них) нет в графе ";
        return;
    }
};

// Вывод матрицы смежности в консоль
void Graph::showAdj() {
    for (int i = 0; i < this->maxSize; ++i) qDebug() << this->adjMatrix[i] << ' ';

    qDebug();
}

// Возвращает матрицу смежности
QVector<QVector<int> > Graph::getAdj() {
    return this->adjMatrix;
};

// Удаление ребра из графа
void Graph::eraseEdge(const int& vert, const int& vert2) {
    int p1 = this->GetVertPos(vert); // Получаем индекс первой вершины
    int p2 = this->GetVertPos(vert2); // Получаем индекс второй вершины
    if (p1 != -1 && p2 != -1) // Если обе вершины существуют
    {
        this->adjMatrix[p1][p2] = 0; // Устанавливаем вес ребра в 0
    }
};

// Удаление вершины из графа
void Graph::eraseVertex(const int& vert) {
    int pos = this->GetVertPos(vert); // Получаем индекс вершины
    if ( pos != -1) // Если вершина существует
    {
        // Удаляем все ребра, связанные с этой вершиной
        for (int i = 0; i < this->vertexList.size(); ++i)
        {
            this->adjMatrix[i].erase(this->adjMatrix[i].begin() + pos);
        }
        this->adjMatrix.erase(this->adjMatrix.begin() + pos); // Удаляем строку из матрицы смежности
        this->vertexList.erase(this->vertexList.begin() + pos); // Удаляем вершину из списка вершин
    }
};
