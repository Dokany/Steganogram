#include "Message.h"
#include <stdint.h>
#include <cstdio> 
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <fstream>
#include <netinet/in.h>

using namespace std;

#ifndef PACKGEN_H
#define PACKGEN_H

class PackGen
{
	private:
		int max_size;
    public:
    	PackGen(int max_size);
    	vector<Message> fragment(Message m);
    	Message defragment(vector<Message> vm);
    	~PackGen();
};
#endif //MESSAGE_H
