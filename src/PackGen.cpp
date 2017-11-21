#include "PackGen.h"
#include <algorithm>
#include<iostream>
PackGen::PackGen(int max_size){
	this->max_size=max_size;
}
vector<Message> PackGen::fragment(Message m)
{
	vector<Message> tmp;
	if(m.getDataSize()<=max_size)
	{
		m.setSeg(1,1);
		tmp.push_back(m);

	}
	else
	{
		int total = ceil((double)m.getDataSize()/(double)max_size);
		string fullData = m.getData();
		string IP = m.getOwnerIP();
		int port = m.getOwnerPort();
		int ID = m.getID();
		MessageType mt = m.getType();
		int start = 0;
		for(int seg = 1; seg<=total; seg++)
		{
			Message mm;
			mm.setMessageID(ID);
			mm.setIP(IP);
			mm.setPort(port);
			mm.setSeg(total, seg);
			mm.setType(mt);
			if(seg!=total)
				mm.setDataSize(max_size);
			else
				mm.setDataSize(m.getDataSize()%max_size);
			string partialData = fullData.substr(start,max_size);
			mm.setFlattenedData(partialData);
			start+=max_size;

			tmp.push_back(mm);
		}
	}
	return tmp;
}

struct comp
{
	bool operator()(Message &a, Message &b)
	{
		return a.getSegNum()<b.getSegNum();
	}
};

Message PackGen::defragment(vector<Message> vm)
{
	if(vm.size()==0)
	{
		perror("No Messages found to defragment\n");
		Message tt;
		return tt;
	}
	sort(vm.begin(),vm.end(),comp());
	string IP = vm[0].getOwnerIP();
	int port = vm[0].getOwnerPort();
	int ID = vm[0].getID();
	MessageType mt = vm[0].getType();
	string fullData="";
	int total_data_size = 0;
	for(Message m:vm)
	{
		fullData+=m.getData();
		total_data_size += m.getDataSize();
	}
	Message mm;
	mm.setMessageID(ID);
	mm.setIP(IP);
	mm.setPort(port);
	mm.setType(mt);
	mm.setFlattenedData(fullData);
	mm.setDataSize(total_data_size);
	mm.setSeg(1,1);
	return mm;
}
PackGen::~PackGen(){}