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
    char informationheader[InformationHeaderSize];
    image.read(fileheader,FileHeaderSize);
    image.read(informationheader,InformationHeaderSize);
    if (fileheader[0] == 'B' && fileheader[1] == 'M'){
        cout << "File is a BMP"<< endl;
    }
    else{
        cout << "File is not a BMP" << endl;
    }

    int FileSize = ((int)fileheader[2]) + (((int)fileheader[3]) << 8) + (((int)fileheader[4]) << 16) + (((int)fileheader[5]) << 24);
    int DataOffset = ((int)fileheader[10]) + (((int)fileheader[11]) << 8) + (((int)fileheader[12]) << 16) + (((int)fileheader[13]) << 24);
    int Width = ((int)informationheader[4]) + (((int)informationheader[5]) << 8) + (((int)informationheader[6]) << 16) + (((int)informationheader[7]) << 24);
    int Height = ((int)informationheader[8]) + (((int)informationheader[9]) << 8) + (((int)informationheader[10]) << 16) + (((int)informationheader[11]) << 24);
    int BitWidth = ((int)informationheader[14]) + ((int)informationheader[15] << 8);

    // int i;
    // cout << "File Header:"<<endl;
    // for (i=0;i<FileHeaderSize;i++){
    //     cout <<(int)fileheader[i]<< " ";
    // }
    // cout << endl;

    cout << "File Size = "<<FileSize/1024<<" KB"<<endl;
    cout << "Data Offset = " <<DataOffset<<" bytes"<<endl;
    cout << "Height = " <<Height<<" pixels"<<endl;
    cout << "Width = " <<Width<<" pixels"<<endl;
    cout << "BitWidth = " <<BitWidth<<" bits = "<<BitWidth/8<<" bytes"<< endl;

    char PixelData[Height*Width*BitWidth/8];
    image.read(PixelData,Height*Width*BitWidth/8);

    char ImageData[Height][Width*BitWidth/8];
    int i,j;
    for (i=0;i<Height;i++){
	    for (j=0;j<Width*BitWidth/8;j++){
	   	ImageData[i][j] = PixelData[((Width*BitWidth/8)*i)+j];
		if(j == 0)
			cout << "[";
		else if(j%3 == 0)
			cout << "] [";
		else
			cout << ",";

		cout << (int)ImageData[i][j];
	    }
	    cout << "]" << endl;
    }

}
