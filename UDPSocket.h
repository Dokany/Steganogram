#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <unistd.h>
#include <stdint.h>
#include <cstdio> 
#include <string>
#include <netdb.h>
#include <ctime>
#include <netinet/in.h>

#ifndef UDPSOCKET_H
#define UDPSOCKET_H

class UDPSocket
{
    protected:
        const size_t MAX_SIZE_MSG = 2048;
        int sock;
        socklen_t aLength;
        struct sockaddr_in myAddr;

    public:

        UDPSocket ();
        
        bool initializeServer (char * hostname, int _myPort);
        bool initializeClient ();

        int writeToSocket (char * buffer,  int maxBytes, int server_port, char *hostname);
        int writeToSocketAndWait (char * buffer,  int maxBytes, int server_port, char *hostname, int sec, char *ack);

        void makeLocalSA( char * hostname, int port);
        void makeDestSA(struct sockaddr_in *peerAddr, char *hostname, int port);

        int readFromSocketWithNoBlock (char * buffer, int  maxBytes);      
        int getMyPort ();        

        ~UDPSocket ( );
};
#endif // UDPSOCKET_H
