#include "client.h"

ssize_t cs457::client::send(std::string msg)
{
    return sock->sendString(":" + username + " " + msg + "\r\n", false);
}

std::string cs457::client::command(std::string command)
{
    std::string retStr = "";
    if (command[0] == '/')
       {
           //get rid of leading slash
           command = command.substr(1, command.length() - 1);
           Parsing::IRC_message msg(command + "\r\n");

           if (msg.command == "HELP")
           {
               retStr += "A helpful message";
           }
           else if (msg.command == "QUIT")
           {
               send(command);
               sock->closeSocket();
               retStr = "QUIT";
           }
           else
           {
               send(command);
           }
       }
    else
    {
        //to be sent to active channel or whatever.
    }
    return retStr;

}
