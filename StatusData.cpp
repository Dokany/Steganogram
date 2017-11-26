
#include "StatusData.h"
using namespace std;
StatusData::StatusData()
{}
bool StatusData::addUser(string name, string address, int port)
{
	if(name.find(seperator)!=-1 || address.find(seperator)!=-1)
	{
		perror("restriced character used\n");
		return false;
	}
	onlineUsers.push_back(make_pair(name,make_pair(address,port)));
	return true;
}
vector<pair<string,pair<string, int> > >  StatusData::getOnlineUsers()
{
	return onlineUsers;
}
bool StatusData::Flatten()
{
	if(onlineUsers.size()==0)
	{
		perror("Data not ready to be flattened\n");
		return false;
	}
	flattened="";
	for(pair<string,pair<string,int> > p:onlineUsers)
	{
		flattened+=seperator;
		flattened+=p.first;
		flattened+=seperator;
		flattened+=p.second.first;
		flattened+=seperator;
		flattened+=to_string(p.second.second);
	}
	return true;
}
bool StatusData::unFlatten(string s)
{
	onlineUsers.clear();
	stringstream ss(s);
	string user,add,po;
	while(ss>>user>>add>>po)
	{
		int port = stoi(po);
		onlineUsers.push_back(make_pair(user,make_pair(add,port)));
	}
	return true;
}       
StatusData::~StatusData(){}