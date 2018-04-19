
#include "Data.h"
using namespace std;
#ifndef VIEWSREQUESTDATA_H
#define VIEWSREQUESTDATA_H
class ViewsRequestData : public Data
{
    private:
        string name;
    public:
        ViewsRequestData();
        bool setName(string name);
        string getName();
        bool Flatten();
        bool unFlatten(string s);
        ~ViewsRequestData();
};
#endif // VIEWSREQUESTDATA_H
