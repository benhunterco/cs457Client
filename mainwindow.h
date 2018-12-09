#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tcpClientSocket.h"
#include "QtConcurrent/qtconcurrentrun.h"
#include "client.h"
#include "Parsing.h"
#include <iostream>
#include <string>
#include <thread>
#include <map>
#include <QMessageBox>

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
    void on_send_clicked();

    void on_connect_clicked();

    //void on_pushButton_clicked();

    void slotCloseTab(int);

    void on_messageInput_returnPressed();

    void on_credentials_clicked();

    void on_password_returnPressed();

private:
    Ui::MainWindow *ui;
    cs457::tcpClientSocket clientSocket;
    void displayMessage(string message, Ui::MainWindow *myui, string tab = "main", bool focus = false);
    unique_ptr<std::thread> rcvThread;
    QFuture<void> future;
    void receive(Ui::MainWindow *myui);
    bool continueReceiveing;
    void addNewChannel(string channelName);
    cs457::client client;
    map<string, QWidget*> channelMap;
    bool debug = false;

    void connectionFailed(std::string msg = "Connection failed");

};

#endif // MAINWINDOW_H
