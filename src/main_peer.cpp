#include "Peer.h"
#include <string>
#include <cstring>
#include <iostream>

using namespace std;

int main()
{

	char* server_hostname = new char[15];

	cout << "Enter Server IP: ";
	cin >> server_hostname;

	char* client_hostname = "10.7.57.200";

	Peer client(NULL, 0);

    //while (true)
    for (int i = 0; i < 10; ++i)
	{
		// char* msg = new char[2048];
		// memset(msg, '\0', strlen(msg));

		// cout << "Enter new message: ";
		// cin >> msg;

		client.execute("Hiiiii", 4444, client_hostname, server_hostname);

		//delete [] msg;
	}

	return 0;
}
