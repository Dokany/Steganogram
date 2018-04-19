#include "Data.h"
using namespace std;
#ifndef VIEWSREPLYDATA_H
#define VIEWSREPLYDATA_H
class ViewsReplyData : public Data
{
    private:
        int count;
        string name;
    public:
        ViewsReplyData();
        bool setCount(int);
        int getCount();
        bool setName(string name);
        string getName();
        bool Flatten();
        bool unFlatten(string s);
        ~ViewsReplyData();
};
#endif //MESSAGE_H
