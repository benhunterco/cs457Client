#include <netinet/in.h> 
#include <arpa/inet.h>
#include "tcpClientSocket.h"
#include <string> 
#include <cstring> 
#include <vector> 

using namespace std; 
    

cs457::tcpClientSocket::tcpClientSocket(string networkAddress, uint portNumber): address(networkAddress), port(portNumber)
{
    init(); 
    setSocketOptions();
};


cs457::tcpClientSocket::tcpClientSocket(){

}



void cs457::tcpClientSocket::init()
{
    //here I may have differences with server 
    //check after testing
    clientSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    const char * cstr = address.c_str();
    int val =0;  
    bzero(&serverAddress,sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    val = inet_aton(cstr,&addr);
    serverAddress.sin_addr = addr;
    //string addresscpy(inet_ntoa(addr));
    //address = addresscpy;  
    serverAddress.sin_port = htons(port);
}

void cs457::tcpClientSocket::setSocketOptions()
{
    int optval = 1;
    setsockopt(clientSocket, SOL_SOCKET, SO_REUSEADDR, 
	                (const void *)&optval , sizeof(int));
}

int cs457::tcpClientSocket::connectSocket()
{
    return connect(clientSocket,(struct sockaddr *)&serverAddress,sizeof(serverAddress));


}

int cs457::tcpClientSocket::closeSocket()
{
    return close(clientSocket);
}

std::tuple<string,ssize_t> cs457::tcpClientSocket::recvString(int bufferSize, bool useMutex)
{
    char stringBuffer[bufferSize]; 
    //fixed by Ben
    memset(stringBuffer, 0, sizeof(stringBuffer));    //change made here. Zeros out buffer.

    ssize_t recvMsgSize;

    if (useMutex)
    {
        lock_guard<mutex> lock(recvMutex);
        recvMsgSize = recv(clientSocket, stringBuffer, bufferSize, 0); 
    }    
    else
    {
        recvMsgSize = recv(clientSocket, stringBuffer, bufferSize, 0); 
    }
    
    
   
    return make_tuple(string(stringBuffer),recvMsgSize);     
};
        

ssize_t cs457::tcpClientSocket::sendString(const string & data, bool useMutex)
{
    //https://stackoverflow.com/questions/7352099/stdstring-to-char
    if (data.size() == 0) return 0;                 
    int bufferSize = data.size()+1; 
    vector<char> stringBuffer(data.c_str(), data.c_str() + data.size() + 1u);

    ssize_t rval; 
    if (useMutex)
    {
       lock_guard<mutex> lock(sendMutex);
       rval = send(clientSocket, &stringBuffer[0], bufferSize, 0);
    }
    else
    {
       rval = send(clientSocket, &stringBuffer[0], bufferSize, 0);     
    }

    return rval;
}


void cs457::tcpClientSocket::setAddress(string addr)
{
    address = addr;
}


void cs457::tcpClientSocket::setPort(uint prt)
{
    port = prt;
}
