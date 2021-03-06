#include "Message.h"
#include<cstring>
#include<iostream>
int Message::all_ID = 0;
Message::Message()
{

}

Message::Message(MessageType type, string IP, int Port, string targetIP, int targetPort)
{
	messageID = to_string(all_ID++);
	ownerPort = Port;
	this->targetPort = targetPort;
	if(IP.find(' ')!=-1 || targetIP.find(' ')!=-1 )perror("IP error\n");
	ownerIP = IP;
	this->targetIP = targetIP;
	this->type = type;
	seg_num = seg_tot = 1;
	data="";
	size=0;
}

Message::Message(const Message& other)
{
	messageID = other.messageID;
	seg_num = other.seg_num;
	seg_tot = other.seg_tot;
	size = other.size;
	ownerPort = other.ownerPort;
	targetPort = other.targetPort;
	type = other.type;
	data = other.data;
	ownerIP = other.ownerIP;
	targetIP = other.targetIP;
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
	targetIP = other.targetIP;
	ownerIP = other.ownerIP;
	flattened = other.flattened;

}
string Message::getID()
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
// bool Message::setImageData(string path)
// {
// 	if(type!=ImageReply)
// 	{
// 		perror("This is not an Image Message\n");
// 		return false;
// 	}
// 	int cnt = 0;
// 	ifstream in;
// 	in.open(path);
// 	if(!in){
// 		perror("Error opening file\n");
// 		return false;
// 	}
// 	char c;
// 	string s="";
// 	while(in.get(c))
// 	{
// 		cnt++;
// 		s+=c;
// 	}
// 	size = cnt;
// 	data=s;
// 	return true;
// }
bool Message::setData(Data &d)
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
		case Ack:
		{
			AckData &ad = dynamic_cast<AckData&>(d);
			ad.Flatten();
			data = ad.getFlattenedData();
			break;
		}
		case NegAck:
		{
			AckData &ad = dynamic_cast<AckData&>(d);
			ad.Flatten();
			data = ad.getFlattenedData();
			break;
		}
		case ImageReply:
		{
			ImageData &id = dynamic_cast<ImageData&>(d);
			id.Flatten();
			data = id.getFlattenedData();
			break;
		}
		case Ping:
		{
			PingData &pd = dynamic_cast<PingData&>(d);
			pd.Flatten();
			data = pd.getFlattenedData();
			break;
		}
        case ViewsRequest:
        {
                ViewsRequestData &pd = dynamic_cast<ViewsRequestData&>(d);
                pd.Flatten();
                data = pd.getFlattenedData();
                break;
        }
        case ViewsReply:
        {
           ImageData &pd = dynamic_cast< ImageData&>(d);
            pd.Flatten();
             data = pd.getFlattenedData();
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

int Message::getTargetPort()
{
	return targetPort;
}
string Message::getTargetIP()
{
	return targetIP;
}

int Message::getDataSize()
{
	return size;
}
int Message::getTotalSize()
{
	return flattened.length();
}
bool Message::Flatten()
{

    flattened = "";
    flattened+=messageID;
    flattened+=seperator;
    flattened+=to_string(seg_num);
    flattened+=seperator;
    flattened+=to_string(seg_tot);
    flattened+=seperator;
    flattened+=to_string(size);
    flattened+=seperator;
    flattened+=to_string(ownerPort);
    flattened+=seperator;
    flattened+=to_string(targetPort);
    flattened+=seperator;
    if(ownerIP.find(seperator)!=-1)
    {
    	perror("Owner IP Error\n");
    	return false;
    }
    flattened+=ownerIP;

    flattened+=seperator;
    if(targetIP.find(seperator)!=-1)
    {
    	perror("Target IP Error\n");
    	return false;
    }
    flattened+=targetIP;
    flattened+=seperator;
    flattened+=to_string((int)type);
    flattened+=seperator;
   // cout<<"data when flatteneing: "<<data<<endl;
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
	string tmp;
	ss>>messageID;	
	ss>>tmp;
	seg_num=stoi(tmp);
	ss>>tmp;
	seg_tot=stoi(tmp);
	ss>>tmp;
	size=stoi(tmp);
	ss>>tmp;
	ownerPort=stoi(tmp);	
	ss>>tmp;
	targetPort=stoi(tmp);
	ss>>ownerIP;
	ss>>targetIP;
	ss>>tmp;
	type=(MessageType)stoi(tmp);
	data="";
	char c;

	while(ss.get(c))
	{
		data+=c;
	}
	if(data.length()>0)data.erase(0,1);
	

}
string Message::getFlattenedMessage()
{
	return flattened;
}

void Message::setMessageID(string num)
{
	messageID=num;
}
void Message::setOwnerPort(int num)
{
	ownerPort=num;
}
void Message::setOwnerIP(string s)
{
	if(s.find(' ')!=-1){
		perror("IP error\n");
		return;
	}
	ownerIP=s;
}

void Message::setTargetPort(int num)
{
	targetPort=num;
}
void Message::setTargetIP(string s)
{
	if(s.find(' ')!=-1){
		perror("IP error\n");
		return;
	}
	targetIP=s;
}

void Message::printMessageDetails()
{
	cout<<"Message ID: "<<messageID<<endl;
	cout<<"Segment "<<seg_num<<"/"<<seg_tot<<endl;
	cout<<"Owner IP: "<<ownerIP<<endl;
	cout<<"Owner Port: "<<ownerPort<<endl;	
	cout<<"Target IP: "<<targetIP<<endl;
	cout<<"Target Port: "<<targetPort<<endl;
	cout<<"Data Size: "<<size<<endl;
	cout<<"Message Type: "<<type<<endl;
}

Message::~Message()
{
}
