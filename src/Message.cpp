#include "Message.h"

using namespace std;

Message::Message(void * p_message, size_t p_message_size, struct sockaddr_in sender, MessageType type)
{
	this->message = p_message;
	this->message_size = p_message_size;
	this->sender = sender;
	this->message_type = type;
	this->message_id = ++this->message_count;
}

sockaddr_in Message::getSenderAddress()
{
	return sender;
}
int Message::getMessageID () 
{
	return message_id;
}

void * Message::getMessage() 
{
	return message;
}
size_t Message::getMessageSize()
{
	return message_size;
}
MessageType Message::getMessageType()
{
	return message_type;
}

void Message::setMessage (void *message,  size_t message_size)
{
	this->message = message;
	this->message_size = message_size;
}
void Message::setMessageType (MessageType message_type)
{
	this->message_type = message_type;
}
Message::~Message(){}

int Message::message_count = 0;
