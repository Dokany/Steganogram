#include "Data.h"
#include <ctime>
using namespace std;
#ifndef PINGDATA_H
#define PINGDATA_H
class PingData : public Data
{
    private:
        string username;
    public:
        PingData();
    	PingData(string username);

    	bool setUsername(string user);
    	string getUsername();
    	
        bool Flatten();
        bool unFlatten(string s);  
              
        ~PingData();
};
#endif //MESSAGE_H
