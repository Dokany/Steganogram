#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <functional>
#include "Peer.h"
#include "Message.h"
#include <chrono>
using namespace std;

//server
Peer p("10.7.57.200", 4444);



int main()
{
	
 	this_thread::sleep_for (std::chrono::seconds(300));
 	
	// cout << "Threads completed.\n";
	
	// Message msg2(Terminate,  "10.7.57.249", 4444, "10.7.57.249", 4444);	
	// //msg.Flatten();
	// thread t2 (sendMsg, ref(msg2));	
	// t2.join();

	p.halt();
	
	return 0;
}
