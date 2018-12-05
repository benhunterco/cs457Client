#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tcpClientSocket.h"
#include <iostream>
#include <string>
#include <thread>

using namespace std;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr, string networkAddress = "127.0.0.1", uint portNumber = 2000);
    ~MainWindow();
//    cs457::tcpClientSocket clientSocket;

private slots:
    void on_pushButton_2_clicked();

    void on_connect_clicked();

private:
    Ui::MainWindow *ui;
    cs457::tcpClientSocket clientSocket;
    void displayMessage(string message);
    unique_ptr<std::thread> rcvThread;
    void test();
    bool continueReceiveing;

};

#endif // MAINWINDOW_H
