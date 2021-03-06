#include "Server.h"
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/param.h>
#include <sys/utsname.h>
#include <stdlib.h>  
#include <stdio.h>
#include <string>
using namespace std;

Server::Server(char * _listen_hostname, int _listen_port)
{
	this->udpSocket = new UDPSocket();

	udpSocket->initializeServer(_listen_hostname, _listen_port);
}

bool Server::getRequest()
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

void Server::sendReply (char *_message, int client_port, char *client_hostname)
{
	char* ack;

	cout << "Server echoed reply to be sent: \n";
	for (int i =0; i < 20; ++i)
		cout << _message[i];

	cout << '\n';
	int n = udpSocket->writeToSocket(_message, 2048, client_port, client_hostname);
 }


bool Server::listen()
{
	return getRequest();
}

Server::~Server(){}
