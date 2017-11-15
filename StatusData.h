#include "Data.h"
#include <vector>
#include <string>
using namespace std;
#ifndef STATUSDATA_H
#define STATUSDATA_H
class StatusData : public Data
{
    private:
        vector<pair<string,string> > onlineUsers;
    public:
    	StatusData();
    	bool addUser(string name, string address);
    	vector<pair<string,string> > getOnlineUsers();
        bool Flatten();
        bool unFlatten();        
        ~StatusData();
};
#endif //MESSAGE_H