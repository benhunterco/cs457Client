#include "client.h"

ssize_t cs457::client::send(std::string msg)
{
    return sock->sendString(":" + username + " " + msg + "\r\n", false);
}

ssize_t cs457::client::registerUser()
{
    std::string registration = "PASS " + password;
    return send(registration);
}
