#include "Message.h"
#include "UDPSocket.h"
#include <thread>
#include <vector>
#include <queue>

#ifndef PEER_H
#define PEER_H

class Peer
{
    private:
        UDPSocket * udpSocket_client;
        UDPSocket * udpSocket_server;
        
        std::vector<std::thread> processes;
        std::queue<char*> requests;

        bool getRequest();
        void sendReply (char *_message, int client_port, char* client_hostname);        

    public:
        Peer(char * _listen_hostname, int _listen_port);
        char * execute(char * _message, int server_port, char *hostname, char *server_host);
        bool listen();
        ~Peer();
};
#endif // PEER_H
