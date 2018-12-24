/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLabel *label_device;
    QPushButton *btn_refresh;
    QPushButton *btn_led_random;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 300);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 20, 47, 13));
        label_device = new QLabel(centralWidget);
        label_device->setObjectName(QStringLiteral("label_device"));
        label_device->setGeometry(QRect(70, 10, 221, 31));
        btn_refresh = new QPushButton(centralWidget);
        btn_refresh->setObjectName(QStringLiteral("btn_refresh"));
        btn_refresh->setGeometry(QRect(310, 10, 75, 31));
        btn_led_random = new QPushButton(centralWidget);
        btn_led_random->setObjectName(QStringLiteral("btn_led_random"));
        btn_led_random->setGeometry(QRect(150, 130, 91, 23));
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QApplication::translate("MainWindow", "Device :", nullptr));
        label_device->setText(QApplication::translate("MainWindow", "None", nullptr));
        btn_refresh->setText(QApplication::translate("MainWindow", "Refresh", nullptr));
#ifndef QT_NO_ACCESSIBILITY
        btn_led_random->setAccessibleName(QApplication::translate("MainWindow", "Random", nullptr));
#endif // QT_NO_ACCESSIBILITY
        btn_led_random->setText(QApplication::translate("MainWindow", "Random", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
