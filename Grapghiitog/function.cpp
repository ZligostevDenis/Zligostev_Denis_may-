#include "function.h" // Подключаем заголовочный файл главного окна
#include "ui_function.h" // Подключаем файл с описанием интерфейса

#include "graph.h" // Подключаем класс графа

#include <QDebug> // Подключаем для отладки
#include <QMouseEvent> // Подключаем для обработки событий мыши

#include <QGraphicsEllipseItem> // Подключаем для работы с графическими элементами

// Конструктор класса Dialog
Dialog::Dialog(QWidget *parent) :
    QDialog(parent), // Вызываем конструктор родительского класса QDialog
    ui(new Ui::Dialog()) // Создаем объект интерфейса Ui::Dialog
{
    ui->setupUi(this); // Инициализируем интерфейс

    scene = new QGraphicsScene(this); // Создаем сцену для графического представления графа
    ui->graphicsView->setScene(scene); // Устанавливаем сцену в graphicsView

    // Устанавливаем цвет фона для кнопок
    ui->btnAddEdge->setStyleSheet("background-color:" + QColor(255, 255, 255).name());
    ui->btnAddVertex->setStyleSheet("background-color:" + QColor(255, 255, 255).name());
    ui->btnAdj->setStyleSheet("background-color:" + QColor(255, 255, 255).name());
    ui->btnDelete->setStyleSheet("background-color:" + QColor(255, 255, 255).name());
    ui->btnBFS->setStyleSheet("background-color:" + QColor(255, 255, 255).name());
    ui->btnDFS->setStyleSheet("background-color:" + QColor(255, 255, 255).name());
    ui->btnDijkstra->setStyleSheet("background-color:" + QColor(255, 255, 255).name());
}

// Деструктор класса Dialog
Dialog::~Dialog()
{
    delete ui; // Удаляем объект интерфейса
}

// Обработчик нажатия на кнопку "Добавить вершину"
void Dialog::on_btnAddVertex_clicked() {
    int num = vertices.size(); // Получаем количество вершин
    vert = new graphVertex(num); // Создаем новую вершину с индексом num
    vert->setGraph(&graph); // Устанавливаем граф для вершины
    vertices.push_back(vert); // Добавляем вершину в список вершин
    scene->addItem(vert); // Добавляем вершину на сцену
    if (graph.insertVertex(num)) qDebug() << "вершина добавлена!"; // Добавляем вершину в граф и выводим сообщение об успехе
}

// Обработчик нажатия на кнопку "Матрица смежности"
void Dialog::on_btnAdj_clicked()
{
    adj = new Adjacency; // Создаем объект для отображения матрицы смежности
    adj->setWindowTitle("Матрица смежности для графа"); // Устанавливаем заголовок окна
    // Настраиваем цвет фона окна
    QPalette Pal(QColor(255, 255, 255));
    adj->setPalette(Pal);
    adj->setAutoFillBackground(true);
    // Передаем данные о графе в объект для отображения матрицы смежности
    adj->setAdj(graph.getAdj());
    adj->setSize(graph.getVertexList().size());
    // Собираем имена вершин
    QVector<QString> names;
    for (auto elem : graph.getVertexList()){
        names.push_back(QString::number(elem));
    }
    adj->rebuild(names); // Перестраиваем матрицу смежности
    adj->show(); // Отображаем окно с матрицей смежности
}

// Обработчик нажатия на кнопку "Добавить ребро"
void Dialog::on_btnAddEdge_clicked()
{
    graphVertex *node1, *node2; // Указатели на вершины, между которыми будет создано ребро
    int vert1, vert2; // Индексы вершин

    if (ui->graphicsView->scene()->selectedItems().size() == 1) { // Если выбрана только одна вершина
        node1 = dynamic_cast<graphVertex *> (ui->graphicsView->scene()->selectedItems().at(0)); // Получаем указатель на выбранную вершину
        node1->setPressed(true); // Помечаем вершину как нажатую
        if (for_draw.isEmpty()) for_draw.push_back(node1); // Если список вершин для рисования пуст, добавляем выбранную вершину
        else if (for_draw.front() != node1 && for_draw.front() != nullptr) { // Если в списке уже есть вершина и она не совпадает с выбранной
            /// ВЫЗОВ ДИАЛОГОВОГО ОКНА ///
            int result = 1; // Вес ребра по умолчанию
            GetWeight gw; // Создаем диалоговое окно для ввода веса ребра
            gw.setWindowTitle("Вес выбранного ребра"); // Устанавливаем заголовок окна
            // Настраиваем цвет фона окна
            QPalette Pal(QColor(255, 255, 255));
            gw.setPalette(Pal);
            gw.setAutoFillBackground(true);
            if (gw.exec()) result = gw.weight; // Если пользователь ввел вес, сохраняем его
            if (result == 0) result = 1; // Если вес равен 0, устанавливаем вес 1

            node2 = for_draw.front(); // Получаем вторую вершину из списка для рисования
            vert1 = node1->getNum(); vert2 = node2->getNum(); // Получаем индексы вершин
            // Добавляем ребра в граф
            graph.InsertEdge(vert2, vert1, result);
            graph.InsertEdge(vert1, vert2, result);
            edge = new Edge(node1, node2); // Создаем новое ребро между вершинами
            edge->setGraph(&graph); // Устанавливаем граф для ребра
            // Снимаем пометку "нажата" с вершин
            if (node1->pressed() == true) node1->setPressed(false);
            if (node2->pressed() == true) node2->setPressed(false);
            edge->setContent(result); // Устанавливаем вес ребра
            scene->addItem(edge); // Добавляем ребро на сцену
            edges.push_back(edge); // Добавляем ребро в список ребер
            for_draw.pop_back(); // Удаляем вторую вершину из списка для рисования
        }
    }
    ui->graphicsView->scene()->clearSelection(); // Снимаем выделение с вершин
}

void Dialog::on_btnDelete_clicked() { // Обработчик нажатия на кнопку "Удалить"
    if (ui->graphicsView->scene()->selectedItems().size()!=0){ // Если на сцене есть выбранные элементы
        int last = ui->graphicsView->scene()->selectedItems().size()-1; // Получаем индекс последнего выбранного элемента
        auto current = ui->graphicsView->scene()->selectedItems().at(last); // Получаем указатель на последний выбранный элемент
        delete current; // Удаляем элемент
    }
}

void Dialog::on_btnBFS_clicked() { // Обработчик нажатия на кнопку "BFS"
    int current = 0; // Индекс вершины, с которой начинается обход
    GetWeight gw; // Создаем диалоговое окно для ввода номера вершины
    // Настраиваем цвет фона диалогового окна
    QPalette Pal1(QColor(255, 255, 255));
    gw.setPalette(Pal1);
    gw.setAutoFillBackground(true);
    gw.setWindowTitle("Введие номер изначальной вершины"); // Устанавливаем заголовок окна
    if (gw.exec()) current = gw.weight; // Если пользователь ввел номер вершины, сохраняем его
    if (current < graph.getVertexList().size()){ // Если номер вершины корректен
        ShowInfo info; // Создаем окно для вывода результата обхода
        // Настраиваем цвет фона окна
        QPalette Pal(QColor(255, 255, 255));
        info.setPalette(Pal);
        info.setAutoFillBackground(true);
        QString res = ""; // Строка для хранения результата обхода
        QVector<bool> visited(graph.getVertexList().size()); // Вектор для отметки посещенных вершин
        for (auto it = visited.begin(); it !=visited.end(); ++it) *it = false; // Изначально все вершины не посещены
        graph.BFS(current, visited, res); // Выполняем обход в ширину
        info.setInfo(res); // Устанавливаем результат обхода в окно
        if (!info.exec()) qDebug() << "Error"; // Отображаем окно с результатом
    }
}

void Dialog::on_btnDFS_clicked() { // Обработчик нажатия на кнопку "DFS"
    // Аналогично on_btnBFS_clicked, но выполняется обход в глубину
    int current = 0;
    GetWeight gw;
    QPalette Pal1(QColor(255, 255, 255));
    gw.setPalette(Pal1);
    gw.setAutoFillBackground(true);
    gw.setWindowTitle("Введите номер изначальной вершины");
    if (gw.exec()) current = gw.weight;
    if (current < graph.getVertexList().size()){
        ShowInfo info;
        QPalette Pal(QColor(255, 255, 255));
        info.setPalette(Pal);
        info.setAutoFillBackground(true);
        QString res = "";
        QVector<bool> visited(graph.getVertexList().size());
        for (auto it = visited.begin(); it !=visited.end(); ++it) *it = false;
        graph.DFS(current, visited, res);
        info.setInfo(res);
        if (!info.exec()) qDebug() << "Ошибка";
    }
}

void Dialog::on_btnDijkstra_clicked() { // Обработчик нажатия на кнопку "Алгоритм Дейкстры"
    // Аналогично предыдущим обработчикам, но выполняется алгоритм Дейкстры
    int current = 0;
    GetWeight gw;
    QPalette Pal1(QColor(255, 255, 255));
    gw.setPalette(Pal1);
    gw.setAutoFillBackground(true);
    gw.setWindowTitle("Введите номер изначальной вершины");
    if (gw.exec()) current = gw.weight;
    if (current < graph.getVertexList().size()){
        ShowInfo info;
        QPalette Pal(QColor(255, 255, 255));
        info.setPalette(Pal);
        info.setAutoFillBackground(true);
        QString res = "";
        graph.Dijkstra(current, res);
        info.setInfo(res);
        if (!info.exec()) qDebug() << "Ошибка";
    }
}

void Dialog::on_graphicsView_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint)
{

}

