#include "Server.h"
#include "Client.h"
#include <string>
#include <cstring>
#include <iostream>

using namespace std;

int main()
{

	char* server_hostname = new char[15];

	cout << "Enter Server IP: ";
	cin >> server_hostname;

	//char* server_hostname = server_ip;
	char* client_hostname = "10.7.57.200";

	Client client;

	while (true)
	{
		char* msg = new char[2048];
		memset(msg, '\0', strlen(msg));

		cout << "Enter new message: ";
		cin >> msg;

		client.execute(msg, 4444, client_hostname, server_hostname);

		delete [] msg;
	}

	return 0;
}
