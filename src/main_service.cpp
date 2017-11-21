#include "Service.h"
#include <string>
#include <iostream>
#include <thread>
using namespace std;

int main()
{
	char* server_hostname = "10.7.57.229";
	Service service(server_hostname, 4444);
	
	while (!service.listen());
	std::cout << "Server Terminated."; 

	return 0;
}
