#include "PingData.h"
PingData::PingData(){

}

PingData::PingData(string user)
{
	if(user.find(' ')!=-1)
	{
		perror("username invalid\n");
	}
	username=user;
}

bool PingData::setUsername(string user)
{	
	if(user.find(' ')!=-1)
	{
		perror("username invalid\n");
		return false;
	}
	username=user;
	return true;
}
string PingData::getUsername()
{
	return username;
}

bool PingData::Flatten()
{
	flattened=username;
	return true;
}
bool PingData::unFlatten(string s)
{
	username=s;
}
      
PingData::~PingData()
{

}