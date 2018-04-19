#include "Data.h"
#include <vector>
using namespace std;
#ifndef IMAGELISTDATA_H
#define IMAGELISTDATA_H
class ImageListData : public Data
{
    private:
        vector<string> imageList;
    public:
    	ImageListData();
    	bool addImage(string s);
    	vector<string> getImageList();
        bool Flatten();
        bool unFlatten(string s);        
        ~ImageListData();
};
#endif //MESSAGE_H