#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tcpClientSocket.h"
#include "QtConcurrent/qtconcurrentrun.h"
#include "client.h"
#include "Parsing.h"
#include "displayworker.h"
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
    explicit MainWindow(QWidget *parent = nullptr);
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

    void displayMessageSlot(QString message, QString tab, bool focus = false);


    void connectionFailedSlot(QString Qmsg);

    void updateStatusSlot(QString status);

    void updateUsernameSlot(QString username);

    void closeTabByNameSlot(QString tabName);

private:
    Ui::MainWindow *ui;
    cs457::tcpClientSocket clientSocket;
    void displayMessage(string message, Ui::MainWindow *myui, string tab = "main", bool focus = false);
    unique_ptr<std::thread> rcvThread;
    QFuture<void> future;
    void receive();
    bool continueReceiveing;
    void addNewChannel(string channelName);
    cs457::client client;
    map<string, QWidget*> channelMap;
    bool debug = false;

    void connectionFailed(std::string msg = "Connection failed");

    displayWorker* worker;

};

#endif // MAINWINDOW_H
