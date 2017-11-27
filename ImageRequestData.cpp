#include "ImageRequestData.h"

ImageRequestData::ImageRequestData(){
	imageName="";
}
bool ImageRequestData::setImageName(string s)
{
	if(s.find(seperator)!=-1)
	{
		perror("restriced character used\n");
		return false;
	}
	imageName=s;
	return true;
}
string ImageRequestData::getImageName()
{
	return imageName;
}
bool ImageRequestData::Flatten()
{
	if(imageName=="")
	{
		perror("Data not ready to be flattened\n");
		return false;
	}
	flattened="";
	flattened+=imageName;	
	return true;
}
bool ImageRequestData::unFlatten()
{
	if(flattened=="")
	{
		perror("Data unavailable\n");
		return false;
	}
	stringstream s(flattened);
	s>>imageName;
	return true;
}       
ImageRequestData::~ImageRequestData(){}