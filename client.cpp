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

std::string cs457::client::command(std::string command)
{
    std::string retStr = "";

    if (command[0] == '/')
    {
        command = command.substr(1, command.length() - 1);
        Parsing::IRC_message msg(command + "\r\n");
        //quit breaks out of the command loop, as well as notifying the server politely
        //   that we are quiting.
        if (msg.command == "QUIT")
        {
            //retVal = 0;  //need some sort of continue variable in client. Threads will be contingent on.
            send(command); //sends string without slash.
        }
        else if (msg.command == "HELP")
        {
            retStr    + "************************************************************************************\n"
                       + "To see list of online users, type '/USERS'\n"
                             + "To send a message to a user, type '/PRIVMSG <user> :<your message here>'\n"
                             + "To create or join a channel, type '/JOIN <#channelName>'\n"
                             +  "To see the created channels, type '/LIST'\n"
                             +  "To send a message to a channel, type '/PRIVMSG <#channelName> :<your message here>'\n"
                             +  "A more thorough explanation can be found in the readme file.\n"
                             +  "************************************************************************************\n";
        }
        else
        {
            //let the server deal with it.
            send(command);
        }
    }
}
