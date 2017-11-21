#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <functional>
#include "Peer.h"
#include "AckData.h"
#include "Message.h"
#include <chrono>
using namespace std;

//server
Peer p("10.7.57.117", 4444);

void sendMsg(Message& msg)
{
	p.execute(msg);
	
}


int main()
{
	Message msg(Ack, "10.7.57.249", 4444, "10.7.57.249", 4444);	
	AckData ack(AckType(0), msg.getID());
	msg.setData(ack);
	msg.Flatten();

  	thread t1 (sendMsg, ref(msg));	

  	// sending messages thread
 	cout << "Sending and receiving threads running concurrently...\n";

	// synchronize threads
 	t1.join();
 	this_thread::sleep_for (std::chrono::seconds(3));
 	
	cout << "Threads completed.\n";
	
	Message msg2(Terminate,  "10.7.57.249", 4444, "10.7.57.249", 4444);	
	//msg.Flatten();
	thread t2 (sendMsg, ref(msg2));	
	t2.join();

	p.halt();
	
	return 0;
}
