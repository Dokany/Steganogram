#include<stdint.h>
#include<cstdio> 
#include<string>
#include<sstream>
#include<map>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

using namespace std;
#ifndef DATA_H
#define DATA_H
class Data
{
    protected:
        string flattened;
        const char seperator=' ';
    public:
    	Data();        
        string getFlattenedData();
        virtual bool Flatten()=0;
        virtual bool unFlatten(string s)=0;        
        ~Data();
};
#endif //MESSAGE_H
