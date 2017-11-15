
#include "ImageListData.h"

ImageListData::ImageListData()
{}
bool ImageListData::addImage(string s)
{
	if(s.find(seperator)!=-1)
	{
		perror("restriced character used\n");
		return false;
	}
	imageList.push_back(s);
	return true;
}
vector<string> ImageListData::getImageList()
{
	return imageList;
}
bool ImageListData::Flatten()
{
	if(imageList.size()==0)
	{
		perror("Data not ready to be flattened\n");
		return false;
	}
	flattened="";
	for(string p:imageList)
	{
		flattened+=p;
		flattened+=seperator;
	}
	return true;
}
bool ImageListData::unFlatten()
{
	imageList.clear();
	stringstream ss(flattened);
	string img;
	while(ss>>img)
	{
		imageList.push_back(img);
	}
	return true;
}       
ImageListData::~ImageListData(){}
