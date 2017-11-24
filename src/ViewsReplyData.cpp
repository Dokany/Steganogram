
#include<string>
#include<sstream>
#include "ViewsReplyData.h"

ViewsReplyData::ViewsReplyData(){}
bool ViewsReplyData::setCount(int count)
{
    this->count=count;
}
bool ViewsReplyData::setName(string name)
{
    this->name=name;
}

string ViewsReplyData::getName()
{
    return name;
}

int ViewsReplyData::getCount()
{
    return count;
}

bool ViewsReplyData::Flatten()
{
    flattened=to_string(count);
    flattened+=seperator;
    flattened+=name;
}

bool ViewsReplyData::unFlatten(string s)
{
    stringstream ss(s);
    string tmp;
    ss>>tmp;
    count=stoi(tmp);
    ss>>name;
}
ViewsReplyData::~ViewsReplyData(){}
