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
	
	tst.setData(id);
	tst.Flatten();
	// string first=tst.getData();
	// cout<<first.substr(49950,100)<<endl;
	 PackGen pg(50000),pg2(50000);
	vector<Message> msgs = pg.fragment(tst);
	vector<Message> msgs2(msgs.size());
	cout<<endl;
	for(int i=0;i<msgs.size();i++){msgs[i].Flatten();
		cout<<msgs[i].getFlattenedMessage()<<endl;
		// string current = msgs[i].getData();
		// if(i==0)cout<<current.substr(49950,50)<<endl<<endl;
		// else  cout<<current.substr(0,200)<<endl<<endl;
	}
	for(int i=0;i<msgs.size();i++)
		{
			msgs2[i].unFlatten(msgs[i].getFlattenedMessage());
		 msgs2[i].printMessageDetails();
		}

	Message res = pg2.defragment(msgs2);

	//first=res.getData();
	//cout<<first.substr(49950,100)<<endl;
	cout<<"start: "<<res.getFlattenedMessage()<<"    end\n";
	res.printMessageDetails();
	ofstream out;
	out.open("OUTPUT.jpg");
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