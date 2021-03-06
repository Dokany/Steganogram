#include "Message.h"
#include "UDPSocket.h"
#include "PackGen.h"

#include <thread>
#include <mutex>
#include <vector>
#include <queue>
#include <map>
#include <atomic>
#include <set>
#include <condition_variable>
#include <QtCore>
#include <QtGui>
#include <QObject>

#ifndef PEER_H
#define PEER_H
enum MessageStatusType{sending, sent, lost};
class Peer : public QObject
{
    Q_OBJECT
    private:
        UDPSocket * udpSocket_client;
        UDPSocket * udpSocket_server;

        std::thread main_send, main_receive, main_listen, main_pinger;
        int myPort, servicePort;
        char * myHostname, *serviceHostname ;
        string username;

        std::mutex mutex_1, mutex_2, mutex_3;
        std::condition_variable cond, cond1;

        std::atomic<bool> listening, logged_in, waiting;

        std::vector<std::thread> processes_r, processes_s, request_workers;
        std::queue<Message> requests;
        std::queue<char*> requests_process;
        std::queue<string> replies;

        std::map<string,MessageStatusType> messageSentStatus;
        std::map<string,vector<Message> > segmentTable;
        std::map<string,bool> receivedMessageHistory;

        string auth_id;
        std::map<string,pair<string,int> > nameToAddress;
        std::map<string,pair<string,int> > currentOnlineUsers;
        std::map<string,vector<pair<string,int> > > currentImageViewers;
        std::map<string,int> imageStatus;
        std::set<string> localImages, currentImageListReply;
        std::map<string,string> pendingImageOwners; //messageid and user to add to currentImageViewers

        const int max_size = 50000;

        bool getRequest();
        void listen();
        void processRequest();

        void sendMain();
        void sendHandler(Message msg, int port, char *hostname, int timeout);
        void sendWithoutWaiting(Message m, int port, char *hostname);

        void ping();
        int extract(string );
        void receiveHandler(string message_id, int timeout);
        void handleReceivedMessage(Message m, string id);
        void receiveMain();

        string mbox_request, mbox_title, mbox_image_name, mbox_ip, mbox_id, mbox_path;
        int mbox_port,mbox_count;
        MessageType mbox_mt;
        bool mbox_bool, mbox_mine;


    signals:
        void terminateProgram();
        void firstWindow();
        void countWindow();
    public:
        Peer();
        Peer(char * _listen_hostname, int _listen_port, char* service_hostname, int service_port);
        Peer(const Peer& other);
        Peer& operator=(const Peer& other);
        std::map<string,pair<string,int> > getStatus();
        vector<pair<string,int> > getCurrentImageViewers(string);
        void start();
        int checkImage(string name, string ip);
        void addImage(string name, string path);
        void sendImage(string name, string IP, int port, int count);
        std::set<string> getMyImages();
        std::set<string> getUserImages(string username);
        void setLocalImages(std::set<string>);
        string getMBoxTitle();
        string getMBoxRequest();
        void setMBoxBool(bool);
        int login(string username, string password);
        void execute(Message msg);
        void requestImage(string name, string user);
        void logOff();
        void requestViews(string name, string user);
        void addViews(int count, string image, string user);
        void halt();
        void processReply();
        void setMBoxCount(int);
        int getMBoxCount();
        string viewImage(string path);
        int getImageStatus(string name);

        bool getMBoxMine();
        string getMBoxPath();
        string getMBoxName();
        ~Peer();
};
#endif // PEER_H
