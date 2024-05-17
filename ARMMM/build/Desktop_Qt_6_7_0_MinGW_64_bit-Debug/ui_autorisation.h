/********************************************************************************
** Form generated from reading UI file 'autorisation.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTORISATION_H
#define UI_AUTORISATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Autorisation
{
public:
    QGroupBox *groupBox;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *login;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *password;
    QPushButton *pushButton;

    void setupUi(QDialog *Autorisation)
    {
        if (Autorisation->objectName().isEmpty())
            Autorisation->setObjectName("Autorisation");
        Autorisation->resize(400, 451);
        groupBox = new QGroupBox(Autorisation);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(30, 60, 311, 271));
        widget = new QWidget(groupBox);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(40, 60, 243, 201));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(widget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        login = new QLineEdit(widget);
        login->setObjectName("login");

        horizontalLayout->addWidget(login);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        password = new QLineEdit(widget);
        password->setObjectName("password");

        horizontalLayout_2->addWidget(password);


        verticalLayout_2->addLayout(horizontalLayout_2);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName("pushButton");

        verticalLayout_2->addWidget(pushButton);


        retranslateUi(Autorisation);

        QMetaObject::connectSlotsByName(Autorisation);
    } // setupUi

    void retranslateUi(QDialog *Autorisation)
    {
        Autorisation->setWindowTitle(QCoreApplication::translate("Autorisation", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Autorisation", "\320\220\320\262\321\202\320\276\321\200\320\270\320\267\320\260\321\206\320\270\321\217", nullptr));
        label->setText(QCoreApplication::translate("Autorisation", "login", nullptr));
        label_2->setText(QCoreApplication::translate("Autorisation", "password", nullptr));
        pushButton->setText(QCoreApplication::translate("Autorisation", "\320\262\320\276\320\271\321\202\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Autorisation: public Ui_Autorisation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTORISATION_H
