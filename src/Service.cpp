#include "Service.h"
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/param.h>
#include <sys/utsname.h>
#include <stdlib.h>  
#include <stdio.h>
#include <string>
using namespace std;

Service:: Service(char * _listen_hostname, int _listen_port)
{
	this->udpSocket = new UDPSocket();

	udpSocket->initializeServer(_listen_hostname, _listen_port);

	for (int i = 0; i < 5; ++i)
	{
		processes.push_back(std:: thread([&](){

		while (true) {
			std::unique_lock<std::mutex> lck (mutex_);
			cond.wait(lck);		// release lck and waits
			cout << std::this_thread::get_id() << " : " << requests.front() << endl;
			requests.pop();
			//std::this_thread::sleep_for(std::chrono::seconds(10));
			lck.unlock();		// release lck
		}

		}));
	}

	long unsigned int str_username;
	long unsigned int str_password;
	inputFile.open("auth.txt");

	if (inputFile.is_open())
	{
		while (!inputFile.eof())
		{
			inputFile >> str_username >> str_password;
			user_directory[str_username].first = str_password;
			user_directory[str_username].second = false;
		}
	}

	else cout << "Unable to open file\n";

}

bool Service::getRequest()
{
	char * buffer;
	char message1[2048];
	int rr;
	string port = "";
	char* ptr;
	int client_port;
	char* client_hostname = new char[15];

	memset(message1, 0, 2048);
	if((rr = udpSocket->readFromSocketWithNoBlock(message1 , 2048) )< 0)
	{
		printf("Message not recieved.\n");
	}

	else
	{
		for(int i =0; i < 5; i++)
		{
			port += message1[2043 + i];
			
		}

		for(int i =0; i < 16; i++)
		{
			client_hostname[i] = message1[2027 + i];
		}


		client_port = atoi(port.c_str());

		cout << "Client Port no.: " << client_port << endl;
		cout << "Client IP Address: " << client_hostname << endl;

		// Mutex Thread Handling
		std::unique_lock<std::mutex> lck (mutex_);
		requests.push(message1);
		cond.notify_one();		// release lock

		sendReply(message1, client_port, client_hostname);

		if(message1[0] == 'q')
		{
			for(int i= 1; i<= 2026; i++)
				{
					if(message1[i] != '\0') return false;
				}

			return true;
		}
		else return false;

	}
}

void Service::sendReply (char *_message, int client_port, char *client_hostname)
{
	char* ack;

	cout << "Server echoed reply to be sent: \n";
	for (int i =0; i < 20; ++i)
		cout << _message[i];

	cout << '\n';
	int n = udpSocket->writeToSocket(_message, 2048, client_port, client_hostname);
 }


bool Service::listen()
{
	return getRequest();
}

void Service::authenticate(string username, string password)
{
	auto search = user_directory.find(str_hash(username));

	if(search != user_directory.end()) 
	{	
		//username exists
		if (user_directory[str_hash(username)].first == str_hash(password))

		{
			cout << "Redirecting..\n";
			online_directory[username] = time(NULL);
		}

		else cout << "Incorrect Password\n";
	}

	else cout << "Username does not exist\n";
}

void Service::pingHandler(string username, time_t current_time)
{
	auto search = online_directory.find(username);

	if(search != online_directory.end())
		//username online
		search->second = current_time;
}

void Service::pingRefresh()
{
	thread t([&](){
	    cout << "ping thread\n";

	    time_t current_time;
	    time(&current_time);

	    for (auto &a : online_directory) 
			{
				if (abs(a.second - current_time) > 600)
					online_directory.erase(a.first);
			}
    });

    t.join();
}

Service::~Service(){
	for (std::thread &t : processes) t.join();
}