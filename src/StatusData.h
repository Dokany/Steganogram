#include "Data.h"
#include <vector>
#include <string>
using namespace std;
#ifndef STATUSDATA_H
#define STATUSDATA_H
class StatusData : public Data
{
    private:
        vector<pair<string,pair<string, int> > > onlineUsers;
    public:
    	StatusData();
    	bool addUser(string name, string address, int port);
    	 vector<pair<string,pair<string, int> > > getOnlineUsers();
        bool Flatten();
        bool unFlatten(string s);        
        ~StatusData();
};
#endif //MESSAGE_H