/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QPlainTextEdit *plainTextEdit;
    QWidget *tab_2;
    QPlainTextEdit *plainTextEdit_2;
    QWidget *tab_3;
    QPlainTextEdit *plainTextEdit_3;
    QWidget *tab_4;
    QPlainTextEdit *plainTextEdit_4;
    QWidget *tab_5;
    QPlainTextEdit *plainTextEdit_5;
    QWidget *tab_6;
    QPlainTextEdit *plainTextEdit_6;
    QPushButton *connect_Button;
    QLineEdit *custom_address;
    QLineEdit *command_input;
    QPushButton *send_button;
    QLineEdit *custom_port;
    QMenuBar *menuBar;
    QMenu *menuChat_App;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(420, 343);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 30, 411, 211));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(verticalLayoutWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        plainTextEdit = new QPlainTextEdit(tab);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(0, 0, 401, 171));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        plainTextEdit_2 = new QPlainTextEdit(tab_2);
        plainTextEdit_2->setObjectName(QStringLiteral("plainTextEdit_2"));
        plainTextEdit_2->setGeometry(QRect(0, 0, 411, 181));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        plainTextEdit_3 = new QPlainTextEdit(tab_3);
        plainTextEdit_3->setObjectName(QStringLiteral("plainTextEdit_3"));
        plainTextEdit_3->setGeometry(QRect(0, 0, 411, 181));
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        plainTextEdit_4 = new QPlainTextEdit(tab_4);
        plainTextEdit_4->setObjectName(QStringLiteral("plainTextEdit_4"));
        plainTextEdit_4->setGeometry(QRect(0, 0, 411, 181));
        tabWidget->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        plainTextEdit_5 = new QPlainTextEdit(tab_5);
        plainTextEdit_5->setObjectName(QStringLiteral("plainTextEdit_5"));
        plainTextEdit_5->setGeometry(QRect(0, 0, 411, 181));
        tabWidget->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QStringLiteral("tab_6"));
        plainTextEdit_6 = new QPlainTextEdit(tab_6);
        plainTextEdit_6->setObjectName(QStringLiteral("plainTextEdit_6"));
        plainTextEdit_6->setGeometry(QRect(0, 0, 401, 181));
        tabWidget->addTab(tab_6, QString());

        verticalLayout->addWidget(tabWidget);

        connect_Button = new QPushButton(centralWidget);
        connect_Button->setObjectName(QStringLiteral("connect_Button"));
        connect_Button->setGeometry(QRect(320, 0, 89, 25));
        custom_address = new QLineEdit(centralWidget);
        custom_address->setObjectName(QStringLiteral("custom_address"));
        custom_address->setGeometry(QRect(0, 0, 121, 25));
        custom_address->setAutoFillBackground(false);
        command_input = new QLineEdit(centralWidget);
        command_input->setObjectName(QStringLiteral("command_input"));
        command_input->setGeometry(QRect(0, 250, 311, 25));
        send_button = new QPushButton(centralWidget);
        send_button->setObjectName(QStringLiteral("send_button"));
        send_button->setGeometry(QRect(320, 250, 89, 25));
        custom_port = new QLineEdit(centralWidget);
        custom_port->setObjectName(QStringLiteral("custom_port"));
        custom_port->setGeometry(QRect(130, 0, 113, 21));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 420, 22));
        menuChat_App = new QMenu(menuBar);
        menuChat_App->setObjectName(QStringLiteral("menuChat_App"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuChat_App->menuAction());

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Tab 1", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Tab 2", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "Page", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MainWindow", "Page", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("MainWindow", "Page", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QApplication::translate("MainWindow", "Page", Q_NULLPTR));
        connect_Button->setText(QApplication::translate("MainWindow", "Connect", Q_NULLPTR));
        custom_address->setText(QString());
        custom_address->setPlaceholderText(QApplication::translate("MainWindow", "Address:127.0.0.1", Q_NULLPTR));
        command_input->setText(QString());
        command_input->setPlaceholderText(QApplication::translate("MainWindow", "message or command", Q_NULLPTR));
        send_button->setText(QApplication::translate("MainWindow", "Send", Q_NULLPTR));
        custom_port->setText(QString());
        custom_port->setPlaceholderText(QApplication::translate("MainWindow", "Port:2000", Q_NULLPTR));
        menuChat_App->setTitle(QApplication::translate("MainWindow", "Chat App", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
