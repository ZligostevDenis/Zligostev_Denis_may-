#include "mainwindow.h" // Подключение заголовочного файла главного окна
#include "ui_mainwindow.h" // Подключение заголовочного файла с описанием интерфейса

// Конструктор класса MainWindow
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) // Вызов конструктора родительского класса
    , ui(new Ui::MainWindow) // Инициализация объекта ui, отвечающего за интерфейс
{
    ui->setupUi(this); // Инициализация интерфейса

    scene = new PaintScene(); // Создание объекта графической сцены
    // Установка области сцены в соответствии с размером graphicsView
    scene->setSceneRect(0, 0, ui->graphicsView->size().width() - 15, ui->graphicsView->size().height() - 15);
    ui->graphicsView->setScene(scene); // Установка сцены для graphicsView

    Matrix = new PointsAndMatrix(); // Создание объекта для работы с графом

    // Подключение сигналов и слотов:
    connect(scene, &PaintScene::signalGetPtrMatrix, this, &MainWindow::sendPtrMatrix); // Передача указателя на объект Matrix в сцену

    connect(Matrix, &PointsAndMatrix::signalSendMatrixSize, this, &MainWindow::slotGetMatrixSize); // Обновление выпадающих списков при изменении размера матрицы

    this->setFixedSize(1024, 600); // Установка фиксированного размера окна
}

// Деструктор класса MainWindow
MainWindow::~MainWindow()
{
    delete ui; // Удаление объекта ui
}

// Метод для передачи указателя на объект Matrix в сцену
void MainWindow::sendPtrMatrix(PointsAndMatrix*& out_ptrMatrix)
{
    out_ptrMatrix = Matrix;
}

// Слот для обновления выпадающих списков при изменении размера матрицы
void MainWindow::slotGetMatrixSize(int size)
{
    // Очистка выпадающих списков
    ui->comboBox->clear();
    ui->comboBox_2->clear();
    ui->comboBox_3->clear();
    ui->comboBox_4->clear();
    ui->comboBox_5->clear();

    // Заполнение выпадающих списков номерами вершин
    if (size != -1)
    {
        for (int i = 0; i < size; i++)
        {
            ui->comboBox->addItem(QString::number(i));
            ui->comboBox_2->addItem(QString::number(i));
            ui->comboBox_4->addItem(QString::number(i));
        }
    }
}

// Слот для обработки нажатия кнопки удаления вершины
void MainWindow::on_pushButton_clicked()
{
    // Проверка, выбрана ли вершина в выпадающем списке
    if (ui->comboBox->currentIndex() >= 0 && Matrix->Points.size() >= 2)
    {
        // Проверка, существует ли цикл, содержащий выбранную вершину
        if (Matrix->HamiltonianGraph(ui->comboBox->currentIndex()))
        {
            Matrix->deletePoint(ui->comboBox->currentIndex()); // Удаление вершины
        }
        else
        {
            qDebug() << "Нет цикла проходящего через все вершины"; // Вывод сообщения об отсутствии такого цикла
        }
    }
}

// Слот для обработки нажатия кнопки удаления ребра
void MainWindow::on_pushButton_2_clicked()
{
    int i = ui->comboBox_2->currentText().toInt(); // Индекс первой вершины ребра
    int j = ui->comboBox_3->currentText().toInt(); // Индекс второй вершины ребра

    // Проверка, существуют ли вершины и выбрано ли ребро
    if (Matrix->Points.size() > 0 && i >= 0 && j >= 0)
    {
        // Проверка, существует ли цикл, содержащий выбранное ребро
        if (Matrix->HamiltonianGraph(i, j))
        {
            Matrix->deleteLine(i, j); // Удаление ребра
        }
        else
        {
            qDebug() << "Нет цикла проходящего через все вершины"; // Вывод сообщения об отсутствии гамильтонова цикла
        }
    }
}

// Метод для обновления выпадающего списка comboBox_3 (список ребер, исходящих из вершины, выбранной в comboBox_2)
void MainWindow::updateComboBox_3(int indexOfComboBox_2)
{
    if (indexOfComboBox_2 >= 0)
    {
        ui->comboBox_3->clear(); // Очистка comboBox_3

        // Заполнение comboBox_3 номерами вершин, с которыми существует ребро из вершины indexOfComboBox_2
        for (int j = 0; j < Matrix->Points.size(); j++)
        {
            if (Matrix->WaysMatrix[indexOfComboBox_2][j].size != -1)
            {
                ui->comboBox_3->addItem(QString::number(j));
            }
        }
    }
}

// Метод для обновления выпадающего списка comboBox_5 (список вершин, не соединенных ребром с вершиной, выбранной в comboBox_4)
void MainWindow::updateComboBox_5(int indexOfComboBox_4)
{
    if (indexOfComboBox_4 >= 0) // Проверка, выбрана ли вершина в comboBox_4
    {
        ui->comboBox_5->clear(); // Очистка comboBox_5

        // Заполнение comboBox_5 номерами вершин, не соединенных ребром с вершиной indexOfComboBox_4
        for (int j = 0; j < Matrix->Points.size(); j++)
        {
            // Проверка, что вершины разные и между ними нет ребра (size == -1)
            if (Matrix->WaysMatrix[indexOfComboBox_4][j].size == -1 && indexOfComboBox_4 != j)
            {
                ui->comboBox_5->addItem(QString::number(j));
            }
        }
    }
}

// Слот для обработки изменения индекса в comboBox_2 (выбор первой вершины ребра)
void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    updateComboBox_3(index); // Обновление comboBox_3 (список ребер, исходящих из выбранной вершины)
}

// Слот для обработки изменения индекса в comboBox_3 (выбор второй вершины ребра)
void MainWindow::on_comboBox_3_currentIndexChanged(const QString &arg1)
{
    ui->lineEdit->clear(); // Очистка lineEdit (поле для ввода длины ребра)

    int i = ui->comboBox_2->currentIndex(); // Индекс первой вершины ребра
    int j = arg1.toInt(); // Индекс второй вершины ребра

    // Проверка, выбраны ли обе вершины ребра
    if (i >= 0 && j >= 0)
    {
        Matrix->setAllLinesOneColor(0); // Установка стандартного цвета для всех ребер
        Matrix->setLineColor(i, j, 1); // Выделение выбранного ребра другим цветом
        ui->lineEdit->setText(QString::number(Matrix->WaysMatrix[i][j].size)); // Отображение длины ребра в lineEdit
    }
}

// Слот для обработки изменения текста в lineEdit (изменение длины ребра)
void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    int i = ui->comboBox_2->currentIndex(); // Индекс первой вершины ребра
    int j = ui->comboBox_3->currentText().toInt(); // Индекс второй вершины ребра

    // Проверка, что введенная длина ребра корректна (число от 1 до 100)
    if (arg1.toInt() > 0 && arg1.toInt() < 101 && i >= 0 && j >= 0)
    {
        Matrix->setWaySize(i, j, arg1.toInt()); // Установка новой длины ребра
    }
}

// Слот для обработки изменения состояния checkBox (включение/выключение зон вокруг вершин)
void MainWindow::on_checkBox_stateChanged(int arg1)
{
    Matrix->setZones(arg1); // Установка радиуса зон вокруг вершин
}

// Слот для обработки изменения индекса в comboBox (выбор вершины для отображения степени)
void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if (index >= 0) // Проверка, выбрана ли вершина
    {
        ui->label_4->clear(); // Очистка label_4 (отображение степени вершины)
        ui->label_4->setText(QString::number(Matrix->degreeOfTop(index))); // Отображение степени вершины в label_4
        Matrix->setAllPointsOneColor(0); // Установка стандартного цвета для всех вершин
        Matrix->setPointColor(index, 1); // Выделение выбранной вершины другим цветом
    }
}

// Слот для обработки нажатия кнопки "pushButton_3" (удаление всех элементов графа)
void MainWindow::on_pushButton_3_clicked()
{
    Matrix->deleteAll(); // Удаление всех вершин и ребер графа
    // Очистка всех выпадающих списков
    ui->comboBox->clear();
    ui->comboBox_2->clear();
    ui->comboBox_3->clear();
    ui->comboBox_4->clear();
    ui->comboBox_5->clear();
}

// Слот для обработки изменения индекса в comboBox_4 (выбор первой вершины для добавления ребра)
void MainWindow::on_comboBox_4_currentIndexChanged(int index)
{
    updateComboBox_5(index); // Обновление comboBox_5 (список вершин, не соединенных ребром с выбранной вершиной)
}

// Слот для обработки нажатия кнопки "pushButton_4" (добавление ребра)
void MainWindow::on_pushButton_4_clicked()
{
    int i = ui->comboBox_4->currentIndex(); // Индекс первой вершины ребра
    int j = ui->comboBox_5->currentText().toInt(); // Индекс второй вершины ребра

    // Проверка, что вершины разные
    if (i != j)
    {
        // Проверка, что введенная длина ребра корректна (число от 1)
        if (ui->lineEdit_2->text().toInt() > 0 && ui->lineEdit_2->text().toInt() > 0 && i >= 0 && j >= 0)
        {
            Matrix->addLine(i, j, ui->lineEdit_2->text().toInt()); // Добавление ребра в граф
            scene->addItem_Line(i, j); // Добавление графического представления ребра на сцену
        }
        else
        {
            QMessageBox::warning(0, "Представление ребра", "неверно указанное значение ребра, нужно больше нуля"); // Вывод сообщения об ошибке
        }
    }
}

// Слот для обработки нажатия кнопки "pushButton_5" (запуск метода коммивояжера)
void MainWindow::on_pushButton_5_clicked()
{
    Matrix->ActivateSalesmansMethod(); // Запуск метода коммивояжера
}
