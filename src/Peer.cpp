#include "Peer.h"
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstring>
#include <sys/param.h>
#include <sys/utsname.h>
#include <stdlib.h>  
#include <stdio.h>
#include <string>
#include <cstdio>
#include <mutex>
#include <algorithm>
#include <chrono>
using namespace std;

Peer::Peer(char * _listen_hostname, int _listen_port)
{
    this->udpSocket_server = new UDPSocket();
    this->udpSocket_client = new UDPSocket();

    myPort = _listen_port;
    myHostname = new char[strlen(_listen_hostname)+1];
    strcpy(myHostname,_listen_hostname);

    udpSocket_server->initializeServer(_listen_hostname, _listen_port);
	udpSocket_client->initializeClient();

	listening = true;

	main_listen = thread(&Peer::listen,this);

	sendMain();
	receiveMain();
	// main_receive = thread(&Peer::receiveMain,this);
	// main_send = thread(&Peer::sendMain,this);	
	// receiving messages thread
	// thread t2 (sendMsg, ref(msg));
}


void Peer::execute(Message msg)
{
	// Mutex Thread Handling
	cout << "Message to be sent.\n";
	std::unique_lock<std::mutex> lck (mutex_1);
	requests.push(msg);
	cond.notify_one();		// release lock
}

void Peer::sendMain()
{
	for (int i = 0; i < 10; ++i)
	{
		processes_s.push_back(std:: thread([&](){
			while (true) {
				std::unique_lock<std::mutex> lck (mutex_1);
				if (!listening) return;
				cond.wait(lck);		// release lck and waits
				
				if (listening)
				{
					Message msg = requests.front();
					msg.setMessageID(msg.getID()+msg.getOwnerIP());
					msg.Flatten();
					char *IP = new char[msg.getTargetIP().length() + 1];
					memcpy(IP, msg.getTargetIP().c_str(),msg.getTargetIP().length()+1);
					cout << std::this_thread::get_id() << "\t Sending message to IP: " << msg.getTargetIP() <<" : "<<msg.getTargetPort() << endl;
					//cout << std::this_thread::get_id() << "\t Sending message from IP: " << myHostname <<" : "<<myPort << endl;
					requests.pop();
					lck.unlock();
					sendHandler(msg, msg.getTargetPort(), IP, 75);

					cout << "Message Sent Handled.\n";
					//std::this_thread::sleep_for(std::chrono::seconds(10));
							// release lck
				}
				else 
				{
					cout << "Worker thread no." << std::this_thread::get_id()<<" is done sending.\n";
					return;
				}
			}
		}));
	}
}

void Peer::sendHandler(Message msg, int port, char *hostname, int timeout)
{
	//fragment, send all fragments (w/out wait)
	//while(messageSentStatus[message_id]!=sent &&timeout)
	// if messageSentStatus[message_id]== lost, resend all fragments
	//end while
	//0 sending, 1 sent, 2 resend
	PackGen pg(max_size);
	vector<Message> msgs= pg.fragment(msg);
	int ii=0;
    time_t start = time(NULL);
    time_t endwait = start + timeout;
    string msg_id = msg.getID();
    messageSentStatus[msg_id] = lost;
	while(start < endwait && messageSentStatus[msg_id]!=sent)
	{
		//
		if(messageSentStatus[msg_id]==lost)
		{
			cout<<" sending: "<< ii++<<endl;
			for(Message mm:msgs)
			{
				//mm.Flatten();
				cout<<"sending "<<mm.getSegNum()<<" / "<<mm.getSegTot()<<endl;
				string temp = mm.getFlattenedMessage();
				//cout<<"sendhandler: "<<temp<<endl;
				if(temp=="")cout<<"temp is empty\n";
				char *cstr = new char[temp.length() + 1];
				memcpy(cstr, temp.c_str(),temp.length()+1);
				cout<<"SENDTO LENGTH: "<<temp.length()+1<<endl;
				//std::replace(temp.begin(), temp.end(), '\0', ' ');
			/*	cout<<"KARIIIIIIIIIIIIIIIIIIIIIIIIIIM\n";
				for(int i=0;i<=temp.length();i++)
				{
					cout<<cstr[i];
				}cout<<endl;*/
				while((udpSocket_client->writeToSocket(cstr, temp.length()+1, port, hostname))<0);
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}
			messageSentStatus[msg_id]=sending;
		}
		start = time(NULL);
	}
	cout << "Done waiting for ack.\n";
}

void Peer::halt()
{
	
	listening = false;

	//while (main_listen.joinable());

	main_listen.join();

	cond.notify_all();
	cond1.notify_all();

	for (thread& t : processes_s) t.join();

	for (thread& t : processes_r) t.join();
	
	//main_send.join();
	//main_receive.join();
}

void Peer::listen()
{
	while(listening) {
		getRequest();
	}
	
}


bool Peer::getRequest()
{
	char msg1[max_size];
	int rr;
	//memset(msg1, 0, max_size);

	// Listening for messages on socket
	if((rr = udpSocket_server->readFromSocketWithNoBlock(msg1 , max_size) )> 0)
	{
		//Create message object
			

		Message msg;
		string recv="";
		recv=string(&msg1[0], &msg1[rr]);
		cout<<"RECV LENGHT "<<recv.length()<<endl;
		/*for(int i=0;i<=rr;i++)
		{
			recv+=msg1[i];
		}*/

		msg.unFlatten(recv);
		cout << "Message received "<<msg.getSegNum()<<" "<<msg.getSegTot()<<" ID: "<<msg.getID()<<endl;
		/*if(msg.getType()==MessageType(Terminate)){
			cout<<"Terminating getRequest\n";
			//halt();
			return false;
		}*/
		string unique_id = msg.getID();
		auto search = receivedMessageHistory.find(unique_id);

		if(search == receivedMessageHistory.end()) 
		{	
			//Message doesn't exist, assign to new thread
			// Mutex Thread Handling

			cout << "Message not found in history\n";
			std::unique_lock<std::mutex> lck (mutex_2);
			receivedMessageHistory[unique_id] = false;
			messageSentStatus[unique_id] = sending;
			segmentTable[unique_id].push_back(msg);
			replies.push(unique_id);
			cond1.notify_one();		// notify that a new message is received 
		}
		else if (!(search->second)) // if message is not complete
		{
			//messageSentStatus[msg.getID()] = sending;
			bool found=false;
			for(Message mm:segmentTable[unique_id])if(mm.getSegNum()==msg.getSegNum())found=true;
			if(!found)segmentTable[unique_id].push_back(msg);
			else cout<<"duplicate found\n";
		}
	}
	return true;
}

void Peer::receiveMain()
{
	for (int i = 0; i < 10; ++i)
	{
		processes_r.push_back(std:: thread([&](){
			while (true) {
				std::unique_lock<std::mutex> lck2 (mutex_2);
				if (!listening) return;
				cond1.wait(lck2);		// release lck and waits
				
				if (listening)
				{
					string msgID = replies.front();
					cout << std::this_thread::get_id() << ": Recieving Message" << endl;
					replies.pop();
					//std::this_thread::sleep_for(std::chrono::seconds(10));
					lck2.unlock();
					receiveHandler(msgID, 25);
							// release lck
				}
				else 
				{
					cout << "Worker Thread no." << std::this_thread::get_id()<<" is done recieving.\n";
					return;
				}
			}
		}));
	}
}


void Peer::sendWithoutWaiting(Message m, int port, char *hostname)
{
	PackGen pg(max_size);

	vector<Message> v = pg.fragment(m);
	for(Message mm:v)
	{
		mm.Flatten();
		string temp = mm.getFlattenedMessage();
		char *msg = new char[temp.length() + 1];
		strcpy(msg, temp.c_str());
		while((udpSocket_client->writeToSocket(msg, temp.length() + 1, port, hostname)<0));
	}
}

void Peer::receiveHandler(string message_id, int timeout)
{
	//make sure all segments are recevied within a timeout
	time_t start = time(NULL);
    time_t endwait = start + timeout;
    bool complete = false;
    int total = segmentTable[message_id].back().getSegTot();
    string targetIP =  segmentTable[message_id].back().getOwnerIP();
    int targetPort = segmentTable[message_id].back().getOwnerPort();

    while(start < endwait && !complete)
	{
		complete = total==segmentTable[message_id].size();
		start = time(NULL);
		//cout<<total<< " "<<segmentTable[message_id].size()<<endl;
	}
	cout<<"I am out of the wait for all segments with total seg="<<segmentTable[message_id].size()<<endl;
	int myPort = segmentTable[message_id].back().getTargetPort();
	string myIP = segmentTable[message_id].back().getTargetIP();
	
	if(!complete)
	{
		//if not send a neg ack
		Message neg(NegAck, myIP,myPort,targetIP, targetPort);
		AckData nd(_NegAck, segmentTable[message_id].back().getID());
		neg.setData(nd);
		neg.Flatten();
		char *hn = new char[targetIP.length() + 1];
		memcpy(hn, targetIP.c_str(),targetIP.length() + 1);
		sendWithoutWaiting(neg, targetPort,hn);

	}
	else 	
	{
		//else send an ack, defragment and handle



		//defragment
		PackGen pg(max_size);
		Message defraggedMessage = pg.defragment(segmentTable[message_id]);
		//defraggedMessage.Flatten();
		int size = defraggedMessage.getData().length();
		//cout<<"defraggedMessage data size: "<<size<<endl;
		//send ack
		MessageType mmt = defraggedMessage.getType();
		if(mmt!=Ack && mmt!=NegAck && mmt!=Terminate)
		{
			
			Message ackMessage(Ack, myIP,myPort, targetIP, targetPort);
			AckData ad(_Ack, segmentTable[message_id].back().getID());
			ackMessage.setData(ad);
			ackMessage.Flatten();
			char *hn = new char[targetIP.length() + 1];
			
			memcpy(hn, targetIP.c_str(),targetIP.length() + 1);
			sendWithoutWaiting(ackMessage, targetPort,hn);
		}	


		//handle
		handleReceivedMessage(defraggedMessage, message_id);
	}
	cout<<"exiting receive handler\n";
}

void Peer::handleReceivedMessage(Message m, string id)
{
	MessageType mt = m.getType();
	receivedMessageHistory[id]=true;
	string data=m.getData();
	switch(mt)
	{
		case Ack:
		{
			AckData ad;
			ad.unFlatten(data);
			messageSentStatus[ad.getMessageID()]=sent;
			cout<<"Ack Received of Message: "<<ad.getMessageID()<<endl;
			break;
		}
		case NegAck:
		{
			AckData ad;
			ad.unFlatten(data);
			messageSentStatus[ad.getMessageID()]=lost;
			break;
		}
		case ImageReply:
		{
			ImageData id;
			id.unFlatten(data);
			ofstream out;
			string path=m.getOwnerIP();
			path+='_';
			path+=id.getName();
			out.open(path);
			string iim=id.getImage();
			cout<<" IMAGE IN PEER AFTER ALL IS: "<<iim.length()<<endl;
			out<<iim;
			out.close();
			break;

		}
		case StatusReply:
		{
			StatusData sd;
			sd.unFlatten(data);
			cout<<"Received online users: \n";
			vector<pair<string,pair<string, int> > > list = sd.getOnlineUsers();
			for(pair<string,pair<string, int> > t:list)
			{
				string name = t.first;
				string address = t.second.first;
				int port = t.second.second;
				cout<<name<<" "<<address<<" "<<port<<endl;
			}
			cout<<endl;
			break;

		}
		case ImageListReply:
		{
			ImageListData ild;
			ild.unFlatten(data);
			cout<<"Received Image List: \n";
			vector<string> list = ild.getImageList();
			for(string t:list)
			{
				cout<<t<<endl;
			}

			cout<<endl;
			break;

		}
		//TO BE IMPLEMENTED AFTER STEGANOGRAPHY
		// case ImageListRequest:
		// {

		// 	break;
		// }
		// case ViewsRequest:
		// {

		// 	break;
		// }
		// case DenyRequest
		// {

		// 	break;
		// }
		// case ImageRequest:
		// {

		// 	break;
		// }
		// case ViewsReply: 
		// {
		// 	break;
		// }

		//to be added to Service and removed from here
		/*
		SENT FROM USER TO SERVICE
		case StatusRequest:
		case Auth:
		case Ping:

		*/
	}
}

Peer::~Peer(){

	// listening = false;

	// cond.notify_all();
	// cond1.notify_all();

	// for (thread& t : processes) t.join();

	// main_listen.join();
	// main_send.join();
	// main_receive.join();
} 	  