#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <thread>
#include <fstream>
#include "tcpUserSocket.h"
#include "tcpClientSocket.h"
#include "Parsing.h"
#include "client.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"





MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //Read in config file. Not in main because, its not
    //parse the config file.
        //Config file will overwrite the input parameters only if given. No default
        if(client.configFile.length() > 0)
        {
            //parsing stream for the file.
            std::ifstream config(client.configFile);
            if(config.is_open())
            {
                std::string line;
                while(getline(config, line))
                {
                    //if it doesn't start with #, its not a comment.
                    if(line[0] != '#')
                    {
                        //iss of the read in line. Allows us to split on spaces.
                        std::istringstream iss(line);
                        std::string value; std::string attribute;
                        //we treat the first string as the attribute, the second as the value.
                        iss >> attribute;
                        iss >> value;

                        //then, we look to see which attribute we found and set its value to what we read from the file.
                        //disregards unrecognized attributes.
                        if(attribute == "last_server_used")
                            client.hostname = value;
                        else if(attribute == "port")
                            client.serverport = stoi(value);
                        //strings false and true must be used, cases matter.
                        else if (attribute == "default_debug_mode")
                        {
                            if(value == "false")
                            {
                                debug = false;
                                client.debug = false;
                            }
                            else{
                                debug = true;
                                client.debug = true;
                            }
                        }
                        else if (attribute == "log")
                        {
                            if(value == "false")
                            {
                                client.log = false;
                            }
                            else{
                                client.log = true;
                            }
                        }
                        else if (attribute == "default_log_file")
                        {
                            client.logFile = value;
                        }
                    }
                }
            }
            else
                std::cerr << "file could not be opened";
        }

    
}



MainWindow::~MainWindow()
{
    delete ui;
}


void clientReceive(cs457::client* client)
{
    int cont = 1;
    while (cont)
    {
        std::cout << "here2" << std::endl;
        cont = client->rcvCommand();
    }
    //std::cout << "OUT of rcv\n";

}

void MainWindow::on_connect_Button_clicked()
{
    //if the user enters custom connection info, get it.
    if(!MainWindow::ui->custom_address->text().isEmpty() && !MainWindow::ui->custom_port->text().isEmpty())
    {
        client.serverport = stoi(MainWindow::ui->custom_port->text().toStdString());
        client.hostname = MainWindow::ui->custom_address->text().toStdString();
    }
    //open up a socket with supplied info.
    cs457::tcpClientSocket clientSock(client.serverport, client.hostname);
    //client object gets a pointer to the socket, so everthing can share it.
    //threads don't complain about pointers either, which used to be a problem for me.
    client.sock = &clientSock;
    //register the user. This call is not threaded.
    //Wait to verify that user is successfully registered.
    size_t success = client.registerUser();
    //If not successful, toast message?

    //otherwise, spin up recieve thread
    //spin up recieve thread.
    std::cout << "here1" << std::endl;
    std::thread recieveThread(clientReceive, &client);
}

void MainWindow::on_send_button_clicked()
{
    //if there is text to enter, send it. Threaded call?
    if(!MainWindow::ui->command_input->text().isEmpty())
    {
        client.command(MainWindow::ui->command_input->text().toStdString());
    }
}


































