#include "Peer.h"
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/param.h>
#include <sys/utsname.h>
#include <stdlib.h>  
#include <stdio.h>
#include <string>
#include <cstdio>
#include <thread>
#include <mutex>
using namespace std;

Peer::Peer(char * _listen_hostname, int _listen_port)
{
    this->udpSocket_server = new UDPSocket();
    this->udpSocket_client = new UDPSocket();

    udpSocket_server->initializeServer(_listen_hostname, _listen_port);
	udpSocket_client->initializeClient();
}

bool Peer::getRequest()
{
	char * buffer;
	char message1[2048];
	int rr;
	string port = "";
	char* ptr;
	int client_port;
	char* client_hostname = new char[15];

	memset(message1, 0, 2048);
	if((rr = udpSocket_server->readFromSocketWithNoBlock(message1 , 2048) )< 0)
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

void Peer::sendReply (char *_message, int client_port, char *client_hostname)
{
	char* ack;

	cout << "Server echoed reply to be sent: \n";
	for (int i =0; i < 20; ++i)
		cout << _message[i];

	cout << '\n';
	int n = udpSocket_server->writeToSocket(_message, 2048, client_port, client_hostname);
 }

 char * Peer::execute(char * message, int server_port, char *hostname, char *server_host)
 {
     const int SIZE = 2048;
     char *ack;
 
     char* message_ = new char[SIZE];
     memset(message_, '\0', 2048);
     string s = to_string(udpSocket_client->getMyPort());
     const char *port = s.c_str();
 
     for(int i =0; i < strlen(message); i++)
     {
         message_[i] = message[i];
     }
 
     sprintf(message_ + 2043, port); //store port
 
     sprintf(message_ + 2027, hostname);	//store ip
 
     int n = udpSocket_client->writeToSocketAndWait (message_, 2048, server_port, server_host, 1000 , ack);
 
     if (n > 0) 
         return message_;
     else 
         return "No Acknowledgement Recieved\n";
 }

bool Peer::listen()
{
	return getRequest();
}

Peer::~Peer(){}
