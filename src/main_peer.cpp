#include "Peer.h"
#include <string>
#include <iostream>
Peer pe("10.7.57.15", 4444,"10.7.57.200",4444);
void sendMsg(Message& msg)
{
	pe.execute(msg);
	
}
void logs()
{
	pe.login("yasmin","heyy");
}
int main()
{
	
	

	
	Message msg(StatusRequest, "10.7.57.15", 4444, "10.7.57.200", 4444);	
	
	msg.Flatten();
	msg.printMessageDetails();
	cout<<"LOGGING IN\n";
	thread t2 (logs);	

	t2.join();
	this_thread::sleep_for (std::chrono::seconds(3));

	cout<<"Requesting IN\n";
	thread t1 (sendMsg, ref(msg));	
	t1.join();
	this_thread::sleep_for (std::chrono::seconds(200));
	pe.halt();

	return 0;

}
