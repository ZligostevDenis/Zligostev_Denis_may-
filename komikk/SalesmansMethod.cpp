//файл для работы с выводом в консоль
#include "SalesmansMethod.h" // Подключаем заголовочный файл SalesmansMethod.h

// Конструктор класса SalesmansMethod:
SalesmansMethod::SalesmansMethod(int** arr, int size, std::vector<Edge> *&ways)
    : sizeArr{ size + 1 }, sizeArrSecond{ size + 1 }, firstSizeArr{ size + 1 }, Ways{ ways }
{
    // Выделяем память под массивы:
    array = new int*[sizeArr]; // Массив для хранения матрицы расстояний
    arraySecond = new int*[sizeArrSecond]; // Массив для хранения копии матрицы расстояний
    for (int i = 0; i < sizeArr; i++)
    {
        array[i] = new int[sizeArr];
        arraySecond[i] = new int[sizeArr];
    }

    // Инициализируем массивы:
    // Первая строка и столбец содержат в себе названия соответствующих строк и столбцов
    for (int i = 0; i < sizeArr; i++)
    {
        for (int j = 0; j < sizeArr; j++)
        {
            if (i == 0)
            {
                // Заполняем первую строку (заголовки столбцов):
                array[i][j] = j - 1;
                arraySecond[i][j] = j - 1;
            }
            if (j == 0)
            {
                // Заполняем первый столбец (заголовки строк):
                array[i][j] = i - 1;
                arraySecond[i][j] = i - 1;
            }
            if (i > 0 && j > 0)
            {
                // Копируем значения из входной матрицы arr:
                array[i][j] = arr[i - 1][j - 1];
                arraySecond[i][j] = arr[i - 1][j - 1];
            }
        }
    }

    // Создаем массивы для хранения весов редукции строк (di) и столбцов (dj):
    di = new int[sizeArr - 1];
    dj = new int[sizeArr - 1];
    diSecond = new int[sizeArr - 1];
    djSecond = new int[sizeArr - 1];

    // Инициализируем di, dj, diSecond, djSecond значением 101:
    for (int i = 0; i < sizeArr - 1; i++)
    {
        di[i] = dj[i] = diSecond[i] = djSecond[i] = 101;
    }

    // Инициализируем переменные:
    //Ways = new std::vector<Edge>;
    HWays = 0; // Счетчик ребер в оптимальном маршруте
    H_current = 0; // Текущая оценка решения
    H_0 = 0; // Начальная оценка решения
    H_1 = 0; // Оценка решения после первой редукции
}

// Метод для нахождения минимального элемента в столбце j, исключая строку currI:
int SalesmansMethod::findMinElemColumn(int j, int currI)
{
    int min = 101; // Инициализируем минимальное значение
    // Перебираем все строки в столбце j:
    for (int i = 1; i < sizeArr; i++)
    {
        // Если элемент не равен -1 (ребро существует):
        if (array[i][j] != -1)
        {
            // Если currI равен -1, то рассматриваем все строки:
            if (currI == -1)
            {
                // Если текущий элемент меньше минимального, обновляем минимальное значение:
                if (array[i][j] < min)
                {
                    min = array[i][j];
                }
            }
            // Иначе, если currI не равен -1, пропускаем строку currI:
            else
            {
                if (i != currI)
                {
                    // Если текущий элемент меньше минимального, обновляем минимальное значение:
                    if (array[i][j] < min)
                    {
                        min = array[i][j];
                    }
                }
            }
        }
    }

    // Если currI равен -1 и минимальное значение не было обновлено, устанавливаем его в 0:
    if (currI == -1) { if (min == 101) min = 0; }
    // Иначе, если currI не равен -1 и минимальное значение не было обновлено, оставляем его равным 101:
    else { if (min == 101) min = 101; }

    // Возвращаем минимальное значение:
    return min;
}

// Метод для нахождения минимального элемента в строке i, исключая столбец currJ:
int SalesmansMethod::findMinElemRow(int i, int currJ)
{
    int min = 101; // Инициализируем минимальное значение
    // Перебираем все столбцы в строке i:
    for (int j = 1; j < sizeArr; j++)
    {
        // Если элемент не равен -1 (ребро существует):
        if (array[i][j] != -1)
        {
            // Если currJ равен -1, то рассматриваем все столбцы:
            if (currJ == -1)
            {
                // Если текущий элемент меньше минимального, обновляем минимальное значение:
                if (array[i][j] < min)
                {
                    min = array[i][j];
                }
            }
            // Иначе, если currJ не равен -1, пропускаем столбец currJ:
            else
            {
                if (j != currJ)
                {
                    // Если текущий элемент меньше минимального, обновляем минимальное значение:
                    if (array[i][j] < min)
                    {
                        min = array[i][j];
                    }
                }
            }
        }
    }

    // Если currJ равен -1 и минимальное значение не было обновлено, устанавливаем его в 0:
    if (currJ == -1) { if (min == 101) min = 0; }
    // Иначе, если currJ не равен -1 и минимальное значение не было обновлено, оставляем его равным 101:
    else { if (min == 101) min = 101; }

    // Возвращаем минимальное значение:
    return min;
}

// Метод для расчета весов строк (di):
void SalesmansMethod::findDi()
{
    // "Обнуляем" di:
    for (int i = 0; i < sizeArr - 1; i++)
    {
        di[i] = 101;
    }

    di_sum = 0; // Сумма весов строк

    // Вычисляем di для каждой строки:
    for (int i = 0; i < sizeArr - 1; i++)
    {
        di[i] = findMinElemRow(i + 1); // Находим минимальный элемент в строке i + 1
        di_sum += di[i]; // Добавляем di к общей сумме
    }
}

// Метод для расчета весов редукции столбцов (dj):
void SalesmansMethod::findDj()
{
    // "Обнуляем" dj:
    for (int j = 0; j < sizeArr - 1; j++)
    {
        dj[j] = 101;
    }

    dj_sum = 0; // Сумма весов редукции столбцов

    // Вычисляем dj для каждого столбца:
    for (int j = 0; j < sizeArr - 1; j++)
    {
        dj[j] = findMinElemColumn(j + 1); // Находим минимальный элемент в столбце j + 1
        dj_sum += dj[j]; // Добавляем dj к общей сумме
    }
}

// Метод для редукции матрицы расстояний:
void SalesmansMethod::reduceMatrix()
{
    // Вычисляем веса редукции строк (di):
    findDi();

    // Вычитаем di из каждой ячейки соответствующей строки:
    for (int i = 1; i < sizeArr; i++)
    {
        for (int j = 1; j < sizeArr; j++)
        {
            if (array[i][j] != -1) // Если ребро существует
            {
                array[i][j] -= di[i - 1];
            }
        }
    }

    // Вычисляем веса редукции столбцов (dj):
    findDj();

    // Вычитаем dj из каждой ячейки соответствующего столбца:
    for (int j = 1; j < sizeArr; j++)
    {
        for (int i = 1; i < sizeArr; i++)
        {
            if (array[i][j] != -1) // Если ребро существует
            {
                array[i][j] -= dj[j - 1];
            }
        }
    }
}

// Метод для поиска нулей в матрице:
void SalesmansMethod::findZeros()
{
    // Очищаем вектор zerosArray, который хранит информацию о нулях:
    zerosArray.clear();

    int J = 0; // Не используется

    // Перебираем все ячейки матрицы:
    for (int i = 1; i < sizeArr; i++)
    {
        J = i; // Не используется
        for (int j = 1; j < sizeArr; j++)
        {
            // Если ячейка равна 0 (ребро с минимальной стоимостью):
            if (array[i][j] == 0)
            {
                // Добавляем новый объект Zero в вектор zerosArray:
                // - quantity: сумма минимальных элементов в строке i и столбце j,
                //   исключая текущую ячейку (i, j)
                // - i: номер строки
                // - j: номер столбца
                zerosArray.push_back(Zero((findMinElemRow(i, j) + findMinElemColumn(j, i)), i, j));
            }
        }
    }
}

// Метод, идентичный findZeros():
void SalesmansMethod::findZeros1()
{
    zerosArray.clear(); // Очищаем вектор zerosArray
    int J = 0; // Не используется

    // Перебираем все ячейки матрицы:
    for (int i = 1; i < sizeArr; i++)
    {
        J = i; // Не используется
        for (int j = 1; j < sizeArr; j++)
        {
            if (array[i][j] == 0)
            {
                zerosArray.push_back(Zero((findMinElemRow(i, j) + findMinElemColumn(j, i)), i, j));
            }
        }
    }
}

// Метод для поиска нуля с максимальной оценкой:
int SalesmansMethod::findBiggerZero()
{
    int numb = 0; // Индекс нуля с максимальной оценкой в векторе zerosArray

    // Перебираем все нули в векторе zerosArray:
    for (int i = 0; i < zerosArray.size(); i++)
    {
        // Если оценка текущего нуля больше, чем оценка нуля с индексом numb, обновляем numb:
        if (zerosArray[i].quantity > zerosArray[numb].quantity)
        {
            numb = i;
        }
    }

    // Возвращаем индекс нуля с максимальной оценкой:
    return numb;
}

// Метод для исключения ребра (i, j) из дальнейшего рассмотрения:
void SalesmansMethod::exclusionSimilarEdge(int indexI, int indexJ, bool choseArr)
{
    int I = -1;
    int J = -1;

    // Если choseArr == true, работаем с массивом array:
    if (choseArr == 1)
    {
        // Находим индексы столбца J и строки I в массиве array,
        // соответствующие indexI и indexJ в массиве arraySecond:
        for (int i = 1; i < sizeArr; i++)
        {
            if (arraySecond[indexI][0] == array[0][i])
            {
                J = i;
            }
            if (arraySecond[0][indexJ] == array[i][0])
            {
                I = i;
            }
        }

        // Если индексы I и J найдены, устанавливаем array[I][J] в -1,
        // исключая ребро (I, J) из дальнейшего рассмотрения:
        if (I != -1 && J != -1) { array[I][J] = -1; }
    }
    // Иначе, работаем с массивом arraySecond:
    else
    {
        // Устанавливаем arraySecond[indexI][indexJ] в -1, исключая ребро (indexI, indexJ)
        // из дальнейшего рассмотрения:
        arraySecond[indexI][indexJ] = -1;
    }
}

// Метод для исключения ребра (indexI, indexJ) из матрицы array
// и сдвига элементов для уменьшения размера матрицы:
void SalesmansMethod::edgesExclusion(int indexI, int indexJ)
{
    // Копируем текущую матрицу array в arraySecond,
    // перед тем как провести выключение ребра:
    for (int i = 0; i < sizeArr; i++)
    {
        for (int j = 0; j < sizeArr; j++)
        {
            arraySecond[i][j] = array[i][j];
        }
    }

    // Копируем размер матрицы array в sizeArrSecond:
    sizeArrSecond = sizeArr;

    // Копируем массивы di и dj в diSecond и djSecond:
    for (int i = 0; i < sizeArrSecond - 1; i++)
    {
        diSecond[i] = di[i];
        djSecond[i] = dj[i];
    }

    // Исключаем ребро (indexI, indexJ) и сдвигаем элементы:
    int I = 0, J = 0;
    // Перебираем строки матрицы:
    for (int i = 1; i < sizeArr; i++)
    {
        I = i;
        // Если текущая строка не совпадает с indexI:
        if (i != indexI)
        {
            // Если текущая строка больше indexI, уменьшаем I на 1
            // (так как строка indexI будет удалена):
            if (i > indexI) { --I; }

            // Перебираем столбцы матрицы:
            for (int j = 1; j < sizeArr; j++)
            {
                J = j;
                // Если текущий столбец не совпадает с indexJ:
                if (j != indexJ)
                {
                    // Если текущий столбец больше indexJ, уменьшаем J на 1
                    // (так как столбец indexJ будет удален):
                    if (j > indexJ) { --J; }

                    // Копируем элемент из arraySecond в array, учитывая сдвиг:
                    array[I][J] = arraySecond[i][j];
                }
            }
        }
    }

    // Уменьшаем размер матрицы array на 1:
    --sizeArr;

    // Проводим смещение заголовков строк и столбцов:
    // Первая строка и столбец матрицы содержат в себе названия соответствующих строк и столбцов
    // Смещаем заголовки строк, начиная с indexI:
    for (int i = indexI; i < sizeArr; i++)
    {
        array[i][0] = array[i + 1][0];
    }

    // Смещаем заголовки столбцов, начиная с indexJ:
    for (int j = indexJ; j < sizeArr; j++)
    {
        array[0][j] = array[0][j + 1];
    }

    // Обновляем di и dj, удаляя элементы, соответствующие
    // удаленной строке и столбцу:
    // Смещаем элементы di, начиная с indexI - 1:
    for (int i = indexI - 1; i < sizeArr - 1; i++)
    {
        di[i] = di[i + 1];
    }

    // Смещаем элементы dj, начиная с indexJ - 1:
    for (int j = indexJ - 1; j < sizeArr - 1; j++)
    {
        dj[j] = dj[j + 1];
    }
}

// Метод для выбора матрицы, с которой будет продолжена работа:
void SalesmansMethod::chooseMatrix(int chose)
{
    // Если chose == 1, продолжаем работать с текущей матрицей array
    // и устанавливаем H_current в H_1:
    if (chose == 1)
    {
        H_current = H_1;
    }
    // Иначе, восстанавливаем матрицу array из копии arraySecond
    // и устанавливаем H_current в H_0:
    else
    {
        sizeArr = sizeArrSecond;
        for (int i = 0; i < sizeArrSecond; i++)
        {
            for (int j = 0; j < sizeArrSecond; j++)
            {
                array[i][j] = arraySecond[i][j];
            }
        }

        // Восстанавливаем di и dj из diSecond и djSecond:
        for (int i = 0; i < sizeArr - 1; i++)
        {
            di[i] = diSecond[i];
            dj[i] = djSecond[i];
        }

        H_current = H_0;
    }
}


// Основная функция алгоритма метода ветвей и границ:
void SalesmansMethod::mainFunction()
{
    // Редуцируем исходную матрицу расстояний:
    reduceMatrix();

    // Вычисляем начальную оценку решения (H_current):
    H_current = di_sum + dj_sum;

    int numbOfZeroMax = 0; // Индекс нуля с максимальной оценкой
    bool isH_0 = false; // Флаг, указывающий, работаем ли мы с веткой H_0
    bool flag = true; // Флаг продолжения цикла
    // Цикл продолжается, пока размер матрицы не станет равен 1:
    while (flag)
    {
        // Если isH_0 == false, работаем с текущей матрицей:
        if (isH_0 == false)
        {
            // Находим нули в редуцированной матрице:
            findZeros();
        }
        // Иначе, работаем с веткой H_0:
        else
        {
            // Удаляем последний выбранный ноль из вектора zerosArray:
            zerosArray.erase(zerosArray.begin() + numbOfZeroMax);

            // Если вектор zerosArray пуст, значит, в ветке H_0
            // не осталось нулей, и нужно вернуться к предыдущей ветке:
            if (zerosArray.size() == 0)
            {
                //findZeros1(); // Не используется
            }
        }

        // Выбираем ноль с наибольшей оценкой:
        numbOfZeroMax = findBiggerZero();
        Zero zeroMax = zerosArray[numbOfZeroMax];

        // Создаем две ветки:
        // 1. Ветка H_0: исключаем ребро (zeroMax.i, zeroMax.j)
        H_0 = H_current + zeroMax.quantity;

        // 2. Ветка H_1: включаем ребро (zeroMax.i, zeroMax.j)
        edgesExclusion(zeroMax.i, zeroMax.j);
        exclusionSimilarEdge(zeroMax.i, zeroMax.j, 1);

        //exclusionSimilarEdge(zeroMax.i, zeroMax.j, 0); // Не используется
        //exclusionSimilarEdge(zeroMax.i, zeroMax.j, 1); // Дублирует предыдущую строку

        // Редуцируем матрицу для ветки H_1:
        reduceMatrix();

        // Вычисляем оценку H_1:
        H_1 = H_current + di_sum + dj_sum;

        // Выбираем ветку с меньшей оценкой:
        // Если H_1 <= H_0, выбираем ветку H_1:
        if (H_1 <= H_0)
        {
            isH_0 = false;
            // Добавляем ребро (zeroMax.i, zeroMax.j) в оптимальный маршрут:
            (*Ways).push_back(Edge(arraySecond[zeroMax.i][0], arraySecond[0][zeroMax.j]));
            // Продолжаем работать с матрицей array (ветка H_1):
            chooseMatrix(1);
        }
        // Иначе, выбираем ветку H_0:
        else
        {
            isH_0 = true;
            // Возвращаемся к матрице arraySecond (ветка H_0):
            chooseMatrix(0);
            // Вычитаем оценку zeroMax.quantity из H_current,
            // так как ребро (zeroMax.i, zeroMax.j) было исключено:
            H_current -= zeroMax.quantity;
        }

        // Если размер матрицы стал равен 1, значит, решение найдено:
        if (sizeArr == 1)
        {
            flag = false;
        }
    }
}

// Деструктор класса SalesmansMethod:
SalesmansMethod::~SalesmansMethod()
{
    // Освобождаем выделенную память:
    for (int i = 0; i < sizeArr; i++)
    {
        delete[] array[i];
        delete[] arraySecond[i];
    }

    delete[] array;
    delete[] arraySecond;

    delete[] di;
    delete[] dj;
    delete[] diSecond;
    delete[] djSecond;
}
