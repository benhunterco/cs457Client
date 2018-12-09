#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tcpClientSocket.h"
#include "displayworker.h"
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

    //create our displayworker object. Allows gui manipulation in secondary threads.
    displayWorker* displayer = new displayWorker;
    connect(displayer, SIGNAL(requestDisplay(QString, QString, bool)), this, SLOT(displayMessageSlot(QString, QString, bool)));
    connect(displayer, SIGNAL(requestFailure(QString)), this, SLOT(connectionFailedSlot(QString)));
    connect(displayer, SIGNAL(requestStatusUpdate(QString)), this, SLOT(updateStatusSlot(QString)));
    connect(displayer, SIGNAL(requestUsernameUpdate(QString)), this, SLOT(updateUsernameSlot(QString)));
    worker = displayer;

    //add status bar, tell if you're connected or not.
    ui->statusBar->showMessage(tr("Disconnected"));

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
    cout << "here" << endl;
    if(tab == "main"){

        string displaymsg = "server: " + msg + "\n";
        myui->plainTextEdit->insertPlainText (QString::fromStdString(displaymsg));
    }
    else{
        QWidget* tabToDisplay = channelMap[tab];
        //come back here after you find the object names.
        QPlainTextEdit* box = tabToDisplay->findChild<QPlainTextEdit*>(QString::fromStdString(tab + "_text"));
        string displaymsg = msg + "\n";
        myui->plainTextEdit->moveCursor (QTextCursor::End);
        box->insertPlainText(QString::fromStdString(displaymsg));

        //if we want to switch to this tab, do so.
        if(focus)
            myui->tabWidget->setCurrentWidget(tabToDisplay);

    }
    cout << "tohere" << endl;

}

void MainWindow::displayMessageSlot(QString Qmessage, QString Qtab, bool focus /* = false*/)
{
    std::string tab = Qtab.toStdString();
    std::string message = Qmessage.toStdString();

    if(tab == "main"){

        string displaymsg = "server: " + message + "\n";
        ui->plainTextEdit->insertPlainText (QString::fromStdString(displaymsg));
        ui->plainTextEdit->moveCursor (QTextCursor::End);
    }
    else{
        QWidget* tabToDisplay = channelMap[tab];
        //come back here after you find the object names.
        QPlainTextEdit* box = tabToDisplay->findChild<QPlainTextEdit*>(QString::fromStdString(tab + "_text"));
        string displaymsg = message + "\n";
        ui->plainTextEdit->moveCursor (QTextCursor::End);
        box->insertPlainText(QString::fromStdString(displaymsg));

        //if we want to switch to this tab, do so.
        if(focus)
            ui->tabWidget->setCurrentWidget(tabToDisplay);

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
                    //if its a channel
                    if(msg.params[0][0] == '#')
                    {
                        if(channelMap.find(msg.params[0]) == channelMap.end())
                        {
                            //add new channel for incoming message.
                            //can block messages server side.
                            worker->display(QString::fromStdString("New message from: " + msg.name + " to " + msg.params[0] + ". PRIVMSG back to create new tab.\n"), QString("main"), false);
                            worker->display(QString::fromStdString(msg.params[1]), QString("main"), false);
                            //addNewChannel(msg.params[0]);
                        }
                        else
                        {
                            //display
                            worker->display(QString::fromStdString(msg.name + ": " + msg.params[1]), QString::fromStdString(msg.params[0]), false);
                        }
                    }
                    else
                    {
                        //in this case it was sent to user
                        if(channelMap.find(msg.name) == channelMap.end())
                        {
                            //add new channel for incoming message.
                            //can block messages server side.
                            worker->display(QString::fromStdString("New message from: " + msg.name + ". PRIVMSG back to create new tab.\n"), QString("main"), false);
                            worker->display(QString::fromStdString(msg.params[1]), QString("main"), false);
                            //addNewChannel(msg.params[0]);
                        }
                        else
                        {
                            //display
                            worker->display(QString::fromStdString(msg.name + ": " + msg.params[1]), QString::fromStdString(msg.name), false);
                        }
                    }
                }
            } else if(msg.command == "QUIT")
            {
                continueReceiveing = false;
                client.connected = false;
                client.sock->closeSocket();
                //show disconnect message?
                worker->status(QString("Disconnected (quit)"));
            }
            else if(msg.command == "PING")
            {
                worker->display(QString::fromStdString("received ping"), QString("main"), false);
                client.sock->sendString(":" + client.username + " PONG", false);
            }
            else if(msg.command == "NICK")
            {
                client.username = msg.params[0];
                worker->display(QString::fromStdString(msg.params[1]), QString("main"), false);
                worker->username(QString::fromStdString(client.username));
            }
            else
            {
                worker->display(QString::fromStdString(rcvmsg), QString("main"), false);
            }
            rcvmsg.erase();
        }
        else
        {
            cout << "Read from empty socket";
            continueReceiveing = false;
            client.connected = false;
            //show some sort of message?
            //connectionFailed("Connection to remote host lost");
            worker->failure(QString("Connection to remote host lost"));
            worker->status(QString("Disconnected (connection lost)"));

        }
    }
}

void MainWindow::on_messageInput_returnPressed()
{
    on_send_clicked();
}
void MainWindow::on_send_clicked()
{
    if(client.connected)
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
                //client.sock->closeSocket();
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
            else if (msg.command == "PART")
            {
                if(channelMap.find(msg.params[0]) != channelMap.end())
                {
                    //get the channel
                    QWidget * tab = channelMap[msg.params[0]];
                    int toDelete = ui->tabWidget->indexOf(tab);
                    slotCloseTab(toDelete);
                }
                client.send(command);
            }
            else if (msg.command == "NICK")
            {
                client.username = msg.params[0];
                //update username bar.
                worker->username(QString::fromStdString(client.username));
                client.send(command);
            }
            else
            {
                client.send(command);
            }
        }
        else
        {
            //send to active window
            //first get name of active recipient
            string recipient = ui->tabWidget->currentWidget()->objectName().toStdString();
            if(recipient != "tab")
            {
                client.send("PRIVMSG " + recipient + " :" + command);
                displayMessage(client.username + ": " + command + "\n", ui, recipient, true);
            }
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
    if (val != 0)
    {
        cout << "error creating socket" << endl;
        //connectionFailed();
        worker->failure(QString("Failed to connect to remote host."));
    }
    else
    {
        //register the user
        //string = get registration?
        string registration = ":" + client.username + " PASS " + client.password + "\r\n";
        client.sock->sendString(registration, false);
        continueReceiveing = true;
        //rcvThread = make_unique<std::thread>(&MainWindow::test, ui);
        //QFuture<void> future = QtConcurrent::run(aFunction)
        //qRegisterMetaType<std::string>();
        //qRegisterMetaType<bool>();
        future = QtConcurrent::run(this, &MainWindow::receive, ui);
        client.connected = true;
        worker->status(QString("Connected"));
    }
}

void MainWindow::addNewChannel(string newChannelName)
{
    //go to "convenient" Qstring
    QString newChannelQ = QString::fromStdString(newChannelName);
    QString newTextQ = QString::fromStdString(newChannelName+"_text");
    //create the new tab object
    QWidget* newTab = new QWidget();
    //call it newchannelname
    newTab->setObjectName(newChannelQ);
    newTab->setWindowTitle(newChannelQ);

    auto newOutputPage = new QPlainTextEdit(newTab);
    newOutputPage->setObjectName(newTextQ);
    newOutputPage->setGeometry(QRect(0, 0, 701, 471));
    newOutputPage->clear();
    //cout << "Name: " + newOutputPage->objectName().toStdString() << endl;
    ui->tabWidget->addTab(newTab, newChannelQ);

    //uncomment to make closable. However this causes segfaults, whereas part does not.
    //SO just use part.
    //ui->tabWidget->setTabsClosable(true);
    //connect(ui->tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(slotCloseTab(int)));//ty stack overflow. Makes tabs closable
    //Add tab to map
    channelMap[newChannelName] = newTab;

}

/*
void MainWindow::on_pushButton_clicked()
{
    addNewChannel("#Channel");
}*/

//TODO:
/*https://stackoverflow.com/questions/35597431/closable-qtabwidget-tabs-but-not-all-of-them*/
void MainWindow::slotCloseTab(int index)
{
    if(index > 0)
    {
        //remove from channel map too
        std::string channelToClose = ui->tabWidget->widget(index)->objectName().toStdString();
        channelMap.erase(channelToClose);
        //delete ui element.
        delete ui->tabWidget->widget(index);
    }
}


void MainWindow::on_password_returnPressed()
{
    //treat this as clicking the button to the right of it.
    on_credentials_clicked();
}
void MainWindow::on_credentials_clicked()
{
    if(!ui->username->text().isEmpty())
    {
        cout << "set credentials" << endl;
        client.username = ui->username->text().toStdString();
        if(!ui->password->text().isEmpty())
            client.password = ui->password->text().toStdString();
        //otherwise it remains as @
    }
}

void MainWindow::connectionFailed(std::string msg)
{
    QMessageBox msgBox(ui->centralWidget);
    msgBox.setText(QString::fromStdString(msg));
    msgBox.exec();

}

void MainWindow::connectionFailedSlot(QString Qmsg)
{
    QMessageBox msgBox(ui->centralWidget);
    msgBox.setText(Qmsg);
    msgBox.exec();
}

void MainWindow::updateStatusSlot(QString status)
{
    ui->statusBar->showMessage(status);
}

void MainWindow::updateUsernameSlot(QString username)
{
    ui->username->setText(username);
}
































