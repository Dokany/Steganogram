#include "ImageData.h"
ImageData::ImageData()
{}
ImageData::ImageData(string name, string path)
{
	this->name=name;
	if(name.find(seperator)!=-1)
	{
		perror("Invalid file name\n");
	}
	ifstream in;
	in.open(path);
	if(!in){
		perror("Error opening file\n");
	}
	else
	{
		char c;
		image="";
		while(in.get(c))
		{
			image+=c;
		}
		in.close();
	}
}

bool ImageData::setName(string name)
{
	if(name.find(seperator)!=-1)
	{
		perror("Invalid file name\n");
		return false;
	}
	this->name=name;
	return true;
}
bool ImageData::setImage(string path)
{
	ifstream in;
	in.open(path);
	if(!in){
		perror("Error opening file\n");
		return false;
	}
	else
	{
		char c;
		image="";
		while(in.get(c))
		{
			image+=c;
		}
		in.close();
		return true;
	}
}
string ImageData::getImage()
{
	return image;
}
string ImageData::getName()
{
	return name;
}

bool ImageData::Flatten()
{
	flattened="";
	flattened+=name;
	flattened+=seperator;
	flattened+=image;
	return true;
}
bool ImageData::unFlatten(string s)
{
	if(s=="")
	{
		perror("Nothing to unFlatten\n");
		return false;
	}
	stringstream ss(s);
	string tmp;
	ss>>name;
	getline(ss,tmp);
	if(tmp.length()>0)
	{
		tmp.erase(0,1);
	}
	image = tmp;
	image +='\n';
	while(getline(ss,tmp))
	{
		image+=tmp;
		image+='\n';
	}
	return true;
} 

ImageData::~ImageData(){}