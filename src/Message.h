#include<stdint.h>
#include<cstdio> 
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

using namespace std;
#ifndef MESSAGE_H
#define MESSAGE_H
enum MessageType { Request, Reply};
class Message
{
    private:
        MessageType message_type;
        void * message;
        size_t message_size;
        static int message_count;
        int message_id;
        struct sockaddr_in sender;

    public:

        Message(void * p_message, size_t p_message_size, struct sockaddr_in sender, MessageType type);

        struct sockaddr_in getSenderAddress();
        int getMessageID ();

        void * getMessage();
        size_t getMessageSize();
        MessageType getMessageType();

        void setMessage (void *message,  size_t message_size);
        void setMessageType (MessageType message_type);
        ~Message();
};
#endif //MESSAGE_H
