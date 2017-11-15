#include "AuthData.h"
using namespace std;
AuthData::AuthData(){
	username=password="";
}
bool AuthData::setUsername(string s)
{
	if(username.find(seperator)!=-1)
	{
		perror("restriced character used\n");
		return false;
	}
	username=s;
	return true;
}
bool AuthData::setPassword(string s)
{
	if(password.find(seperator)!=-1)
	{
		perror("restriced character used\n");
		return false;
	}
	password=s;
	return true;
}
string AuthData::getUsername()
{
	return username;
}
string AuthData::getPassword()
{
	return password;
}
bool AuthData::Flatten()
{
	if(username=="" || password=="")
	{
		perror("Data not ready to be flattened\n");
		return false;
	}
	flattened="";
	flattened+=username;
	flattened+=seperator;
	flattened+=password;	
	return true;
}
bool AuthData::unFlatten()
{
	if(flattened=="")
	{
		perror("Data unavailable\n");
		return false;
	}
	stringstream s(flattened);
	s>>username>>password;
	return true;
}        
AuthData::~AuthData(){}