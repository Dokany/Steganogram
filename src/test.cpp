#include<iostream>
#include<string>
#include<fstream>
#include "PackGen.h"
#include "Data.h"

using namespace std;

int main()
{

	Message tst(ImageReply, "192.168.1.5", 9999,"192.168.1.5", 9999);
	
	ImageData id("dog_b.jpg","dog_b.jpg");
	id.Flatten();
	tst.setData(id);
	tst.Flatten();
	tst.printMessageDetails();
	PackGen pg(50000),pg2(50000);
	vector<Message> msgs = pg.fragment(tst);

	//for(Message mm:msgs)mm.printMessageDetails();

	Message res = pg2.defragment(msgs);
	res.printMessageDetails();
	ofstream out;
	out.open("dogg.jpg");
	//string ff=res.getFlattenedMessage();
	//Message tst2;
	//tst2.unFlatten(ff);
	ImageData id2;
	id2.unFlatten(res.getData());
	// stringstream ss(soura);
	// string name,tmp,data;
	// ss>>name;
	// soura="";
	// getline(ss,tmp);
	// if(tmp.length()>0)
	// {
	// 	tmp.erase(0,1);
	// }
	// data = tmp;
	// data+='\n';
	// while(getline(ss,tmp))
	// {
	// 	data+=tmp;

	// data+='\n';
	// }
	out<<id2.getImage();

	return 0;
}