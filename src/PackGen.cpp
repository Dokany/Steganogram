#include "PackGen.h"
#include <algorithm>
#include<iostream>
#include<fstream>
PackGen::PackGen(int max_size){
	this->max_size=max_size;
}
vector<Message> PackGen::fragment(Message m)
{
	vector<Message> tmp;
	m.Flatten();
	if(m.getDataSize()<=max_size)
	{
		m.setSeg(1,1);
		tmp.push_back(m);

	}
	else
	{
		int total = ceil((double)m.getDataSize()/(double)max_size);
		string fullData = m.getData();
		string ownerIP = m.getOwnerIP();
		int ownerPort = m.getOwnerPort();
		string targetIP = m.getTargetIP();
		int targetPort = m.getTargetPort();
		int ID = m.getID();
		MessageType mt = m.getType();
		int start = 0;
		for(int seg = 1; seg<=total; seg++)
		{
			Message mm;
			mm.setMessageID(ID);
			mm.setOwnerIP(ownerIP);
			mm.setOwnerPort(ownerPort);
			mm.setTargetIP(targetIP);
			mm.setTargetPort(targetPort);
			mm.setSeg(total, seg);
			mm.setType(mt);
			int mx;
			if(seg!=total)
			{
				mm.setDataSize(max_size);
				mx=max_size;
			}
			else{
				mm.setDataSize(m.getDataSize()%max_size);
				mx=m.getDataSize()%max_size;
			}

				
			string partialData = fullData.substr(start,mx);
			//cout<<partialData.size()<<endl;
			mm.setFlattenedData(partialData);
			//mm.Flatten();
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
	string ownerIP = vm[0].getOwnerIP();
	int ownerPort = vm[0].getOwnerPort();
	string targetIP = vm[0].getTargetIP();
	int targetPort = vm[0].getTargetPort();
	int ID = vm[0].getID();
	MessageType mt = vm[0].getType();
	string fullData="";
	int total_data_size = 0;
	for(Message m:vm)
	{

		string cur = m.getData();
		fullData+=cur;
		total_data_size += m.getDataSize();
	}
	Message mm;
	mm.setMessageID(ID);
	mm.setOwnerIP(ownerIP);
	mm.setOwnerPort(ownerPort);
	mm.setTargetIP(targetIP);
	mm.setTargetPort(targetPort);
	mm.setType(mt);
	mm.setFlattenedData(fullData);
	mm.setDataSize(total_data_size);
	mm.setSeg(1,1);
	mm.Flatten();
	return mm;
}
PackGen::~PackGen(){}