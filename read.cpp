#include <bits/stdc++.h>
#include <fstream>

#define FileHeaderSize 14
#define InformationHeaderSize 40

using namespace std;

uint8_t* read (char* Path, int FileSize,int DataOffset, int Width, int Height, int BitWidth);
void RGBtoGray(char* Path, uint8_t* Image, int Width, int Height, int BitWidth);

int main(){
    char path[] = "./lena_colored_256.bmp";
    uint8_t* pixeldata;
    int FileSize, DataOffset,Width,Height,BitWidth;
    pixeldata = read(path,FileSize, DataOffset,Width,Height,BitWidth);
    return 0;
}

uint8_t* read (char* Path, int FileSize,int DataOffset, int Width, int Height, int BitWidth){
    FILE* image;
    image=fopen(Path,"r");                            
    // if (image.is_open() == 0){                  
    //     cout << "Cannot open image" << endl;
    // }

    char fileheader[FileHeaderSize];
    char informationheader[InformationHeaderSize];
    fread(fileheader,1,FileHeaderSize,image);
    fread(informationheader,1,InformationHeaderSize,image);
    if (fileheader[0] == 'B' && fileheader[1] == 'M'){
        cout << "File is a BMP"<< endl;
    }
    else{
        cout << "File is not a BMP" << endl;
    }

    FileSize = ((int)fileheader[2]) + (((int)fileheader[3]) << 8) + (((int)fileheader[4]) << 16) + (((int)fileheader[5]) << 24);
    DataOffset = ((int)fileheader[10]) + (((int)fileheader[11]) << 8) + (((int)fileheader[12]) << 16) + (((int)fileheader[13]) << 24);
    Width = ((int)informationheader[4]) + (((int)informationheader[5]) << 8) + (((int)informationheader[6]) << 16) + (((int)informationheader[7]) << 24);
    Height = ((int)informationheader[8]) + (((int)informationheader[9]) << 8) + (((int)informationheader[10]) << 16) + (((int)informationheader[11]) << 24);
    BitWidth = ((int)informationheader[14]) + ((int)informationheader[15] << 8);

    cout << "File Size = "<<FileSize/1024<<" KB"<<endl;
    cout << "Data Offset = " <<DataOffset<<" bytes"<<endl;
    cout << "Height = " <<Height<<" pixels"<<endl;
    cout << "Width = " <<Width<<" pixels"<<endl;
    cout << "BitWidth = " <<BitWidth<<" bits = "<<BitWidth/8<<" bytes"<< endl;
    int totalSize  = Height*Width*BitWidth/8;
    cout<<totalSize;
    uint8_t PixelData[Height*Width*BitWidth/8];

    fread(PixelData,1,totalSize,image);
    
    uint8_t ImageData[Height][Width*BitWidth/8];
    int i,j;
    ofstream fot;
    fot.open("Pixel_data.txt");
    for (i=0;i<Height;i++){
	    for (j=0;j<Width*BitWidth/8;j++){
	   	ImageData[i][j] = PixelData[((Width*BitWidth/8)*i)+j];
		if(j == 0)
			fot << "[";
		else if(j%3 == 0)
			fot << "] [";
		else
			fot << ",";

		fot << (int)(uint8_t)ImageData[i][j];
	    }
	    fot << "]" << endl;
    }
    RGBtoGray(Path,PixelData,Width,Height,BitWidth);                   //ldskp;lqkdp;k 
    return PixelData;
}

void RGBtoGray(char* Path, uint8_t* Image, int Width, int Height, int BitWidth){

    int i,j;
    uint8_t grayscale[Height*Width*BitWidth/8];
    for (i=0;i<Height*Width*BitWidth/8;i+=3){
        
        grayscale[i] = ((0.114*Image[i] + 0.587*Image[i+1] + 0.299*Image[i+2]));
        grayscale[i+1] = grayscale[i];
        grayscale[i+2] = grayscale[i];
        
    }
    FILE* image;
    image=fopen(Path,"r");                            

    char fileheader[FileHeaderSize];
    char informationheader[InformationHeaderSize];
    fread(fileheader,1,FileHeaderSize,image);
    fread(informationheader,1,InformationHeaderSize,image);

    uint8_t photo[Height*Width*BitWidth/8];

    fread(photo, 1,Height*Width*BitWidth/8,image);

    ofstream grayscale_image;
    grayscale_image.open("grayscale.bmp");
    for(i=0;i<FileHeaderSize;i++){
        grayscale_image << fileheader[i];
    }
    for(i=0;i<InformationHeaderSize;i++){
        grayscale_image << informationheader[i];
    }

    for (i=0;i<Height*Width*BitWidth/8;i++){
	   	grayscale_image << grayscale[i];
        //cout<<(uint8_t)grayscale[i]<<" "; 
    }
}