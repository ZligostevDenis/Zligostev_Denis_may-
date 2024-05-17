#ifndef MAINWINDOW_H  // Заголовочный охранник: предотвращает повторное включение файла
#define MAINWINDOW_H

#include <QMainWindow>  // Базовый класс для главного окна
#include <QGraphicsScene> // Для создания графической сцены
#include <vector>       // Стандартный контейнер (может использоваться для данных)
#include "BinaryTree.h"  // Заголовочный файл для класса бинарного дерева

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; } // Пространство имен для классов UI от Qt Designer
QT_END_NAMESPACE

class MainWindow : public QMainWindow // Класс главного окна, наследуется от QMainWindow
{
    Q_OBJECT // Макрос для использования механизма метаобъектов Qt (сигналы/слоты)

public:
    MainWindow(QWidget *parent = nullptr); // Конструктор с необязательным родительским виджетом
    ~MainWindow();                      // Деструктор

private slots: // Слоты - функции, реагирующие на события (нажатия кнопок и т.д.)
    void on_insert_btn_clicked();     // Обработчик нажатия кнопки "Вставить"
    void on_search_btn_clicked();     // Обработчик нажатия кнопки "Найти элемент"
    void on_del_btn_clicked();        // Обработчик нажатия кнопки "Удалить"
    void on_pushButton_clicked();     // Обработчик нажатия кнопки "Балансировка"
    void on_preOrder_btn_clicked();    // Обработчик нажатия кнопки "Прямой обход"
    void on_del_tree_btn_clicked();   // Обработчик нажатия кнопки "Удалить дерево"
    void on_simOrder_btn_clicked();    // Обработчик нажатия кнопки "Симметричный обход"
    void on_postOrder_btn_clicked();   // Обработчик нажатия кнопки "Обратный обход"

private:
    Ui::MainWindow *ui;        // Указатель на элементы UI, созданные Qt Designer
    BinaryTree T;             // Объект бинарного дерева
    QGraphicsScene* CreateScene(Tree*); // Функция создания графической сцены дерева
    void clear_status();     // Функция очистки полей статуса в UI
};

#endif // MAINWINDOW_H  // Закрывающий заголовочный охранник
