#ifndef MAINWINDOW_H // Проверка, не был ли этот файл уже подключен
#define MAINWINDOW_H

#include <QMainWindow> // Подключаем класс QMainWindow для создания главного окна
#include <QMessageBox> // Подключаем класс QMessageBox для вывода сообщений

#include "paintscene.h" // Подключаем заголовочный файл класса PaintScene
#include "point.h" // Подключаем заголовочный файл класса Point
#include "pointsandmatrix.h" // Подключаем заголовочный файл класса PointsAndMatrix

// Определение пространства имен Ui
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// Класс MainWindow, наследуемый от QMainWindow
class MainWindow : public QMainWindow
{
    Q_OBJECT // Макрос для использования сигналов и слотов

public:
    MainWindow(QWidget *parent = nullptr); // Конструктор класса
    ~MainWindow(); // Деструктор класса

private:
    Ui::MainWindow *ui; // Указатель на объект интерфейса

    PaintScene* scene = nullptr; // Указатель на объект сцены для рисования
    PointsAndMatrix* Matrix = nullptr; // Указатель на объект для работы с точками и матрицей

    // Приватные методы для обновления выпадающих списков
    void updateComboBox_3(int indexOfComboBox_2);
    void updateComboBox_5(int indexOfComboBox_4);

private slots:
    // Слот для получения указателя на объект PointsAndMatrix
    void sendPtrMatrix(PointsAndMatrix*& out_ptrMatrix);

    // Слот для получения размера матрицы
    void slotGetMatrixSize(int size);

    // Слоты для обработки сигналов от элементов интерфейса
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_comboBox_2_currentIndexChanged(int index);
    void on_comboBox_3_currentIndexChanged(const QString &arg1);
    void on_lineEdit_textChanged(const QString &arg1);
    void on_checkBox_stateChanged(int arg1);
    void on_comboBox_currentIndexChanged(int index);
    void on_pushButton_3_clicked();
    void on_comboBox_4_currentIndexChanged(int index);
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
};

#endif // MAINWINDOW_H // Завершение блока условного включения
