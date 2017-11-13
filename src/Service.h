#include <map>
#include <functional>
#include <fstream>
#include <string>
#include <utility>
#include "UDPSocket.h"
#include <exception>
#include <thread>
#include <mutex>
#include <vector>
#include <queue>
#include <condition_variable>
#include <ctime>
using namespace std;

#ifndef SERVICE_H
#define SERVICE_H

class Service
{
private:

	UDPSocket * udpSocket;

	std::mutex mutex_;
    std::condition_variable cond;

    std::vector<std::thread> processes;
    std::queue<char*> requests;


    bool getRequest();
    void sendReply (char *_message, int client_port, char* client_hostname);  

	ifstream inputFile;
	hash<string> str_hash;
	map<long unsigned int, pair<long unsigned int, bool>> user_directory;
	map<string, time_t> online_directory;

public:

	Service(char * _listen_hostname, int _listen_port);
	void authenticate(string username, string password);
	void pingHandler(string IP, time_t current_time);
	void pingRefresh();
	bool listen();
	~Service();
};
#endif