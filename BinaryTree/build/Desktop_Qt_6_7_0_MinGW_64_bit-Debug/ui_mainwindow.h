/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGraphicsView *graphicsView;
    QLabel *search_status_label;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QPushButton *insert_btn;
    QPushButton *del_btn;
    QPushButton *search_btn;
    QTextEdit *inser_textEdit;
    QTextEdit *del_textEdit;
    QTextEdit *search_textEdit;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QPushButton *del_tree_btn;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout;
    QPushButton *preOrder_btn;
    QPushButton *postOrder_btn;
    QPushButton *simOrder_btn;
    QTextBrowser *Order_result_textBrowser;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1150, 531);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setGeometry(QRect(480, 0, 661, 451));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy1);
        QPalette palette;
        QBrush brush(QColor(255, 255, 127, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush1(QColor(255, 251, 133, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        graphicsView->setPalette(palette);
        search_status_label = new QLabel(centralwidget);
        search_status_label->setObjectName("search_status_label");
        search_status_label->setGeometry(QRect(310, 20, 149, 16));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 50, 441, 121));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        insert_btn = new QPushButton(layoutWidget);
        insert_btn->setObjectName("insert_btn");
        sizePolicy.setHeightForWidth(insert_btn->sizePolicy().hasHeightForWidth());
        insert_btn->setSizePolicy(sizePolicy);

        gridLayout->addWidget(insert_btn, 0, 0, 1, 1);

        del_btn = new QPushButton(layoutWidget);
        del_btn->setObjectName("del_btn");
        QPalette palette1;
        QBrush brush2(QColor(255, 0, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush2);
        QBrush brush3(QColor(255, 255, 255, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush3);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush3);
        del_btn->setPalette(palette1);

        gridLayout->addWidget(del_btn, 0, 1, 1, 1);

        search_btn = new QPushButton(layoutWidget);
        search_btn->setObjectName("search_btn");

        gridLayout->addWidget(search_btn, 0, 2, 1, 1);

        inser_textEdit = new QTextEdit(layoutWidget);
        inser_textEdit->setObjectName("inser_textEdit");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(inser_textEdit->sizePolicy().hasHeightForWidth());
        inser_textEdit->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(inser_textEdit, 1, 0, 1, 1);

        del_textEdit = new QTextEdit(layoutWidget);
        del_textEdit->setObjectName("del_textEdit");

        gridLayout->addWidget(del_textEdit, 1, 1, 1, 1);

        search_textEdit = new QTextEdit(layoutWidget);
        search_textEdit->setObjectName("search_textEdit");

        gridLayout->addWidget(search_textEdit, 1, 2, 1, 1);

        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(10, 280, 171, 67));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(layoutWidget1);
        pushButton->setObjectName("pushButton");

        verticalLayout->addWidget(pushButton);

        del_tree_btn = new QPushButton(layoutWidget1);
        del_tree_btn->setObjectName("del_tree_btn");

        verticalLayout->addWidget(del_tree_btn);

        layoutWidget2 = new QWidget(centralwidget);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(10, 170, 439, 41));
        horizontalLayout = new QHBoxLayout(layoutWidget2);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        preOrder_btn = new QPushButton(layoutWidget2);
        preOrder_btn->setObjectName("preOrder_btn");

        horizontalLayout->addWidget(preOrder_btn);

        postOrder_btn = new QPushButton(layoutWidget2);
        postOrder_btn->setObjectName("postOrder_btn");

        horizontalLayout->addWidget(postOrder_btn);

        simOrder_btn = new QPushButton(layoutWidget2);
        simOrder_btn->setObjectName("simOrder_btn");

        horizontalLayout->addWidget(simOrder_btn);

        Order_result_textBrowser = new QTextBrowser(centralwidget);
        Order_result_textBrowser->setObjectName("Order_result_textBrowser");
        Order_result_textBrowser->setGeometry(QRect(12, 210, 441, 41));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1150, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        search_status_label->setText(QString());
        insert_btn->setText(QCoreApplication::translate("MainWindow", "\320\222\321\201\321\202\320\260\320\262\320\270\321\202\321\214 \321\203\320\267\320\265\320\273", nullptr));
        del_btn->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \321\203\320\267\320\265\320\273", nullptr));
        search_btn->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\271\321\202\320\270 \321\215\320\273\320\265\320\274\320\265\320\275\321\202", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\320\221\320\260\320\273\320\260\320\275\321\201\320\270\321\200\320\276\320\262\320\272\320\260 \320\264\320\265\321\200\320\265\320\262\320\260", nullptr));
        del_tree_btn->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\264\320\265\321\200\320\265\320\262\320\276", nullptr));
        preOrder_btn->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\321\217\320\274\320\276\320\271 \320\276\320\261\321\205\320\276\320\264", nullptr));
        postOrder_btn->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261\321\200\320\260\321\202\320\275\321\213\320\271", nullptr));
        simOrder_btn->setText(QCoreApplication::translate("MainWindow", "\320\241\320\270\320\274\320\274\320\265\321\202\321\200\320\270\321\207\320\275\321\213\320\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
