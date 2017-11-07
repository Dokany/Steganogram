#include "UDPSocket.h"
#include <cstring>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <ctime>
#include <iostream>
#include <stddef.h>
#include <stdio.h>

using namespace std;

UDPSocket::UDPSocket (){}


bool UDPSocket::initializeServer (char * hostname, int _myPort)
{
    if((this->sock = socket(AF_INET, SOCK_DGRAM, 0))<0)
    {
        perror("socket  failed");
        return false;
    }
    makeLocalSA( hostname, _myPort);

    if( bind(this->sock, (struct sockaddr *)&myAddr, sizeof(struct sockaddr_in))!= 0)
    {
        perror("Bind  failed\n");
        close(this->sock);
        return false;
    }
    aLength = sizeof(myAddr);
    this->myAddr.sin_family = AF_INET; /* note that this is needed */
}

bool UDPSocket::initializeClient ()
{
    if((this->sock = socket(AF_INET, SOCK_DGRAM, 0))<0) 
    {
        perror("socket  failed");
        return false;
    }
    makeLocalSA(nullptr, 0);

    if( bind(sock, (struct sockaddr *)&myAddr, sizeof(struct sockaddr_in))!= 0)
    {
        perror("Bind  failed\n");
        close (sock);
        return false;
    }   
}

int UDPSocket::getMyPort ()
{
    struct sockaddr_in sin;
    socklen_t len = sizeof(sin);

    if (getsockname(sock, (struct sockaddr *)&sin, &len) == -1)
        perror("getsockname");

    return ntohs(sin.sin_port);
}

void UDPSocket::makeLocalSA( char * hostname, int port)
{
    struct hostent *host;
    
    this->myAddr.sin_family  =  AF_INET;
    this->myAddr.sin_port = htons(port);
    this->myAddr.sin_addr.s_addr = htonl(INADDR_ANY);
}

void UDPSocket::makeDestSA(struct sockaddr_in *peerAddr, char *hostname, int port)
{   
    struct hostent *host;
    peerAddr->sin_family = AF_INET;

    if((host = gethostbyname(hostname)) == NULL)
    {
        printf("Unknown host name\n");
        exit(-1);
    }

    peerAddr->sin_addr = *(struct in_addr *) (host->h_addr);
    peerAddr->sin_port = htons(port);
}

//send without waiting for an ack
int UDPSocket::writeToSocket (char * buffer,  int maxBytes, int server_port, char *hostname)
{
    struct sockaddr_in peerAddr;

    makeDestSA(&peerAddr, hostname, server_port);

    return sendto(sock, buffer, 2048, 0, (struct sockaddr *)&peerAddr, sizeof(peerAddr));
}


//waits for an ack
int UDPSocket::writeToSocketAndWait (char * buffer,  int maxBytes, int server_port, char *hostname, int sec, char *ack)
{
    char ack1[2048];
	memset(ack1, '\0', 2048);
    time_t start = time(NULL);
    time_t endwait = start + sec;
    int sent=-1,rec=-1;
    while (start < endwait)
    {   
        if(sent < 0)
        {
                 sent = writeToSocket(buffer,maxBytes, server_port, hostname);
                
                if (sent >= 0) 
                {
                    rec = readFromSocketWithNoBlock(ack1, maxBytes);
                    if(rec >= 0) 
                        break;
                }
                 
        }
        else
        {
            //wait for ack
            rec = readFromSocketWithNoBlock(ack1, maxBytes);
            if(rec >= 0) 
                break;
        }
        start = time(NULL);
    }
    printf("Server echoed reply recieved: %s\n\nMessage sent successfully to server.\n", ack1);
    return sent;
}

int UDPSocket::readFromSocketWithNoBlock (char message1[2048], int  maxBytes)
{
    std::lock_guard<std::mutex> lock_m(m);
	memset(message1, '\0', 2048);

    int ret = recvfrom(sock, message1, maxBytes, 0, (struct sockaddr *)&myAddr, &aLength);

    cout << "Message Recieved: ";

printf("%s\n", message1);

    return ret;
}


UDPSocket::~UDPSocket() {}
