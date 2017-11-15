#include "Message.h"
#include<cstring>
#include<iostream>
int Message::all_ID = 0;
Message::Message()
{

}

Message::Message(MessageType type, string IP, int Port)
{
	messageID = all_ID++;
	ownerPort = Port;
	if(IP.find(' ')!=-1)perror("IP error\n");
	ownerIP = IP;
	this->type = type;
	seg_num = seg_tot = 1;
	data="";
}

Message::Message(const Message& other)
{
	messageID = other.messageID;
	seg_num = other.seg_num;
	seg_tot = other.seg_tot;
	size = other.size;
	ownerPort = other.ownerPort;
	type = other.type;
	data = other.data;
	ownerIP = other.ownerIP;
	flattened = other.flattened;

}

Message& Message::operator=(const Message& other)
{
	messageID = other.messageID;
	seg_num = other.seg_num;
	seg_tot = other.seg_tot;
	size = other.size;
	ownerPort = other.ownerPort;
	type = other.type;
	data = other.data;
	ownerIP = other.ownerIP;
	flattened = other.flattened;

}
int Message::getID()
{
	return messageID;
}

MessageType Message::getType()
{
	return type;
}

void Message::setType(MessageType mt)
{
	type = mt;
}
bool Message::setImageData(string path)
{
	if(type!=ImageReply)
	{
		perror("This is not an Image Message\n");
		return false;
	}
	int cnt = 0;
	ifstream in;
	in.open(path);
	if(!in){
		perror("Error opening file\n");
		return false;
	}
	char c;
	string s="";
	while(in.get(c))
	{
		cnt++;
		s+=c;
	}
	size = cnt;
	data=s;
	return true;
}
bool Message::setTextData(Data &d)
{
	
	data="";
	switch(type)
	{
		case Auth:
		{
			AuthData &ad = dynamic_cast<AuthData&>(d);
			ad.Flatten();
			data = ad.getFlattenedData();
			break;
		}
		case StatusReply:
		{
			StatusData &sd = dynamic_cast<StatusData&>(d);
			sd.Flatten();
			data = sd.getFlattenedData();
			break;
		}	
		case ImageRequest:
		{
			ImageRequestData &ird = dynamic_cast<ImageRequestData&>(d);
			ird.Flatten();
			data = ird.getFlattenedData();
			break;
		}
		case ImageListReply:
		{
			ImageListData &ild = dynamic_cast<ImageListData&>(d);
			ild.Flatten();
			data = ild.getFlattenedData();
			break;
		}
		default:
		{
			perror("No Data Needed\n");
			return false;
		}
	}
	size=data.length();
	return true;
}
void Message::setFlattenedData(string s)
{
	data=s;
	//unFlatten(s);
}

void Message::setDataSize(int i)
{
	size = i;
}
string Message::getData()
{
	return data;
}

void Message::setSeg(int total, int current)
{
	seg_num=current;
	seg_tot=total;
}
int Message::getSegNum()
{
	return seg_num;
}
int Message::getSegTot()
{
	return seg_tot;
}
int Message::getOwnerPort()
{
	return ownerPort;
}
string Message::getOwnerIP()
{
	return ownerIP;
}
int Message::getDataSize()
{
	return size;
}
bool Message::Flatten()
{

    flattened = "";
    flattened+=to_string(messageID);
    flattened+=seperator;
    flattened+=to_string(seg_num);
    flattened+=seperator;
    flattened+=to_string(seg_tot);
    flattened+=seperator;
    flattened+=to_string(size);
    flattened+=seperator;
    flattened+=to_string(ownerPort);
    flattened+=seperator;
    if(ownerIP.find(seperator)!=-1)
    {
    	perror("IP Error\n");
    	return false;
    }
    flattened+=ownerIP;
    flattened+=seperator;
    flattened+=to_string((int)type);
    flattened+=seperator;
    flattened+=data;

    return true;
}
bool Message::unFlatten(string s)
{
	if(s=="")
	{
		perror("Nothing is there to be unflattened\n");
		return false;
	}
	stringstream ss(s);
	cout<<"UNFLATTENING: "<<s.substr(0,10)<<endl;
	string tmp;
	ss>>tmp;
	messageID=stoi(tmp);	
	ss>>tmp;
	seg_num=stoi(tmp);
	ss>>tmp;
	seg_tot=stoi(tmp);
	ss>>tmp;
	size=stoi(tmp);
	ss>>tmp;
	ownerPort=stoi(tmp);
	ss>>ownerIP;
	ss>>tmp;
	type=(MessageType)stoi(tmp);
	getline(ss,tmp);
	if(tmp.length()>0)
	{
		tmp.erase(0,1);
	}
	data = tmp;
	data+='\n';
	while(getline(ss,tmp))
	{
		data+=tmp;

	data+='\n';
	}
	

}
string Message::getFlattenedMessage()
{
	return flattened;
}

void Message::setMessageID(int num)
{
	messageID=num;
}
void Message::setPort(int num)
{
	ownerPort=num;
}
void Message::setIP(string s)
{
	if(s.find(' ')!=-1){
		perror("IP error\n");
		return;
	}
	ownerIP=s;
}

void Message::printMessageDetails()
{
	cout<<"Message ID: "<<messageID<<endl;
	cout<<"Segment "<<seg_num<<"/"<<seg_tot<<endl;
	cout<<"Owner IP: "<<ownerIP<<endl;
	cout<<"Owner Port: "<<ownerPort<<endl;
	cout<<"Data Size: "<<size<<endl;
	cout<<"Message Type: "<<type<<endl;
}

Message::~Message()
{
}