#include "ImageData.h"

ImageData::ImageData()
{}
ImageData::ImageData(string name, string path, int count)
{
    encryptJpeg enc;
    string out_path = "./." + name + " .txt";

    char* inputPath = new char[path.length()+1];
    char* outPath = new char[out_path.length()+1];
    strcpy(inputPath, path.c_str());
    strcpy(outPath,out_path.c_str());

    this->name=name;


    if(name.find(seperator)!=-1)
    {
        perror("Invalid file name\n");
    }

    // Creat hidden textfile containing image count
    string tempFile = "." + name + "_TEMP.txt";
    ofstream of;
    of.open(tempFile);
    of<<count;

    // Use steganography to hide count in image
    string command = "steghide embed -ef " + tempFile + " -cf " + name + " -p 0 -f";

    char* command_char = new char[command.length()+1];
    strcpy(command_char, command.c_str());
    system(command_char);

    if(remove(tempFile.c_str())!=0)cout<<"Couldn't delete file\n";
    // set files
    enc.setInFile(inputPath);
    enc.setOutFile(outPath);

    // set key
    //cout << "Please enter a key: ";
    //cin >> key;
    enc.setPlainKey("200");

    // do the actual encryption
    enc.process('e');

    ifstream in;
    in.open(outPath);
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
void ImageData::setCount(int count)
{
    string tempFile = "." + name + "_TEMP.txt";
    ofstream of;
    of.open(tempFile);
    of<<count;

    // Use steganography to hide count in image
    string command = "steghide embed -ef " + tempFile + " -cf " + name + " -p 0 -f";

    char* command_char = new char[command.length()+1];
    strcpy(command_char, command.c_str());
    system(command_char);

    if(remove(tempFile.c_str())!=0)cout<<"Couldn't delete file\n";
}

int ImageData::getCount()
{
    int count;

    // Use steganography to extract count from image
    string command = "steghide extract -sf " + name + " -p 0 -f";

    char* command_char = new char[command.length()+1];
    strcpy(command_char, command.c_str());
    system(command_char);

    string tempFile = "." + name + "_TEMP.txt";
    ifstream in;
    in.open(tempFile);
    in>>count;
    if(remove(tempFile.c_str())!=0)cout<<"Couldn't delete file\n";
    return count;
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
    flattened+=name;;
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
    image="";
    char c;

    while(ss.get(c))
    {
        image+=c;
    }

    image.erase(0,1);

    string command = "steghide embed -ef ./." + name + ".txt -cf default.jpg -sf " + name + ".jpg -p 0 -f";

    char* command_char = new char[command.length()+1];
    strcpy(command_char, command.c_str());
    system(command_char);

    return true;
}

ImageData::~ImageData(){}
