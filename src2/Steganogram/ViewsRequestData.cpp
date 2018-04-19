
#include<string>
#include "ViewsRequestData.h"

ViewsRequestData::ViewsRequestData(){}
bool ViewsRequestData::setName(string name)
{
    this->name=name;
}

string ViewsRequestData::getName()
{
    return name;
}

bool ViewsRequestData::Flatten()
{

    flattened=name;
}

bool ViewsRequestData::unFlatten(string s)
{
    name=s;
}

ViewsRequestData::~ViewsRequestData(){};
