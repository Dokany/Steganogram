#include "Data.h"
using namespace std;
#ifndef ACKDATA_H
#define ACKDATA_H
enum AckType{_Ack, _NegAck};
class AckData : public Data
{
    private:
        AckType type_;
        int message_id;
    public:
        AckData();
    	AckData(AckType type, int message_id);

    	bool setType(AckType t);
    	bool setMessageID(int id);
    	AckType getType();
    	int getMessageID();
    	
        bool Flatten();
        bool unFlatten(string s);  
              
        ~AckData();
};
#endif //MESSAGE_H
