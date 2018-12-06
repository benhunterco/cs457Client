#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tcpClientSocket.h"
#include "QtConcurrent/qtconcurrentrun.h"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>


using namespace std;

MainWindow::MainWindow(QWidget *parent, string serverIP, uint port) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    clientSocket.setAddress(client.hostname);
    clientSocket.setPort(client.serverport);
    client.sock = &clientSocket;
    ui->plainTextEdit->moveCursor (QTextCursor::End);

    //delete second tab. Couldn't remove it in the form...
    ui->tabWidget->removeTab(1);

}

MainWindow::~MainWindow()
{
    string msgExit("EXIT");
    clientSocket.sendString(msgExit,false);
    clientSocket.closeSocket();
    continueReceiveing = false;
    if(rcvThread && rcvThread->joinable())
    {
        rcvThread->join();
    }
    delete ui;
}

void MainWindow::displayMessage(string msg, Ui::MainWindow *myui)
{
    //ui->plainTextEdit->moveCursor (QTextCursor::End);
    string displaymsg = "server: " + msg + "\n";
    myui->plainTextEdit->insertPlainText (QString::fromStdString(displaymsg));

}

void MainWindow::test(Ui::MainWindow *myui)
{
    while(continueReceiveing){
        cout << "Attempting to recv from socket." << endl;
        string rcvmsg;
        ssize_t v;
        tie(rcvmsg,v) =  clientSocket.recvString(4096,false);
        if(v > 0)
        {
             displayMessage(rcvmsg, myui);
        }
        else
        {
            cout << "Read from empty socket";
            continueReceiveing = false;
        }
    }
}

void MainWindow::on_send_clicked()
{
    string sendmsg = ui->messageInput->text().toStdString();
    ui->plainTextEdit->moveCursor (QTextCursor::End);
    string displaymsg = "user: " + sendmsg + "\n";
    ui->plainTextEdit->insertPlainText (QString::fromStdString(displaymsg));
    //clientSocket.sendString(sendmsg + "\r\n",false);
    string sendInfo = client.command(sendmsg);
    //for now, just display it. Could use it for status?
    ui->plainTextEdit->insertPlainText (QString::fromStdString(sendInfo));
    //receive();
}

void MainWindow::on_connect_clicked()
{
    if(!ui->custom_address->text().isEmpty() && !ui->custom_port->text().isEmpty())
    {
        client.hostname = ui->custom_address->text().toStdString();
        client.serverport = stoul(ui->custom_port->text().toStdString());
        client.sock->setAddress(client.hostname);
        client.sock->setPort(client.serverport);
    }
    client.sock->init();
    client.sock->setSocketOptions();
    int val = clientSocket.connectSocket();
    if (val > 0)
    {
        cout << "error creating socket" << endl;
    }
    else
    {
        //register the user
        //string = get registration?
        string registration = ":bobby PASS @\r\n";
        client.sock->sendString(registration, false);
    }

    continueReceiveing = true;
    //rcvThread = make_unique<std::thread>(&MainWindow::test, ui);
    //QFuture<void> future = QtConcurrent::run(aFunction)
    QFuture<void> future = QtConcurrent::run(this, &MainWindow::test, ui);

}

void MainWindow::addNewChannel(string newChannelName)
{
    //go to "convenient" Qstring
    QString newChannelQ = QString::fromStdString(newChannelName);
    //create the new tab object
    QWidget* newTab = new QWidget(ui->verticalLayoutWidget);
    //call it newchannelname
    newTab->setObjectName(newChannelQ);
    newTab->setWindowTitle(newChannelQ);
    auto newOutputPage = new QPlainTextEdit(newTab);
    newOutputPage->setGeometry(QRect(0, 0, 531, 231));
    ui->tabWidget->addTab(newTab, newChannelQ);
    ui->tabWidget->setTabsClosable(true);

}

void MainWindow::on_pushButton_clicked()
{
    addNewChannel("#Channel");
}

//TODO:
/*https://stackoverflow.com/questions/35597431/closable-qtabwidget-tabs-but-not-all-of-them
void MainWindow::slotCloseTab(int index)
{
    delete _pTabWidget->widget(index);
}*/





























