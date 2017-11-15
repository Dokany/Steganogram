#include<iostream>
#include<string>
#include<fstream>
#include "PackGen.h"
#include "Data.h"

using namespace std;

int main()
{

	Message tst(ImageReply, "192.168.1.5", 9999);
	tst.setImageData("dog_b.jpg");
	tst.Flatten();
	tst.printMessageDetails();
	PackGen pg(50000);
	vector<Message> msgs = pg.fragment(tst);
	//for(Message mm:msgs)mm.printMessageDetails();

	Message res = pg.defragment(msgs);
	res.printMessageDetails();
	ofstream out;
	out.open("dogg.jpg");
	//string ff=res.getFlattenedMessage();
	//Message tst2;
	//tst2.unFlatten(ff);
	string soura = res.getData();
	out<<soura;


	return 0;
}