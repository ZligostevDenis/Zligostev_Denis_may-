#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <cmath>
#include <string>

#include "BinaryTree.h"

// Конструктор главного окна
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) // Инициализация базового класса QMainWindow
    , ui(new Ui::MainWindow) // Создание объекта пользовательского интерфейса
{
    ui->setupUi(this); // Инициализация пользовательского интерфейса из файла формы

    QGraphicsScene* scene = CreateScene(nullptr); // Создание сцены для отображения дерева (без выделенного узла)
    ui->graphicsView->setScene(scene); // Установка сцены в graphicsView для отображения
}

// Деструктор главного окна
MainWindow::~MainWindow()
{
    delete ui; // Удаление объекта пользовательского интерфейса
}

// Рекурсивная функция для создания графического представления дерева
void preOrderTreeSceneCreate(Tree* tree, QGraphicsScene* Scene, int ell_r, int lvlH, int lvlW, int lvlH_delt, int lvlW_delt, bool left, Tree* to_paint) {
    if(tree != nullptr) { // Проверка, не пустой ли узел
        int cur_lvlW_delt; // Переменная для хранения смещения по горизонтали для текущего уровня

        // Определение смещения для текущего уровня в зависимости от того, левый это потомок или правый
        if(left) { // Если узел левый потомок
            if(lvlW_delt < 25) { // Если смещение меньше 25 (слишком близко к центру)
                cur_lvlW_delt = lvlW_delt + 50; // Увеличиваем смещение на 50
                lvlW_delt = 25; // Устанавливаем минимальное значение смещения
            }
            else
                cur_lvlW_delt = lvlW_delt + 50; // Иначе просто увеличиваем смещение на 50
        }
        else { // Если узел правый потомок
            if(lvlW_delt < 25){ // Если смещение меньше 25 (слишком близко к центру)
                cur_lvlW_delt = lvlW_delt * -1 - 50; // Уменьшаем смещение на 50 (в отрицательную сторону)
                lvlW_delt = 25; // Устанавливаем минимальное значение смещения
            }
            else
                cur_lvlW_delt = (lvlW_delt + 50) * -1; // Иначе уменьшаем смещение на 50 (в отрицательную сторону)
        }

        // Если у узла есть родитель, рисуем ребро к нему
        if(tree->parent != nullptr) {
            QGraphicsLineItem *edge = Scene->addLine(lvlW, lvlH, lvlW + cur_lvlW_delt,lvlH - lvlH_delt); // Создаем линию (ребро) между текущим узлом и его родителем
            QPen PenEdge(Qt::black); // Создаем перо черного цвета для ребра
            edge->setPen(PenEdge); // Устанавливаем перо для ребра
        }

        // Рекурсивные вызовы для левого и правого поддеревьев
        preOrderTreeSceneCreate(tree->left, Scene, ell_r, lvlH + lvlH_delt, lvlW - lvlW_delt, lvlH_delt, lvlW_delt - 50, true, to_paint);
        preOrderTreeSceneCreate(tree->right, Scene, ell_r, lvlH + lvlH_delt, lvlW + lvlW_delt, lvlH_delt, lvlW_delt - 50, false, to_paint);

        // Создание графического представления узла
        QGraphicsEllipseItem *ELL = Scene->addEllipse(lvlW - ell_r/2, lvlH - ell_r/2, ell_r, ell_r); // Создаем эллипс для представления узла
        QPen penELL(Qt::black); // Создаем перо черного цвета для эллипса
        QBrush brushELL(QColor(168, 228, 160)); // Создаем кисть зеленого цвета для эллипса

        // Проверка, нужно ли выделить текущий узел
        if(to_paint != nullptr) { // Если есть узел, который нужно выделить
            if(to_paint->data == tree->data) // Если текущий узел совпадает с узлом для выделения
                brushELL = QBrush(QColor(100, 150, 153)); // Устанавливаем кисть серого цвета для выделения
        }

        ELL->setPen(penELL); // Устанавливаем перо для эллипса
        ELL->setBrush(brushELL); // Устанавливаем кисть для эллипса

        // Добавление текста с значением узла
        int text_delt = std::to_string(tree->data).size(); // Вычисляем смещение для текста в зависимости от количества цифр
        QGraphicsTextItem *text = Scene->addText(QString::number(tree->data)); // Создаем текстовый элемент с значением узла
        text->setDefaultTextColor(Qt::black); // Устанавливаем цвет текста на черный
        text->setPos(lvlW - 5 - 4 * text_delt, lvlH - 12); // Устанавливаем позицию текста
    }
    else {
        return; // Если узел пустой, выходим из рекурсии
    }
}

// Функция для создания графической сцены с деревом
QGraphicsScene* MainWindow::CreateScene(Tree* to_paint) {
    int ell_r = 40; // Радиус эллипса для узла
    int lvlH = 0; // Начальная высота
    int lvlW = 0; // Начальная ширина
    int lvlH_delt = 80; // Вертикальное расстояние между уровнями
    int lvlW_delt = 120; // Горизонтальное расстояние между узлами на одном уровне
    QGraphicsScene* new_Scene = new QGraphicsScene; // Создание новой сцены
    preOrderTreeSceneCreate(T.root, new_Scene, ell_r, lvlH, lvlW, lvlH_delt, lvlW_delt, false, to_paint); // Рекурсивное построение дерева на сцене
    return new_Scene; // Возврат созданной сцены
}



void preOrderQStringCreate(Tree* tree, QString* qstr) {
    // Функция для создания строки с элементами дерева в префиксном порядке
    if(tree != nullptr) {
        *qstr += QString::number(tree->data);
        *qstr += " ";
        preOrderQStringCreate(tree->left, qstr);
        preOrderQStringCreate(tree->right, qstr);
    }
    else
        return;
}

void simOrderQStringCreate(Tree* tree, QString* qstr) {
    // Функция для создания строки с элементами дерева в инфиксном порядке
    if(tree != nullptr) {
        simOrderQStringCreate(tree->left, qstr);
        *qstr += QString::number(tree->data);
        *qstr += " ";
        simOrderQStringCreate(tree->right, qstr);
    }
    else
        return;
}

void postOrderQStringCreate(Tree* tree, QString* qstr) {
    // Функция для создания строки с элементами дерева в постфиксном порядке
    if(tree != nullptr) {
        postOrderQStringCreate(tree->left, qstr);
        postOrderQStringCreate(tree->right, qstr);
        *qstr += QString::number(tree->data);
        *qstr += " ";
    }
    else
        return;
}

void MainWindow::clear_status() {
    // Очистка статуса и результата отображения
    ui->search_status_label->setText("");
    ui->Order_result_textBrowser->setText("");
}

void MainWindow::on_insert_btn_clicked() {
    // Обработчик нажатия кнопки вставки элемента в дерево
    QGraphicsScene *prev_scene = ui->graphicsView->scene();
    clear_status();
    int to_add = ui->inser_textEdit->toPlainText().toInt();
    if(T.root == nullptr)
        T.root = new Tree(to_add);
    else
        T.insert(to_add);
    ui->inser_textEdit->setText("");
    QGraphicsScene *new_Scene = CreateScene(nullptr);
    ui->graphicsView->setScene(new_Scene);
    if(prev_scene) delete prev_scene;
}


void MainWindow::on_search_btn_clicked() {
    // Обработчик нажатия кнопки поиска элемента в дереве
    QGraphicsScene *prev_scene = ui->graphicsView->scene();
    clear_status(); // Очистка статуса и результата отображения
    Tree* found = T.find(ui->search_textEdit->toPlainText().toInt()); // Поиск элемента в дереве
    QGraphicsScene *new_Scene;
    if(found != nullptr) {
        ui->search_status_label->setText("Элемент найден"); // Установка статуса "Элемент найден"
        new_Scene = CreateScene(found); // Создание сцены с найденным элементом
    }
    else {
        ui->search_status_label->setText("Элемент не найден"); // Установка статуса "Элемент не найден"
        new_Scene = CreateScene(nullptr); // Создание пустой сцены
    }
    ui->search_textEdit->setText(""); // Очистка поля ввода для поиска
    ui->graphicsView->setScene(new_Scene); // Установка новой сцены
    if(prev_scene) delete prev_scene; // Удаление предыдущей сцены
}


void MainWindow::on_del_btn_clicked() {
    // Получение предыдущей сцены
    QGraphicsScene *prev_scene = ui->graphicsView->scene();
    // Очистка статуса и результата отображения
    clear_status();
    // Получение значения для удаления из текстового поля и преобразование в целое число
    int to_del = ui->del_textEdit->toPlainText().toInt();
    // Удаление элемента из дерева
    bool flag = T.erase(to_del);
    // Очистка текстового поля для удаления
    ui->del_textEdit->setText("");
    // Создание новой пустой сцены
    QGraphicsScene *new_Scene = CreateScene(nullptr);
    // Установка новой сцены в графическое представление
    ui->graphicsView->setScene(new_Scene);
    // Удаление предыдущей сцены, если она существует
    if(prev_scene) delete prev_scene;
}


void MainWindow::on_pushButton_clicked() {
    // Получение предыдущей сцены
    QGraphicsScene *prev_scene = ui->graphicsView->scene();
    // Очистка статуса и балансировка дерева
    clear_status();
    T.balance();
    // Создание новой пустой сцены
    QGraphicsScene *new_Scene = CreateScene(nullptr);
    // Установка новой сцены в графическое представление
    ui->graphicsView->setScene(new_Scene);
    // Удаление предыдущей сцены, если она существует
    if(prev_scene) delete prev_scene;
}

void MainWindow::on_preOrder_btn_clicked() {
    // Получаем текущую сцену из графического виджета
    QGraphicsScene *prev_scene = ui->graphicsView->scene();
    // Очищаем статус
    clear_status();
    // Создаем строку для хранения результата обхода дерева в префиксной форме
    QString RESULT;
    // Выполняем обход дерева в префиксной форме и сохраняем результат в строку RESULT
    preOrderQStringCreate(T.root, &RESULT);
    // Отображаем результат в текстовом виджете
    ui->Order_result_textBrowser->setText(RESULT);
    // Создаем новую сцену для отображения дерева
    QGraphicsScene *new_Scene = CreateScene(nullptr);
    // Устанавливаем новую сцену в графический виджет
    ui->graphicsView->setScene(new_Scene);
    // Удаляем предыдущую сцену, если она существует
    if(prev_scene) delete prev_scene;
}

void MainWindow::on_del_tree_btn_clicked() {
    // Получаем текущую сцену из графического виджета
    QGraphicsScene *prev_scene = ui->graphicsView->scene();
    // Очищаем статус
    clear_status();
    // Очищаем дерево
    T.clear();
    // Создаем новую сцену для отображения пустого дерева
    QGraphicsScene *new_Scene = CreateScene(nullptr);
    // Устанавливаем новую сцену в графический виджет
    ui->graphicsView->setScene(new_Scene);
    // Удаляем предыдущую сцену, если она существует
    if(prev_scene) delete prev_scene;
}

void MainWindow::on_simOrder_btn_clicked() {
    // Получаем текущую сцену из графического виджета
    QGraphicsScene *prev_scene = ui->graphicsView->scene();
    // Очищаем статус
    clear_status();
    // Создаем строку для хранения результата обхода дерева в инфиксной форме
    QString RESULT;
    // Выполняем обход дерева в инфиксной форме и сохраняем результат в строку RESULT
    simOrderQStringCreate(T.root, &RESULT);
    // Отображаем результат в текстовом виджете
    ui->Order_result_textBrowser->setText(RESULT);
    // Создаем новую сцену для отображения дерева
    QGraphicsScene *new_Scene = CreateScene(nullptr);
    // Устанавливаем новую сцену в графический виджет
    ui->graphicsView->setScene(new_Scene);
    // Удаляем предыдущую сцену, если она существует
    if(prev_scene) delete prev_scene;
}

void MainWindow::on_postOrder_btn_clicked() {
    // Получаем текущую сцену из графического виджета
    QGraphicsScene *prev_scene = ui->graphicsView->scene();
    // Очищаем статус
    clear_status();
    // Создаем строку для хранения результата обхода дерева в постфиксной форме
    QString RESULT;
    // Выполняем обход дерева в постфиксной форме и сохраняем результат в строку RESULT
    postOrderQStringCreate(T.root, &RESULT);
    // Отображаем результат в текстовом виджете
    ui->Order_result_textBrowser->setText(RESULT);
    // Создаем новую сцену для отображения дерева
    QGraphicsScene *new_Scene = CreateScene(nullptr);
    // Устанавливаем новую сцену в графический виджет
    ui->graphicsView->setScene(new_Scene);
    // Удаляем предыдущую сцену, если она существует
    if(prev_scene) delete prev_scene;
}
