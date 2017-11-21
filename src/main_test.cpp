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
Peer p("10.7.57.249", 4444);

void sendMsg(Message& msg)
{
	p.execute(msg);
	
}


int main()
{
	Message msg(ImageReply, "10.7.57.249", 4444, "10.7.57.200", 4444);	
	ImageData img("dog_s.jpg","dog_s.jpg" );
	msg.setData(img);
	msg.Flatten();
	msg.printMessageDetails();
  	thread t1 (sendMsg, ref(msg));	

  	// sending messages thread
 	cout << "Sending and receiving threads running concurrently...\n";

	// synchronize threads
 	t1.join();
 	this_thread::sleep_for (std::chrono::seconds(10));
 	
	// cout << "Threads completed.\n";
	
	// Message msg2(Terminate,  "10.7.57.249", 4444, "10.7.57.249", 4444);	
	// //msg.Flatten();
	// thread t2 (sendMsg, ref(msg2));	
	// t2.join();

	p.halt();
	
	return 0;
}
