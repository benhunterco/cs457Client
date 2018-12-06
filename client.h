#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <iostream>
#include <tcpClientSocket.h>
#include "Parsing.h"

namespace cs457
{
class client
{
public:
    //hostname to connect to
    std::string hostname = "127.0.0.1";
    //username sent in messages. Overwritten by -u
    std::string username = "bobby";
    //Password sent in registration
    //even if it is not yet set, we still send @.
    //this means all users are registered by default.
    std::string password = "@";
    //port on which to open up the socket.
    uint serverport = 2000;
    //if set in command line arguments, overwrites all other relevant params.
    std::string configFile;
    //the following are not yet used.
    std::string testFile = "";
    std::string logFile = "";

    //new and experimental
    tcpClientSocket* sock;
    ssize_t send(std::string msg);
    ssize_t registerUser();

    //interprets the entered command by the
    string command(std::string msg);

    bool connected = false;
private:
    //you actually need to do more than just this.
    bool sendDirect = false;
};
}

#endif // CLIENT_H
