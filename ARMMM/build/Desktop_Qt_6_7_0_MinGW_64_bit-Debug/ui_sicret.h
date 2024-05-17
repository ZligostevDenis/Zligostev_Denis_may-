/********************************************************************************
** Form generated from reading UI file 'sicret.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SICRET_H
#define UI_SICRET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sicret
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;

    void setupUi(QDialog *sicret)
    {
        if (sicret->objectName().isEmpty())
            sicret->setObjectName("sicret");
        sicret->resize(400, 300);
        widget = new QWidget(sicret);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(70, 70, 231, 87));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(widget);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(widget);
        label_4->setObjectName("label_4");

        verticalLayout->addWidget(label_4);


        retranslateUi(sicret);

        QMetaObject::connectSlotsByName(sicret);
    } // setupUi

    void retranslateUi(QDialog *sicret)
    {
        sicret->setWindowTitle(QCoreApplication::translate("sicret", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("sicret", "Glebko George", nullptr));
        label_2->setText(QCoreApplication::translate("sicret", "Muravyov Dmitry", nullptr));
        label_3->setText(QCoreApplication::translate("sicret", "Lomayev David", nullptr));
        label_4->setText(QCoreApplication::translate("sicret", "Zligostev Denis", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sicret: public Ui_sicret {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SICRET_H
