#include "mainwindow.h" // Подключение заголовочного файла главного окна

#include <QApplication> // Подключение класса QApplication для создания приложения

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // Создание объекта приложения
    MainWindow w; // Создание объекта главного окна
    w.show(); // Отображение главного окна
    return a.exec(); // Запуск цикла обработки событий приложения
}
