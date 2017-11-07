#include "Message.h"
#include "UDPSocket.h"
#include <exception>
#include <thread>

#ifndef SERVER_H
#define SERVER_H


class Server
{
    private:
        UDPSocket * udpSocket;
        bool getRequest();
        void sendReply (char *_message, int client_port, char* client_hostname);        

    public:

        Server(char * _listen_hostname, int _listen_port);
        bool listen();
        ~Server();
};
#endif // SERVER_H
