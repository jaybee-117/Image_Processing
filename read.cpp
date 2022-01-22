#include <bits/stdc++.h>
#include <fstream>

#define FileHeaderSize 14
#define InformationHeaderSize 40

using namespace std;

void read (char* Path);

int main(){
    char path[] = "./lena_colored_256.bmp";
    read(path);
    return 0;
}

void read (char* Path){
    ifstream image;
    image.open(Path);                            
    if (image.is_open() == 0){                  
        cout << "Cannot open image" << endl;
    }

    char fileheader[FileHeaderSize];
    image.read(fileheader,FileHeaderSize);

    if (fileheader[0] == 'B' && fileheader[1] == 'M'){
        cout << "File is a BMP"<< endl;
    }
    else{
        cout << "File is not a BMP" << endl;
    }

    int FileSize = ((int)fileheader[2]) + (((int)fileheader[3]) << 8) + (((int)fileheader[4]) << 16) + (((int)fileheader[5]) << 24);
    int DataOffset = ((int)fileheader[10]) + (((int)fileheader[11]) << 8) + (((int)fileheader[12]) << 16) + (((int)fileheader[13]) << 24);

    // int i;
    // cout << "File Header:"<<endl;
    // for (i=0;i<FileHeaderSize;i++){
    //     cout <<(int)fileheader[i]<< " ";
    // }
    // cout << endl;

    cout << "File Size = "<<FileSize/1024<<" KB"<<endl;
    cout << "Data Offset = " <<DataOffset<<" bytes"<<endl;
    cout << "Height = " <<Height<<" bytes"<<endl;
    cout << "Width = " <<Width<<" bytes"<<endl;
    cout << "BitWidth = " <<BitWidth<<" bytes"<<endl;
}