#include "Message.h"
#include "UDPSocket.h"
#include <exception>
#include <thread>
#include <mutex>
#include <vector>
#include <queue>
#include <condition_variable>

#ifndef SERVER_H
#define SERVER_H


class Server
{
    private:
        UDPSocket * udpSocket;

		std::mutex mutex_;
        std::condition_variable cond;

        std::vector<std::thread> processes;
        std::queue<char*> requests;


        bool getRequest();
        void sendReply (char *_message, int client_port, char* client_hostname);        

    public:

        Server(char * _listen_hostname, int _listen_port);
        bool listen();
        ~Server();
};
#endif // SERVER_H
