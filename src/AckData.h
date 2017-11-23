#include "Data.h"
using namespace std;
#ifndef ACKDATA_H
#define ACKDATA_H
enum AckType{_Ack, _NegAck};
class AckData : public Data
{
    private:
        AckType type_;
        string message_id;
    public:
        AckData();
    	AckData(AckType type, string message_id);

    	bool setType(AckType t);
    	bool setMessageID(string id);
    	AckType getType();
    	string getMessageID();
    	
        bool Flatten();
        bool unFlatten(string s);  
              
        ~AckData();
};
#endif //MESSAGE_H
