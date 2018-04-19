#include "Service.h"
#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <functional>
#include <chrono>
using namespace std;

int main3()
{
	char* server_hostname = "10.7.57.200";
	Service serv(server_hostname, 4444);
	
	std::this_thread::sleep_for(std::chrono::seconds(500));

	serv.halt();
	return 0;
}