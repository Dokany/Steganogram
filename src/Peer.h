#include "Message.h"
#include "UDPSocket.h"
#include "PackGen.h"
#include <thread>
#include <mutex>
#include <vector>
#include <queue>
#include <map>
#include <atomic>
#include <condition_variable>

#ifndef PEER_H
#define PEER_H

enum MessageStatusType{sending, sent, lost};
class Peer
{
    private:
        UDPSocket * udpSocket_client;
        UDPSocket * udpSocket_server;

        thread main_send, main_receive, main_listen;
        int myPort;
        char * myHostname;

      	std::mutex mutex_1, mutex_2, mutex_3;
        std::condition_variable cond, cond1;

        std::atomic<bool> listening;

        std::vector<std::thread> processes_r, processes_s, request_workers;
        std::queue<Message> requests;
        std::queue<char*> requests_process; 
        std::queue<string> replies;

        std::map<int,MessageStatusType> messageSentStatus; 
        std::map<string,vector<Message> > segmentTable;
        std::map<string,bool> receivedMessageHistory;

        const int max_size = 50000;

        bool getRequest();
        void listen();
        void processRequest();

        void sendMain();
        void sendHandler(Message msg, int port, char *hostname, int timeout);
        void sendWithoutWaiting(Message m, int port, char *hostname);
        
        void receiveHandler(string message_id, int timeout);
        void handleReceivedMessage(Message m, string id);
        void receiveMain();

    public:
        Peer(char * _listen_hostname, int _listen_port);
        
        void execute(Message msg);

        void halt();

        ~Peer();
};
#endif // PEER_H
