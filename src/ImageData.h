#include "Data.h"
#include <fstream>
using namespace std;
#ifndef IMAGEDATA_H
#define IMAGEDATA_H
class ImageData : public Data
{
    private:
        string image, name;
    public:
        ImageData();
        ImageData(string name, string path, int count);

        bool setName(string n);
        bool setImage(string path);
        void setCount(int);

        int getCount();
        string getImage();
        string getName();

        bool Flatten();
        bool unFlatten(string s);

        ~ImageData();
};
#endif //MESSAGE_H
