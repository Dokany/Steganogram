#include "UDPSocket.h"

#ifndef CLIENT_H
#define CLIENT_H
class Client
{
private:
    UDPSocket *udpSocket;
    
public:
    Client();
    char * execute(char * _message, int server_port, char *hostname, char *server_host);
    ~Client();
};
#endif // CLIENT_H
