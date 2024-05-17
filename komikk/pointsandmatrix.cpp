#include "pointsandmatrix.h" // Подключение заголовочного файла класса PointsAndMatrix

// Конструктор класса PointsAndMatrix
PointsAndMatrix::PointsAndMatrix(QObject *parent) : QObject(parent)
{
    WaysMatrix = nullptr; // Инициализируем указатель на матрицу смежности как nullptr (матрица еще не создана)
}

// Метод добавления новой вершины в граф
int PointsAndMatrix::addPoint(int x, int y)
{
    // Создаем новую матрицу, размер которой на 1 больше предыдущей:
    Way** buffWaysMatrix = new Way*[Points.size() + 1];
    for (unsigned int i = 0; i < Points.size() + 1; i++)
    {
        buffWaysMatrix[i] = new Way[Points.size() + 1];
    }

    // Проверяем, была ли уже создана матрица смежности:
    if (WaysMatrix == nullptr) // Если матрица еще не создана (это первая вершина)
    {
        WaysMatrix = buffWaysMatrix; // Присваиваем WaysMatrix новую матрицу
        buffWaysMatrix = nullptr; // Обнуляем временный указатель
    }
    else // Если матрица уже существует (добавляем вершину к существующему графу)
    {
        // Копируем значения из старой матрицы в новую:
        for (unsigned i = 0; i < Points.size(); i++)
        {
            for (unsigned j = 0; j < Points.size(); j++)
            {
                buffWaysMatrix[i][j] = WaysMatrix[i][j];
            }
        }

        // Очищаем память, выделенную под старую матрицу:
        for (unsigned i = 0; i < Points.size(); i++)
        {
            delete[] WaysMatrix[i];
        }
        delete[] WaysMatrix;

        // Присваиваем WaysMatrix новую матрицу:
        WaysMatrix = buffWaysMatrix;
        buffWaysMatrix = nullptr; // Обнуляем временный указатель
    }

    // Создаем новую вершину и добавляем ее в вектор Points:
    Points.push_back(new Point(x, y, Points.size(), activeZones));

    // Создаем ребра от новой вершины ко всем существующим вершинам:
    for (int i = 0; i < Points.size() - 1; i++)
    {
        // Генерируем случайную длину ребра:
        srand(time(NULL) - i * 100);
        rand();
        int buff = 1 + rand() % 9999;
        buff = 1 + rand() % 9999 + buff;
        buff = 1 + rand() % 9999 + buff;
        srand(time(NULL) - buff);
        rand();

        int way = 1 + (rand() & 0x7FFF) % 24; // Генерируем случайное число от 1 до 24

        // Добавляем ребро в матрицу смежности:
        addLine(i, Points.size() - 1, way);
    }

    // Обновляем данные в выпадающих списках интерфейса программы:
    emit signalSendMatrixSize(Points.size());

    // Возвращаем индекс новой вершины:
    return Points.size() - 1;
}

// Метод добавления ребра между двумя вершинами
void PointsAndMatrix::addLine(int firstTop, int secondTop, int size)
{
    // Сохраняем размер пути в матрице смежности:
    WaysMatrix[firstTop][secondTop].size = size;

    // Создаем графическое представление ребра (линию):
    WaysMatrix[firstTop][secondTop].line = new QGraphicsLineItem(Points[firstTop]->X,
                                                                 Points[firstTop]->Y,
                                                                 Points[secondTop]->X,
                                                                 Points[secondTop]->Y);
    WaysMatrix[firstTop][secondTop].line->setPen(QPen(Qt::black)); // Устанавливаем цвет линии

    // Создаем текстовый элемент для отображения длины ребра:
    WaysMatrix[firstTop][secondTop].text = new QGraphicsTextItem(QString::number(size));
    WaysMatrix[firstTop][secondTop].text->setFont(QFont("", 10, 70, 0)); // Устанавливаем шрифт текста

    // Вычисляем координаты для размещения текста:
    int sizeX = 0, sizeY = 0;
    sizeX = Points[firstTop]->X < Points[secondTop]->X ? Points[firstTop]->X : Points[secondTop]->X;
    sizeY = Points[firstTop]->Y < Points[secondTop]->Y ? Points[firstTop]->Y : Points[secondTop]->Y;
    WaysMatrix[firstTop][secondTop].text->setPos(sizeX + (std::abs(Points[firstTop]->X - Points[secondTop]->X) / 2) - 15,
                                                 sizeY + (std::abs(Points[firstTop]->Y - Points[secondTop]->Y) / 2) - 15);

    // Заполняем симметричные ячейки матрицы смежности (так как граф неориентированный):
    WaysMatrix[secondTop][firstTop].size = WaysMatrix[firstTop][secondTop].size;
    WaysMatrix[secondTop][firstTop].line = WaysMatrix[firstTop][secondTop].line;
    WaysMatrix[secondTop][firstTop].text = WaysMatrix[firstTop][secondTop].text;

    // Обновляем данные в выпадающих списках интерфейса программы:
    emit signalSendMatrixSize(Points.size());
}
void PointsAndMatrix::deleteLine(int index_i, int index_j)
{
    //emit signalDeleteItem_Line(index_i, index_j);

    // Удаление ребра из матрицы смежности:
    WaysMatrix[index_i][index_j].size = -1; // Устанавливаем размер как -1, чтобы обозначить отсутствие ребра
    delete WaysMatrix[index_i][index_j].line; // Удаляем графическое представление ребра
    delete WaysMatrix[index_i][index_j].text; // Удаляем текстовое представление длины ребра
    WaysMatrix[index_i][index_j].line = nullptr; // Обнуляем указатели
    WaysMatrix[index_i][index_j].text = nullptr;

    // Удаление симметричного ребра (так как граф неориентированный):
    WaysMatrix[index_j][index_i].size = -1;
    WaysMatrix[index_j][index_i].line = nullptr;
    WaysMatrix[index_j][index_i].text = nullptr;

    // Отправляем сигнал для обновления выпадающих списков в интерфейсе программы:
    emit signalSendMatrixSize(Points.size());
}

// Метод для удаления вершины из графа
int PointsAndMatrix::deletePoint(int index)
{
    // Проверяем, пустой ли контейнер вершин:
    if (Points.size() == 0)
    {
        qDebug() << "Points пуст. Элемент под индексом " << index << " не был удален.";
        return -1; // Ошибка: контейнер вершин пуст
    }

    // Проверяем, существует ли вершина с заданным индексом:
    if (index >= Points.size())
    {
        qDebug() << "Элемент под индексом " << index << " отсутствует в Points. Элемент не был удален";
        return -2; // Ошибка: вершина с заданным индексом не найдена
    }

    // Обрабатываем случай, когда матрица смежности имеет размер 1x1:
    if (Points.size() == 1)
    {
        deleteLine(0, 0); // Удаляем единственное ребро
        delete[] WaysMatrix[0]; // Удаляем строку матрицы
        delete[] WaysMatrix; // Удаляем саму матрицу
        WaysMatrix = nullptr; // Обнуляем указатель на матрицу
    }
    else // Обрабатываем случай, когда матрица смежности больше 1x1:
    {
        // Удаляем все ребра, связанные с удаляемой вершиной:
        for (int a = 0; a < Points.size(); a++)
        {
            if (a != index)
            {
                deleteLine(index, a);   // Удаление ребра (столбец)
                deleteLine(a, index);   // Удаление ребра (строка)
            }
        }
        deleteLine(index, index); // Удаляем ребро, соединяющее вершину саму с собой (петля)

        // Создаем новую матрицу смежности, уменьшенную на один элемент:
        Way** buffWaysMatrix = new Way*[Points.size() - 1];
        for (unsigned int i = 0; i < Points.size() - 1; i++)
        {
            buffWaysMatrix[i] = new Way[Points.size() - 1];
        }

        // Копируем необходимые элементы из старой матрицы в новую,
        // пропуская удаленные строку и столбец:
        int I = 0, J = 0;
        for (unsigned i = 0; i < Points.size(); i++)
        {
            I = i;
            if (i != index)
            {
                if (i > index) { --I; }
                for (unsigned j = 0; j < Points.size(); j++)
                {
                    J = j;
                    if (j != index)
                    {
                        if (j > index) { --J; }
                        buffWaysMatrix[I][J] = WaysMatrix[i][j];
                    }
                }
            }
        }

        // Удаляем старую матрицу:
        for (unsigned i = 0; i < Points.size(); i++)
        {
            delete[] WaysMatrix[i];
        }
        delete[] WaysMatrix;

        // Сохраняем указатель на обновленную матрицу:
        WaysMatrix = buffWaysMatrix;
    }

    // Удаляем элемент вектора Points:
    //emit signalDeleteItem_Point(index);

    delete Points[index];

    // Обновляем вектор Points: сдвигаем все элементы после удаленного на одну позицию назад,
    // корректируем номера вершин и их отображение:
    for (int i = index; i < Points.size() - 1; i++)
    {
        Points[i] = Points[i + 1];
        Points[i]->Number = i;
        Points[i]->nameOfTop->setPlainText(QString::number(i));
    }

    Points.pop_back(); // Удаляем последний элемент вектора (дубликат)

    // Отправляем сигнал для обновления выпадающих списков в интерфейсе программы:
    emit signalSendMatrixSize(Points.size());

    return 1; // Возвращаем 1, если удаление прошло успешно
}
void PointsAndMatrix::deleteAll()
{
    // Отправляем сигнал для очистки выпадающих списков в интерфейсе программы:
    emit signalSendMatrixSize(-1);

    // Удаляем все ребра графа:
    for (int i = 0; i < Points.size(); i++)
    {
        for (int j = 0; j < Points.size(); j++)
        {
            deleteLine(i, j);
        }
    }

    // Удаляем матрицу смежности:
    for (int i = 0; i < Points.size(); i++)
    {
        delete[] WaysMatrix[i];
    }
    delete[] WaysMatrix;
    WaysMatrix = nullptr;

    // Удаляем все вершины графа:
    for (int i = 0; i < Points.size(); i++)
    {
        delete Points[i];
    }

    // Очищаем вектор вершин:
    Points.clear();
}

// Метод для вывода матрицы смежности в консоль:
void PointsAndMatrix::coutMatrix()
{
    qDebug() << "\n"; // Выводим пустую строку для разделения
    QDebug aaa = qDebug(); // Создаем объект QDebug для форматированного вывода
    aaa << "    "; // Выводим отступ для заголовка столбцов

    // Выводим заголовок столбцов:
    for (int i = 0; i < Points.size(); i++)
    {
        aaa << i << " ";
    }
    aaa << "\n"; // Переход на новую строку
    qDebug() = aaa; // Выводим строку в консоль

    // Выводим строки матрицы:
    for (int i = 0; i < Points.size(); i++)
    {
        // Выводим номер строки:
        for (int j = 0; j < Points.size(); j++)
        {
            if (j == 0) { aaa << i << " "; } // Выводим номер строки только в начале строки
            aaa << WaysMatrix[i][j].size << " "; // Выводим значение элемента матрицы
        }
        aaa << "\n"; // Переход на новую строку
        qDebug() = aaa; // Выводим строку в консоль
    }
}

// Метод для установки цвета ребра:
void PointsAndMatrix::setLineColor(int firstTop, int secondTop, int chose)
{
    // Проверяем, существует ли ребро и корректны ли индексы вершин:
    if (WaysMatrix[firstTop][secondTop].line != nullptr && firstTop >= 0 && secondTop >= 0)
    {
        // Устанавливаем цвет ребра в зависимости от значения chose:
        switch (chose)
        {
        case 0:
        {
            WaysMatrix[firstTop][secondTop].line->setPen(QPen(Qt::black)); // Черный цвет
            break;
        }
        case 1:
        {
            WaysMatrix[firstTop][secondTop].line->setPen(QPen(Qt::green)); // Зеленый цвет
            break;
        }
        case 2:
        {
            WaysMatrix[firstTop][secondTop].line->setPen(QPen(Qt::red)); // Красный цвет
            break;
        }
        }
    }
}

// Метод для установки цвета вершины:
void PointsAndMatrix::setPointColor(int firstTop, int chose)
{
    // Проверяем, существует ли вершина и корректен ли индекс:
    if (Points[firstTop]->point != nullptr && firstTop >= 0)
    {
        // Устанавливаем цвет вершины в зависимости от значения chose:
        switch (chose)
        {
        case 0:
        {
            Points[firstTop]->point->setBrush(QColor(255, 255, 255)); // белый цвет
            Points[firstTop]->point->setPen(QPen(QColor(255, 255, 255)));
            break;
        }
        case 1:
        {
            Points[firstTop]->point->setBrush(QColor(Qt::blue)); // синий цвет
            Points[firstTop]->point->setPen(QPen(Qt::blue));
            break;
        }
        }
    }
}

// Метод для установки одинакового цвета всем вершинам:
void PointsAndMatrix::setAllPointsOneColor(int chose)
{
    // Вызываем метод setPointColor для каждой вершины:
    for (int i = 0; i < Points.size(); i++)
    {
        setPointColor(i, chose);
    }
}


void PointsAndMatrix::setWaySize(int firstTop, int secondTop, int size)
{
    // Устанавливаем новый размер ребра в матрице смежности:
    WaysMatrix[firstTop][secondTop].size = size;
    // Устанавливаем новый размер для симметричного ребра (так как граф неориентированный):
    WaysMatrix[secondTop][firstTop].size = size;
    // Обновляем текстовое представление размера ребра на графической сцене:
    WaysMatrix[firstTop][secondTop].text->setHtml(QString::number(size));
}

// Метод для установки отображения зон вершин
void PointsAndMatrix::setZones(int arg)
{
    // Устанавливаем флаг activeZones, который определяет, нужно ли отображать зоны:
    activeZones = arg;

    // Если зоны нужно отображать:
    if (arg)
    {
        // Для каждой вершины устанавливаем черную рамку зоны:
        for (int i = 0; i < Points.size(); i++)
        {
            Points[i]->zone->setPen(QPen(Qt::black));
        }
    }
    // Если зоны не нужно отображать:
    else
    {
        // Для каждой вершины убираем рамку зоны:
        for (int i = 0; i < Points.size(); i++)
        {
            Points[i]->zone->setPen(QPen(Qt::NoPen));
        }
    }
}

// Метод для установки одинакового цвета всем ребрам:
void PointsAndMatrix::setAllLinesOneColor(int chose)
{
    // Проходим по всем ребрам и устанавливаем цвет:
    for (int i = 0; i < Points.size(); i++)
    {
        for (int j = 0; j < Points.size(); j++)
        {
            setLineColor(i, j, chose);
        }
    }
}

// Метод для определения степени вершины (количество ребер, исходящих из вершины):
int PointsAndMatrix::degreeOfTop(int numbOfTop)
{
    int count = 0; // Счетчик ребер
    // Проходим по строке матрицы смежности, соответствующей вершине numbOfTop:
    for (int j = 0; j < Points.size(); j++)
    {
        // Если размер ребра не равен -1 (ребро существует), увеличиваем счетчик:
        if (WaysMatrix[numbOfTop][j].size != -1) { ++count; }
    }
    // Возвращаем количество ребер:
    return count;
}

// Рекурсивная функция для поиска цикла проходящего через все вершины:
int PointsAndMatrix::gamilton(int k, int size, int* path, int* c, int** a, int v0)
{
    int v, q1 = 0; // v - текущая вершина, q1 - флаг найденного цикла
    // Перебираем все вершины:
    for (v = 0; v < size && !q1; v++)
    {
        // Проверяем, существует ли ребро между текущей вершиной (v) и
        // предыдущей вершиной в пути (path[k-1]):
        if (a[v][path[k - 1]] || a[path[k - 1]][v])
        {
            // Если мы достигли последней вершины и она совпадает с начальной,
            // то цикл найден:
            if (k == size && v == v0) { q1 = 1; }
            // Если вершина v еще не была посещена:
            else if (c[v] == -1)
            {
                // Помечаем вершину v как посещенную:
                c[v] = k;
                // Добавляем вершину v в путь:
                path[k] = v;
                // Рекурсивно вызываем функцию gamilton для следующей вершины:
                q1 = gamilton(k + 1, size, path, c, a, v0);
                // Если цикл не был найден, отменяем посещение вершины v:
                if (!q1) { c[v] = -1; }
            }
            else { continue; } // Если вершина v уже была посещена, переходим к следующей
        }
    }
    return q1; // Возвращаем флаг найденного цикла
}

// Метод для проверки, является ли граф везде проходящим:
bool PointsAndMatrix::isHamiltonianGraph(int **ptr, int size)
{
    bool result = 0; // Флаг результата

    // Создаем матрицу смежности для алгоритма поиска вездепроходящего цикла:
    int **arr = new int*[size];
    for (int i = 0; i < size; i++)
    {
        arr[i] = new int[size];
    }

    // Массив для хранения информации о посещенных вершинах:
    int* c = new int[size];
    // Массив для хранения пути:
    int* path = new int[size];
    // Начальная вершина:
    int v0 = 0;

    // Преобразуем матрицу ptr в матрицу смежности arr:
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (ptr[i][j] == -1) { arr[i][j] = 0; } // Если ребра нет, записываем 0
            else { arr[i][j] = 1; } // Если ребро есть, записываем 1
        }
    }

    // Инициализируем массив c: -1 означает, что вершина не посещена:
    for (int i = 0; i < size; i++)
    {
        c[i] = -1;
    }
    // Добавляем начальную вершину в путь:
    path[0] = v0;
    // Помечаем начальную вершину как посещенную:
    c[v0] = v0;

    // Вызываем функцию gamilton для поиска вездепроходящего цикла:
    if (gamilton(1, size, path, c, arr, v0)) { result = 1; } // Цикл найден
    else { result = 0; } // Цикл не найден

    // Освобождаем выделенную память:
    for (int i = 0; i < size; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;
    delete[] c;
    delete[] path;

    // Возвращаем результат:
    return result;
}

// Метод для проверки, является ли граф выздепроходящим, после удаления вершины с индексом index1:
bool PointsAndMatrix::HamiltonianGraph(int index1)
{
    // Создаем матрицу смежности, уменьшенную на один элемент:
    int **array = new int*[Points.size() - 1];
    for (int i = 0; i < Points.size() - 1; i++)
    {
        array[i] = new int[Points.size() - 1];
    }

    // Копируем необходимые элементы из старой матрицы в новую, пропуская удаленные строку и столбец:
    int I = 0, J = 0;
    for (unsigned i = 0; i < Points.size(); i++)
    {
        I = i;
        if (i != index1)
        {
            if (i > index1) { --I; }
            for (unsigned j = 0; j < Points.size(); j++)
            {
                J = j;
                if (j != index1)
                {
                    if (j > index1) { --J; }
                    array[I][J] = WaysMatrix[i][j].size;
                }
            }
        }
    }

    bool answer =  isHamiltonianGraph(array, Points.size()-1);

    for(int i = 0; i < Points.size()-1; i++)
    {
        delete[] array[i];
    }
    delete[] array;

    return answer;
}

// Метод для проверки, является ли граф вездепроходящим, после удаления ребра между вершинами с индексами index1 и index2:
bool PointsAndMatrix::HamiltonianGraph(int index1, int index2)
{
    // Создаем новую матрицу смежности размером, равным исходной:
    int **array = new int*[Points.size()];
    for (int i = 0; i < Points.size(); i++)
    {
        array[i] = new int[Points.size()];
    }

    // Копируем значения из исходной матрицы смежности в новую:
    for (int i = 0; i < Points.size(); i++)
    {
        for (int j = 0; j < Points.size(); j++)
        {
            array[i][j] = WaysMatrix[i][j].size;
        }
    }

    // Удаляем ребро между вершинами index1 и index2:
    array[index1][index2] = -1;
    // Удаляем симметричное ребро (так как граф неориентированный):
    array[index2][index1] = -1;

    // Вызываем функцию isHamiltonianGraph для проверки вездепроходимости графа с удаленным ребром:
    bool answer = isHamiltonianGraph(array, Points.size());

    // Освобождаем выделенную память:
    for (int i = 0; i < Points.size(); i++)
    {
        delete[] array[i];
    }
    delete[] array;

    // Возвращаем результат проверки:
    return answer;
}

// Метод для запуска метода коммивояжера:
void PointsAndMatrix::ActivateSalesmansMethod()
{
    // Проверяем, достаточно ли вершин для применения метода:
    if (Points.size() > 2)
    {
        // Устанавливаем черный цвет для всех ребер:
        setAllLinesOneColor(0);

        // Создаем новую матрицу смежности размером, равным исходной:
        int **arr = new int*[Points.size()];
        for (int i = 0; i < Points.size(); i++)
        {
            arr[i] = new int[Points.size()];
        }

        // Копируем значения из исходной матрицы смежности в новую:
        for (int i = 0; i < Points.size(); i++)
        {
            for (int j = 0; j < Points.size(); j++)
            {
                arr[i][j] = WaysMatrix[i][j].size;
            }
        }

        // Создаем вектор для хранения ребер, которые будут частью оптимального маршрута:
        std::vector<SalesmansMethod::Edge> *Ways = new std::vector<SalesmansMethod::Edge>;

        // Создаем объект класса SalesmansMethod, передавая ему матрицу смежности, размер графа и вектор для хранения ребер оптимального маршрута:
        SalesmansMethod* Method = new SalesmansMethod(arr, Points.size(), Ways);

        // Запускаем метод коммивояжера:
        Method->mainFunction();

        // Удаляем объект Method:
        delete Method;

        // Устанавливаем красный цвет для ребер, входящих в оптимальный маршрут:
        for (int i = 0; i < (*Ways).size(); i++)
        {
            setLineColor((*Ways)[i].firstTop, (*Ways)[i].secondTop, 2);
        }

        // Удаляем вектор Ways:
        delete Ways;

        // Освобождаем выделенную память:
        for (int i = 0; i < Points.size(); i++)
        {
            delete[] arr[i];
        }
        delete[] arr;
    }
}

// Деструктор класса PointsAndMatrix:
PointsAndMatrix::~PointsAndMatrix()
{
    // В данном случае деструктор пуст, так как очистка памяти
    // происходит в методе deleteAll().
}
