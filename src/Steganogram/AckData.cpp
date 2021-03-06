#include "AckData.h"
AckData::AckData(){

}
AckData::AckData(AckType type_, string message_id){

	this->type_=type_;
	this->message_id=message_id;
}

bool AckData::setType(AckType t)
{
	type_ = t;
	return true;
}
bool AckData::setMessageID(string id)
{
	message_id=id;
	return true;
}
AckType AckData::getType()
{
	return type_;
}
string AckData::getMessageID()
{
	return message_id;
}

bool AckData::Flatten()
{
	flattened="";
	flattened+=to_string(type_);
	flattened+=seperator;
	flattened+=message_id;	
	return true;
}
bool AckData::unFlatten(string s)
{
	if(s=="")
	{
		perror("Data unavailable\n");
		return false;
	}
	stringstream ss(s);
	string tmp1,tmp2;
	ss>>tmp1>>tmp2;
	type_ = (AckType)stoi(tmp1);
	message_id = tmp2;
	
	return true;
}  
      
AckData::~AckData(){}
