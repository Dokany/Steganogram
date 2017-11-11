#include "Peer.h"
#include <string>
#include <iostream>

int main()
{
	char* server_hostname = "10.7.57.117";

	Peer server(server_hostname, 4444);

	while (!server.listen());
	std::cout << "Server Terminated."; 

	return 0;

}
