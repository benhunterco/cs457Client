#include "client.h"

ssize_t cs457::client::send(std::string msg)
{
    return sock->sendString(":" + username + " " + msg + "\r\n", false);
}

ssize_t cs457::client::registerUser()
{
    //string registration = ":bobby PASS @\r\n";
    //client.sock->sendString(registration, false);
    string registration = ":" + username + " PASS " + password + "\r\n";
    return sock->sendString(registration, false);
}
