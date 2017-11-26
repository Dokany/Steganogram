#include "Peer.h"
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstring>
#include <sys/param.h>
#include <sys/utsname.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <cstdio>
#include <mutex>
#include <algorithm>
#include <chrono>
Peer::Peer(){}
Peer::Peer(char * _listen_hostname, int _listen_port, char* service_hostname, int service_port)
{
    this->udpSocket_server = new UDPSocket();
    this->udpSocket_client = new UDPSocket();
    this->username=username;

    myPort = _listen_port;
    myHostname = new char[strlen(_listen_hostname)+1];
    strcpy(myHostname,_listen_hostname);

    servicePort = service_port;
    serviceHostname = new char[strlen(service_hostname)+1];
    strcpy(serviceHostname,service_hostname);

    udpSocket_server->initializeServer(_listen_hostname, _listen_port);
    udpSocket_client->initializeClient();
    logged_in = false;
    waiting =true;
    listening = true;

    main_listen = std::thread(&Peer::listen,this);
    main_pinger = std::thread(&Peer::ping,this);

    sendMain();
    receiveMain();

    // main_receive = thread(&Peer::receiveMain,this);
    // main_send = thread(&Peer::sendMain,this);
    // receiving messages thread
    // thread t2 (sendMsg, ref(msg));
}
void Peer::logOff()
{
    //halt();
    logged_in=false;
}
/*
Peer::Peer(const Peer& other)
{
    udpSocket_client=other.udpSocket_client;
    udpSocket_server=other.udpSocket_server;

   // main_listen = other.main_listen;
  //  main_pinger = other.main_pinger;
  //  main_receive=other.main_receive;

    myPort = other.myPort;
    myHostname = other.myHostname;
    servicePort = other.servicePort;
    myPort = other.myPort;

    username = other.username;

    //mutex_1 = other.mutex_1;
    //mutex_2 = other.mutex_2;
    //mutex_3 = other.mutex_3;

   // cond = other.cond;
   // cond1 = other.cond1;
    //listening = other.listening;

   // processes_r = other.processes_r;
   // processes_s = other.processes_s;

    requests = other.requests;
    requests_process = other.requests_process;
    replies = other.replies;


    messageSentStatus = other.messageSentStatus;
    segmentTable = other.segmentTable;
    receivedMessageHistory = other.receivedMessageHistory;

    auth_id = other.auth_id;
    currentOnlineUsers = other.currentOnlineUsers;
    currentImageViewers = other.currentImageViewers;
    imageStatus = other.imageStatus;
    localImages = other.localImages;
    pendingImageOwners = other.pendingImageOwners;
}

Peer& Peer::operator=(const Peer& other)
{
    udpSocket_client=other.udpSocket_client;
    udpSocket_server=other.udpSocket_server;

   // main_listen = other.main_listen;
    //main_pinger = other.main_pinger;
   // main_receive=other.main_receive;

    myPort = other.myPort;
    myHostname = other.myHostname;
    servicePort = other.servicePort;
    myPort = other.myPort;

    username = other.username;

    //mutex_1 = other.mutex_1;
    //mutex_2 = other.mutex_2;
    //mutex_3 = other.mutex_3;

    //cond = other.cond;
    //cond1 = other.cond1;
   // listening = other.listening;

   // processes_r = other.processes_r;
    //processes_s = other.processes_s;

    requests = other.requests;
    requests_process = other.requests_process;
    replies = other.replies;


    messageSentStatus = other.messageSentStatus;
    segmentTable = other.segmentTable;
    receivedMessageHistory = other.receivedMessageHistory;

    auth_id = other.auth_id;
    currentOnlineUsers = other.currentOnlineUsers;
    currentImageViewers = other.currentImageViewers;
    imageStatus = other.imageStatus;
    localImages = other.localImages;
    pendingImageOwners = other.pendingImageOwners;
}
*/

std::set<string> Peer::getMyImages()
{
    return localImages;
}

std::set<string> Peer::getUserImages(string username)
{
    std::set<string> ret;
    Message req(ImageListRequest,string(myHostname),myPort, nameToAddress[username].first, nameToAddress[username].second);
    req.Flatten();
    execute(req);
    waiting =true;
    while(waiting);

    ret= currentImageListReply;
    currentImageListReply.clear();
    return ret;
}

void Peer::setLocalImages(std::set<string> arg)
{
    localImages=arg;
}

int Peer::login(string username, string password)
{
    Message m(Auth, string(myHostname), myPort, string(serviceHostname), servicePort);
    AuthData ad;
    cout<<username<<" "<<password<<endl;
    if(!ad.setUsername(username) ||!ad.setPassword(password))
    {
        perror("Username/password invalid\n");
        return false;
    }
    m.setData(ad);
    m.Flatten();
    waiting = true;
    cout<<"BEGIN EXECUTION\n";
    execute(m);
    this->username=username;
    cout<<"Waiting is "<<waiting<<endl;
    int i=0;
     std::this_thread::sleep_for(std::chrono::seconds(3));
//    while(true)
//    {
//        if(!waiting)break;
//        else if(i>10)break;
//        else
//        {

//            i++;
//        }
//    }
    cout<<"done waiting --------------------------:\n";
    if(waiting)return -1;
    else return logged_in;
}


void Peer::ping()
{
    while(listening)
    {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        if(logged_in)
        {

            cout<<"pinging\n";
            string myIP(myHostname);
            string targetIP(serviceHostname);
            Message ping(Ping, myIP, myPort, targetIP, servicePort);
            PingData pd(username);
            ping.setData(pd);
            ping.Flatten();

            char *hn = new char[targetIP.length() + 1];
            memcpy(hn, targetIP.c_str(),targetIP.length() + 1);
            sendWithoutWaiting(ping,servicePort, hn);
        }
    }
}

void Peer::execute(Message msg)
{
    // Mutex Thread Handling
    cout << "Message to be sent.\n";
    std::unique_lock<std::mutex> lck (mutex_1);
    requests.push(msg);
    cond.notify_one();		// release lock
}

void Peer::sendMain()
{
    for (int i = 0; i < 10; ++i)
    {
        processes_s.push_back(std:: thread([&](){
            while (true) {
                std::unique_lock<std::mutex> lck (mutex_1);
                if (!listening) return;
                cond.wait(lck);		// release lck and waits

                if (listening)
                {
                    Message msg = requests.front();
                    string idd = msg.getID()+msg.getOwnerIP()+to_string(time(NULL));

                    if(!logged_in){
                        cout<<"set AUTH ID\n";
                              auth_id = idd;
                    }
                    msg.setMessageID(idd);
                    msg.Flatten();
                    char *IP = new char[msg.getTargetIP().length() + 1];
                    memcpy(IP, msg.getTargetIP().c_str(),msg.getTargetIP().length()+1);
                    cout << std::this_thread::get_id() << "\t Sending message to IP: " << msg.getTargetIP() <<" : "<<msg.getTargetPort() << endl;
                    //cout << std::this_thread::get_id() << "\t Sending message from IP: " << myHostname <<" : "<<myPort << endl;
                    requests.pop();
                    lck.unlock();
                    sendHandler(msg, msg.getTargetPort(), IP, 75);

                    cout << "Message Sent Handled.\n";
                    //std::this_thread::sleep_for(std::chrono::seconds(10));
                            // release lck
                }
                else
                {
                    cout << "Worker thread no." << std::this_thread::get_id()<<" is done sending.\n";
                    return;
                }
            }
        }));
    }
}

void Peer::sendHandler(Message msg, int port, char *hostname, int timeout)
{
    //fragment, send all fragments (w/out wait)
    //while(messageSentStatus[message_id]!=sent &&timeout)
    // if messageSentStatus[message_id]== lost, resend all fragments
    //end while
    //0 sending, 1 sent, 2 resend
    PackGen pg(max_size);
    vector<Message> msgs= pg.fragment(msg);
    int ii=0;
    time_t start = time(NULL);
    time_t endwait = start + timeout;
    string msg_id = msg.getID();
    messageSentStatus[msg_id] = lost;
    while(start < endwait && messageSentStatus[msg_id]!=sent)
    {
        //
        if(messageSentStatus[msg_id]==lost)
        {
            cout<<" sending: "<< ii++<<endl;
            for(Message mm:msgs)
            {
                //mm.Flatten();
                cout<<"sending "<<mm.getSegNum()<<" / "<<mm.getSegTot()<<endl;
                string temp = mm.getFlattenedMessage();
                //cout<<"sendhandler: "<<temp<<endl;
                if(temp=="")cout<<"temp is empty\n";
                char *cstr = new char[temp.length() + 1];
                memcpy(cstr, temp.c_str(),temp.length()+1);
                cout<<"SENDTO LENGTH: "<<temp.length()+1<<endl;
                //std::replace(temp.begin(), temp.end(), '\0', ' ');
            /*	cout<<"KARIIIIIIIIIIIIIIIIIIIIIIIIIIM\n";
                for(int i=0;i<=temp.length();i++)
                {
                    cout<<cstr[i];
                }cout<<endl;*/
                udpSocket_client->writeToSocket(cstr, temp.length()+1, port, hostname);
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
            messageSentStatus[msg_id]=sending;
        }
        start = time(NULL);
    }
    cout << "Done waiting for ack.\n";
}

void Peer::halt()
{

    listening = false;

    //while (main_listen.joinable());

    main_listen.join();
    main_pinger.join();

    cond.notify_all();
    cond1.notify_all();

    for (std::thread& t : processes_s) t.join();

    for (std::thread& t : processes_r) t.join();

    //main_send.join();
    //main_receive.join();
}

void Peer::listen()
{
    while(listening) {
        getRequest();
    }

}

std::map<string,pair<string,int> > Peer::getStatus()
{
    return currentOnlineUsers;
}

bool Peer::getRequest()
{
    char msg1[max_size];
    int rr;
    //memset(msg1, 0, max_size);

    // Listening for messages on socket
    if((rr = udpSocket_server->readFromSocketWithNoBlock(msg1 , max_size) )> 0)
    {
        //Create message object


        Message msg;
        string recv="";
        recv=string(&msg1[0], &msg1[rr]);
        cout<<"RECV LENGHT "<<recv.length()<<endl;
        /*for(int i=0;i<=rr;i++)
        {
            recv+=msg1[i];
        }*/

        msg.unFlatten(recv);
        cout << "Message received "<<msg.getSegNum()<<" "<<msg.getSegTot()<<" ID: "<<msg.getID()<<endl;
        /*if(msg.getType()==MessageType(Terminate)){
            cout<<"Terminating getRequest\n";
            //halt();
            return false;
        }*/
        string unique_id = msg.getID();
        auto search = receivedMessageHistory.find(unique_id);

        if(search == receivedMessageHistory.end())
        {
            //Message doesn't exist, assign to new thread
            // Mutex Thread Handling

            cout << "Message not found in history\n";
            std::unique_lock<std::mutex> lck (mutex_2);
            receivedMessageHistory[unique_id] = false;
            messageSentStatus[unique_id] = sending;
            segmentTable[unique_id].push_back(msg);
            replies.push(unique_id);
            cond1.notify_one();		// notify that a new message is received
        }
        else if (!(search->second)) // if message is not complete
        {
            //messageSentStatus[msg.getID()] = sending;
            bool found=false;
            for(Message mm:segmentTable[unique_id])if(mm.getSegNum()==msg.getSegNum())found=true;
            if(!found)segmentTable[unique_id].push_back(msg);
            else cout<<"duplicate found\n";
        }
    }
    return true;
}

vector<pair<string,int> > Peer::getCurrentImageViewers(string name)
 {
     return currentImageViewers[name];
 }

void Peer::receiveMain()
{
    for (int i = 0; i < 10; ++i)
    {
        processes_r.push_back(std:: thread([&](){
            while (true) {
                std::unique_lock<std::mutex> lck2 (mutex_2);
                if (!listening) return;
                cond1.wait(lck2);		// release lck and waits

                if (listening)
                {
                    string msgID = replies.front();
                    cout << std::this_thread::get_id() << ": Recieving Message" << endl;
                    replies.pop();
                    //std::this_thread::sleep_for(std::chrono::seconds(10));
                    lck2.unlock();
                    receiveHandler(msgID, 25);
                            // release lck
                }
                else
                {
                    cout << "Worker Thread no." << std::this_thread::get_id()<<" is done recieving.\n";
                    return;
                }
            }
        }));
    }
}

void Peer::sendWithoutWaiting(Message m, int port, char *hostname)
{
    string idd = m.getID()+m.getOwnerIP()+to_string(time(NULL));
    m.setMessageID(idd);
    PackGen pg(max_size);

    vector<Message> v = pg.fragment(m);
    for(Message mm:v)
    {
        mm.Flatten();
        string temp = mm.getFlattenedMessage();
        char *msg = new char[temp.length() + 1];
        strcpy(msg, temp.c_str());
        udpSocket_client->writeToSocket(msg, temp.length() + 1, port, hostname);
    }
}

void Peer::receiveHandler(string message_id, int timeout)
{
    //make sure all segments are recevied within a timeout
    time_t start = time(NULL);
    time_t endwait = start + timeout;
    bool complete = false;
    int total = segmentTable[message_id].back().getSegTot();
    string targetIP =  segmentTable[message_id].back().getOwnerIP();
    int targetPort = segmentTable[message_id].back().getOwnerPort();

    while(start < endwait && !complete)
    {
        complete = total==segmentTable[message_id].size();
        start = time(NULL);
        //cout<<total<< " "<<segmentTable[message_id].size()<<endl;
    }
    //cout<<"I am out of the wait for all segments with total seg="<<segmentTable[message_id].size()<<endl;
    int myPort = segmentTable[message_id].back().getTargetPort();
    string myIP = segmentTable[message_id].back().getTargetIP();

    if(!complete)
    {
        //if not send a neg ack
        Message neg(NegAck, myIP,myPort,targetIP, targetPort);
        AckData nd(_NegAck, message_id);
        neg.setData(nd);
        neg.Flatten();
        char *hn = new char[targetIP.length() + 1];
        memcpy(hn, targetIP.c_str(),targetIP.length() + 1);
        sendWithoutWaiting(neg, targetPort,hn);

    }
    else
    {
        //else send an ack, defragment and handle



        //defragment
        PackGen pg(max_size);
        Message defraggedMessage = pg.defragment(segmentTable[message_id]);
        //defraggedMessage.Flatten();
        int size = defraggedMessage.getData().length();
        //cout<<"defraggedMessage data size: "<<size<<endl;
        //send ack
        MessageType mmt = defraggedMessage.getType();
        if(mmt!=Ack && mmt!=NegAck && mmt!=Terminate && mmt!=ImageRequest && mmt!=StatusReply && mmt!=ImageListRequest && mmt!=ViewsRequest)
        {

            Message ackMessage(Ack, myIP,myPort, targetIP, targetPort);
            AckData ad(_Ack, message_id);
            ackMessage.setData(ad);
            ackMessage.Flatten();
            char *hn = new char[targetIP.length() + 1];

            memcpy(hn, targetIP.c_str(),targetIP.length() + 1);
            sendWithoutWaiting(ackMessage, targetPort,hn);
        }


        //handle
        handleReceivedMessage(defraggedMessage, message_id);
    }
    cout<<"exiting receive handler\n";
}
void Peer::processReply()
{
    bool accept=mbox_bool;

    MessageType mt=mbox_mt;
    string name = mbox_image_name, id=mbox_id, ip=mbox_ip;
    int port=mbox_port;
    switch(mt)
    {
        case ImageRequest:
        {
            if(accept)
            {
                string path = "Images/"+name;

                ImageData id(name,path,5);

                Message reply(ImageReply, string(myHostname), myPort, ip,port);


                reply.setData(id);

                reply.Flatten();

                execute(reply);

            }
            else
            {
                Message neg(NegAck, myHostname,myPort, ip,port);
                AckData nd(_NegAck, id);
                neg.setData(nd);
                neg.Flatten();
                char *hn = new char[ip.length() + 1];
                memcpy(hn, ip.c_str(),ip.length() + 1);
                sendWithoutWaiting(neg, port,hn);
            }
            break;
        }
        case ImageListRequest:
        {
            if(accept)
            {
                Message reply(ImageListReply, string(myHostname), myPort, ip,port);
                ImageListData ild;
                for(std::set<string>::iterator it=localImages.begin();it!=localImages.end();++it)
                {
                    ild.addImage(*it);
                }
                reply.setData(ild);
                reply.Flatten();
                execute(reply);
            }
            else
            {
                Message reply(DenyRequest, string(myHostname), myPort, ip,port);
                reply.Flatten();
                execute(reply);
            }
            break;
        }
        case ViewsRequest:
        {
            if(accept)
            {
                ViewsReplyData id;
                id.setCount(5);
                id.setName(name);
                Message reply(ImageReply, string(myHostname), myPort, ip,port);
                reply.setData(id);
                reply.Flatten();
                execute(reply);
            }
            else
            {
                Message neg(NegAck, myHostname,myPort, ip,port);
                AckData nd(_NegAck, id);
                neg.setData(nd);
                neg.Flatten();
                char *hn = new char[ip.length() + 1];
                memcpy(hn, ip.c_str(),ip.length() + 1);
                sendWithoutWaiting(neg, port,hn);
            }
            break;
        }
    }
}

void Peer::handleReceivedMessage(Message m, string id)
{
    MessageType mt = m.getType();
    receivedMessageHistory[id]=true;
    string data=m.getData();
    switch(mt)
    {
        case Ack:
        {
            AckData ad;
            ad.unFlatten(data);
            messageSentStatus[ad.getMessageID()] = sent;

            if(ad.getMessageID() == auth_id)
            {
                cout<<"Log is successful\n";
                logged_in = true;

                waiting = false;
            }
            else if(pendingImageOwners.find(ad.getMessageID())!= pendingImageOwners.end())//he got the image
            {
                string name = currentOnlineUsers[m.getOwnerIP()].first;
                currentImageViewers[pendingImageOwners[ad.getMessageID()]].push_back(make_pair(name,5));
                pendingImageOwners.erase(ad.getMessageID());
            }
            cout<<"Ack Received of Message: "<< ad.getMessageID() << endl;
            break;
        }
        case NegAck:
        {
            AckData ad;
            ad.unFlatten(data);
            if(ad.getMessageID() == auth_id)
            {
                cout<<"Log is unsuccessful, retrying..\n";
                logged_in = false;
                waiting = false;
            }
            messageSentStatus[ad.getMessageID()]=lost;
            break;
        }
        case ImageReply:
        {
            if(!logged_in)return;
            ImageData id;
            id.unFlatten(data);
            ofstream out;
            string name=currentOnlineUsers[m.getOwnerIP()].first;
            name+='_';
            name+=id.getName();
            string path= "./Shared/"+name;
            out.open(path);
            string iim=id.getImage();

            cout<<" IMAGE IN PEER AFTER ALL IS: "<<iim.length()<<endl;
            out<<iim;
            out.close();
            id.setPath(path);
            id.embeddInDefault();

            int count = id.getCount();
            imageStatus[name]=count;
            cout << " COUNT ======= "<<endl;
            break;

        }
        case StatusReply:
        {

//            if(!logged_in)return;
            StatusData sd;
            sd.unFlatten(data);
            cout<<"Received online users: \n";
            vector<pair<string,pair<string, int> > > list = sd.getOnlineUsers();
            currentOnlineUsers.clear();
            nameToAddress.clear();
            for(pair<string,pair<string, int> > t:list)
            {
                string name = t.first;
                string address = t.second.first;
                int port = t.second.second;
                cout<<name<<" "<<address<<" "<<port<<endl;
                currentOnlineUsers[address].first = name;
                currentOnlineUsers[address].second = port;
                nameToAddress[name].first=address;
                nameToAddress[name].second = port;
            }
            cout<<endl;
            break;

        }
        case ImageListReply:
        {
            if(!logged_in)return;
            ImageListData ild;
            ild.unFlatten(data);
            cout<<"Received Image List: \n";
            vector<string> list = ild.getImageList();
            for(string t:list)
            {
                currentImageListReply.insert(t);
            }

            waiting=false;
            break;

        }
       // TO BE IMPLEMENTED AFTER STEGANOGRAPHY
         case ImageListRequest:
         {

            //POP UP WINDOW

             string user = currentOnlineUsers[m.getOwnerIP()].first;
            string request = "User "+user+" has requested access to you image list, do you accept?\n";
            string title = "Image List Request Received";


            mbox_request = request;
            mbox_title = title;
            mbox_mt=mt;
            mbox_id=id;
            mbox_port=m.getOwnerPort();
            mbox_ip=m.getOwnerIP();
            emit firstWindow();

            break;
         }

         case ImageRequest:
         {
            ImageRequestData rd;
            rd.unFlatten(data);
            string name=rd.getImageName();
            string user = currentOnlineUsers[m.getOwnerIP()].first;

            char c;
            ifstream in;


            //POP UP
            string request = "User "+user+" has requested access to "+name+ ", do you accept?\n";
            string title = "Image Request Received";
            mbox_image_name=name;
            mbox_request = request;
            mbox_title = title;
            mbox_mt=mt;
            mbox_id=id;
            mbox_port=m.getOwnerPort();
            mbox_ip=m.getOwnerIP();
            emit firstWindow();
            sendImage(name,mbox_ip,mbox_port,5);
            cout<<"EMITED\n";

            break;
         }
         case ViewsRequest:
         {
            ViewsRequestData rd;
            rd.unFlatten(data);
            string name=rd.getName();
            string user = currentOnlineUsers[m.getOwnerIP()].first;
            string request = "User "+user+" has requested more views for "+name+ ", do you accept?\n";
            string title = "Image Request Received";
            mbox_request = request;
            mbox_title = title;
              mbox_mt=mt;
              mbox_image_name=name;
              mbox_id=id;
              mbox_port=m.getOwnerPort();
              mbox_ip=m.getOwnerIP();
            emit firstWindow();

         }
    case DenyRequest:
        {
            //POP UP WINDOW DENIED!
            waiting=false;
           cout<<"User "<<currentOnlineUsers[m.getOwnerIP()].first<<" has denied your request \n";

           break;
        }
//         case ViewsReply:
//         {
//            break;
//         }

        //to be added to Service and removed from here
        /*
        SENT FROM USER TO SERVICE
        case StatusRequest:
        case Auth:
        case Ping:

        */
        case Terminate:
        {
            logged_in=false;
            cout<<"before terminate emit\n";
            emit terminateProgram();

            break;
        }
        default:
        {
            if(!logged_in)return;
            perror("Unknown type received\n");
            break;
        }
    }
}
string Peer::getMBoxTitle()
{
    return mbox_title;
}

string Peer::getMBoxRequest()
{
    return mbox_request;
}
void Peer::setMBoxBool(bool b)
{
    mbox_bool=b;
}

void Peer::requestViews(string name, string user)
{
   string targetIP = nameToAddress[user].first;
   int targetPort = nameToAddress[user].second;
   Message msg(ViewsReply,string(myHostname), myPort, targetIP, targetPort);
   ViewsRequestData vrd;
   vrd.setName(name);
   msg.setData(vrd);
   msg.Flatten();
   execute(msg);
}
void Peer::addViews(int count, string image, string user)
{
    string path = user +'_'+ image;
    ImageData id(image, ".Shared/"+path, count);
     imageStatus[path]=count;
}
int Peer::checkImage(string name, string ip)
{
    string img_name = currentOnlineUsers[ip].first+'_'+name;
    if(imageStatus.find(img_name)==imageStatus.end())return -1;
    else
        return imageStatus[img_name];
}

void Peer::addImage(string name, string path)
{
    string new_path = "Images/"+name;
    ifstream in;
    ofstream of;
    in.open(path);
    string data="";
    char c;
    while(in.get(c))
        data+=c;
    of.open(new_path);
    of<<data;

    in.close();
    of.close();

    localImages.insert(name);


}

void Peer::sendImage(string name, string IP, int port,int count)
{
    ImageData id(name,"Images/",count);
    Message tst(ImageReply, string(myHostname), myPort, IP, port);
    tst.setData(id);
    tst.Flatten();
    execute(tst);
    string m_id = tst.getID()+tst.getOwnerIP();
    pendingImageOwners[m_id]=name;
}

void Peer::requestImage(string name, string user)
{
    string targetIP = nameToAddress[user].first;
    int targetPort = nameToAddress[user].second;
    Message msg(ImageRequest,string(myHostname), myPort, targetIP, targetPort);
    ImageRequestData ird;
    ird.setImageName(name);
    msg.setData(ird);
    msg.Flatten();
    execute(msg);

}

Peer::~Peer(){

    std::map<string,int>::iterator it;
    for(it=imageStatus.begin();it!=imageStatus.end();++it)
    {
        ImageData id;
        string temp=it->first;
        temp.erase(0,8);
        id.setName(temp);
        id.setPath(it->first);
        id.setCount(it->second);
    }
}
