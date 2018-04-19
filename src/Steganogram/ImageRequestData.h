#include "Data.h"
using namespace std;
#ifndef IMAGEREQUESTDATA_H
#define IMAGEREQUESTDATA_H
class ImageRequestData : public Data
{
    private:
        string imageName;
    public:
    	ImageRequestData();
    	bool setImageName(string s);
    	string getImageName();
        bool Flatten();
        bool unFlatten(string s);        
        ~ImageRequestData();
};
#endif //MESSAGE_H