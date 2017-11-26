#include<fstream>
#include<iostream>

using namespace std;

int main()
{
	fstream in1,in2;
	in1.open("dog_b.jpg");
	in2.open("10.7.57.249_dog_b.jpg");

	string s1,s2,tmp;
	s1=s2="";
	while(in1>>tmp)
	{
		s1+=tmp;
	}
	while(in2>>tmp)
	{
		s2+=tmp;
	}
	int i=0;
	while(i<s1.length() && i<s2.length())
	{
		if(s1[i]!=s2[i])
		{
			cout<<"found at "<<i<<" original:"<<(int)s1[i]<<"- current:"<<(int)s2[i]<<endl;
			
		}
		i++;
	}
	cout<<"original size: "<<s1.length()<<endl;
	cout<<"current size: "<<s2.length()<<endl;
	in1.close();
	in2.close();

	return 0;
}