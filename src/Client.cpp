#include "Client.h"
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

Client::Client()
{
	udpSocket = new UDPSocket();
	udpSocket->initializeClient();
}

char * Client::execute(char * message, int server_port, char *hostname, char *server_host)
{
	const int SIZE = 2048;
	char *ack;


	char* message_ = new char[SIZE];
	memset(message_, '\0', 2048);
	string s = to_string(udpSocket->getMyPort());
	const char *port = s.c_str();

	for(int i =0; i < strlen(message); i++)
	{
		message_[i] = message[i];
	}

	sprintf(message_ + 2043, port); //store port

	sprintf(message_ + 2027, hostname);	//store ip

	int n = udpSocket->writeToSocketAndWait (message_, 2048, server_port, server_host, 1000 , ack);

    if (n > 0) 
    	return message_;
	else 
		return "No Acknowledgement Recieved\n";
}

Client::~Client(){}
