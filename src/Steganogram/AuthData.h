#include "Data.h"
using namespace std;
#ifndef AUTHDATA_H
#define AUTHDATA_H
class AuthData : public Data
{
    private:
        string username, password;
    public:
    	AuthData();
    	bool setUsername(string s);
    	bool setPassword(string s);
    	string getUsername();
    	string getPassword();
        bool Flatten();
        bool unFlatten(string s);        
        ~AuthData();
};
#endif //MESSAGE_H
