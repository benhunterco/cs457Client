#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tcpClientSocket.h"
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
    clientSocket.setAddress(serverIP);
    clientSocket.setPort(port);
    ui->plainTextEdit_2->moveCursor (QTextCursor::End);


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

void MainWindow::displayMessage(string msg)
{
    ui->plainTextEdit_2->moveCursor (QTextCursor::End);
    string displaymsg = "server: " + msg + "\n";
    ui->plainTextEdit_2->insertPlainText (QString::fromStdString(displaymsg));

}

void MainWindow::test()
{
    while(continueReceiveing){
        cout << "Attempting to recv from socket." << endl;
        string rcvmsg;
        ssize_t v;
        tie(rcvmsg,v) =  clientSocket.recvString(4096,false);
        if(v > 0)
             displayMessage(rcvmsg);
        else
            cout << "Read from empty socket";

    }
}

void MainWindow::on_pushButton_2_clicked()
{
    string sendmsg = ui->lineEdit_2->text().toStdString();
    ui->plainTextEdit_2->moveCursor (QTextCursor::End);
    string displaymsg = "user: " + sendmsg + "\n";
    ui->plainTextEdit_2->insertPlainText (QString::fromStdString(displaymsg));
    clientSocket.sendString(sendmsg + "\r\n",false);
    //receive();
}

void MainWindow::on_connect_clicked()
{
    if(!ui->custom_address->text().isEmpty() && !ui->custom_port->text().isEmpty())
    {
        clientSocket.setAddress(ui->custom_address->text().toStdString());
        clientSocket.setPort(stoul(ui->custom_port->text().toStdString()));
    }
    clientSocket.init();
    clientSocket.setSocketOptions();
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
        clientSocket.sendString(registration, false);
    }

    continueReceiveing = true;
    rcvThread = make_unique<std::thread>(&MainWindow::test, this);
}
