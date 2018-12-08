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
    clientSocket.setAddress(client.hostname);
    clientSocket.setPort(client.serverport);
    client.sock = &clientSocket;
    ui->plainTextEdit->moveCursor (QTextCursor::End);

    //delete second tab. Couldn't remove it in the form...
    ui->tabWidget->removeTab(1);

}

MainWindow::~MainWindow()
{
    continueReceiveing = false;
    client.command("/QUIT");
    if(future.isStarted())
    {
        future.waitForFinished();
    }
    delete ui;
}

void MainWindow::displayMessage(string msg, Ui::MainWindow *myui, string tab /*= "main*/, bool focus /*=false*/)
{
    if(tab == "main"){

        string displaymsg = "server: " + msg + "\n";
        myui->plainTextEdit->insertPlainText (QString::fromStdString(displaymsg));
    }
    else{
        QWidget* tabToDisplay = channelMap[tab];
        //come back here after you find the object names.
        QPlainTextEdit* box = tabToDisplay->findChild<QPlainTextEdit*>(QString::fromStdString(tab + "_text"));
        string displaymsg = msg + "\n";
        ui->plainTextEdit->moveCursor (QTextCursor::End);
        box->insertPlainText(QString::fromStdString(displaymsg));

        //if we want to switch to this tab, do so.
        if(focus)
            myui->tabWidget->setCurrentWidget(tabToDisplay);

    }

}

void MainWindow::receive(Ui::MainWindow *myui)
{
    while(continueReceiveing){
        cout << "Attempting to recv from socket." << endl;
        string rcvmsg;
        ssize_t v;
        tie(rcvmsg,v) =  clientSocket.recvString(4096,false);
        if(v > 0)
        {
            Parsing::IRC_message msg(rcvmsg);
            if(msg.command == "PRIVMSG")
            {
                if(msg.name != client.username)
                {
                    if(channelMap.find(msg.params[0]) == channelMap.end())
                    {
                        //add new channel for incoming message.
                        //can block messages server side.
                        displayMessage("New message from: " + msg.name + " to " + msg.params[0] + ". PRIVMSG back to create new tab.\n", myui);
                        displayMessage(msg.params[1], myui);
                        //addNewChannel(msg.params[0]);
                    }
                    else
                    {
                        //display
                        displayMessage(msg.name + ": " + msg.params[1], myui, msg.params[0], false);
                    }
                }
            }
            else
            {
                displayMessage(rcvmsg, myui);
            }
            rcvmsg.erase();
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
    //change the qstring to string
    string command = ui->messageInput->text().toStdString();
    ui->plainTextEdit->moveCursor (QTextCursor::End);

    //show it, for testing. later show your message when you privmsg
    if(debug)
    {
        string displaymsg = "user: " + command + "\n";
        ui->plainTextEdit->insertPlainText (QString::fromStdString(displaymsg));
    }
    //clientSocket.sendString(sendmsg + "\r\n",false);

    //now do what command used to do.
    if(command[0] == '/')
    {
        command = command.substr(1, command.length() - 1);
        Parsing::IRC_message msg(command + "\r\n");
        if (msg.command == "HELP")
        {
            displayMessage("A helpful message", ui);
        }
        else if (msg.command == "QUIT")
        {
            client.send(command);
            continueReceiveing = false;
            client.sock->closeSocket();
        }
        else if (msg.command == "PRIVMSG")
        {
            //send out what you said. lets deal with dmfisrt

            if(channelMap.find(msg.params[0]) == channelMap.end())
            {
                addNewChannel(msg.params[0]);
            }
            displayMessage(client.username + ": " + msg.params[1] + "\n", ui, msg.params[0], true);
            client.send(command);

        }
        else if (msg.command == "JOIN")
        {
            if(channelMap.find(msg.params[0]) == channelMap.end())
            {
                addNewChannel(msg.params[0]);
            }
            client.send(command);
        }
        else
        {
            client.send(command);
        }
    }

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
    future = QtConcurrent::run(this, &MainWindow::receive, ui);

}

void MainWindow::addNewChannel(string newChannelName)
{
    //go to "convenient" Qstring
    QString newChannelQ = QString::fromStdString(newChannelName);
    QString newTextQ = QString::fromStdString(newChannelName+"_text");
    //create the new tab object
    QWidget* newTab = new QWidget(ui->verticalLayoutWidget);
    //call it newchannelname
    newTab->setObjectName(newChannelQ);
    newTab->setWindowTitle(newChannelQ);
    auto newOutputPage = new QPlainTextEdit(newTab);
    newOutputPage->setObjectName(newTextQ);
    newOutputPage->setGeometry(QRect(0, 0, 531, 231));
    //cout << "Name: " + newOutputPage->objectName().toStdString() << endl;
    ui->tabWidget->addTab(newTab, newChannelQ);
    ui->tabWidget->setTabsClosable(true);

    //Add tab to map
    channelMap[newChannelName] = newTab;

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





























