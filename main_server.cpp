#include "Server.h"
#include "Service.h"
#include <string>
#include <iostream>

int main()
{
	char* server_hostname = "10.7.57.229";
	Server server(server_hostname, 4444);
	
	while (!server.listen());
	std::cout << "Server Terminated."; 

	return 0;

}
