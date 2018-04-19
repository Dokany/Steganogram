#include "Data.h"
#include <fstream>
#include <string>
#include <cstring>
#include <iostream>
using namespace std;

#ifndef IMAGEDATA_H
#define IMAGEDATA_H
class ImageData : public Data
{
    private:
        string image, name, path,cur;
    public:
        ImageData();
        ImageData(string name, string path, int count);

        bool setName(string n);
        bool setImage(string path);
        void setCount(int);
        void setPath(string path);

        int getCount();
        int getExtractedCount();
        string getImage();
        string getName();
        string getPath();
        void embeddInDefault();
        string view(string path, int &count);

         bool Flatten();
         bool unFlatten(string s);

        ~ImageData();
};
#endif //MESSAGE_H
