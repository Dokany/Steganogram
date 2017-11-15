
#include "StatusData.h"
using namespace std;
StatusData::StatusData()
{}
bool StatusData::addUser(string name, string address)
{
	if(name.find(seperator)!=-1 || address.find(seperator)!=-1)
	{
		perror("restriced character used\n");
		return false;
	}
	onlineUsers.push_back(make_pair(name,address));
	return true;
}
vector<pair<string,string> > StatusData::getOnlineUsers()
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
	for(pair<string,string> p:onlineUsers)
	{
		flattened+=p.first;
		flattened+=seperator;
		flattened+=p.second;
		flattened+=seperator;
	}
	return true;
}
bool StatusData::unFlatten()
{
	onlineUsers.clear();
	stringstream ss(flattened);
	string user,add;
	while(ss>>user>>add)
	{
		onlineUsers.push_back(make_pair(user,add));
	}
	return true;
}       
StatusData::~StatusData(){}