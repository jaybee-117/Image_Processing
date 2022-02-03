#include <bits/stdc++.h>
#include <fstream>

#define FileHeaderSize 14
#define InformationHeaderSize 40

using namespace std;

uint8_t* read (char* Path, int &FileSize,int &DataOffset, int &Width, int &Height, int &BitWidth);
void RGBtoGray(char* Path, uint8_t* Image, int Width, int Height, int BitWidth);
void Flip(char* Path, uint8_t* Image, int Width, int Height, int BitWidth);
void rotate90(char* Path, uint8_t* Image, int Width, int Height, int BitWidth);
void write(char* Path, uint8_t* Image, string FileName);

int main(){
    char path[] = "./lena_colored_256.bmp";
    uint8_t* pixeldata;
    int FileSize, DataOffset,Width,Height,BitWidth;
    pixeldata = read(path,FileSize, DataOffset,Width,Height,BitWidth);
    RGBtoGray(path, pixeldata, Width, Height, BitWidth);
    Flip(path, pixeldata, Width, Height, BitWidth);
    rotate90(path, pixeldata, Width, Height, BitWidth);
    return 0;
}
    
void Flip(char* Path, uint8_t* Image, int Width, int Height, int BitWidth){
    int i,j;

    uint8_t ImageData[Height][Width][BitWidth/8];
    int jj=0;
    for (i=0;i<Height;i++){
	    for (j=0;j<Width*BitWidth/8;j+=BitWidth/8){
            for(int k=0;k<BitWidth/8;k++){
               ImageData[i][jj][k] = Image[((Width*BitWidth/8)*i)+j+k];
            }
                ++jj;
	    }
        jj=0;
    }

    uint8_t flip[Width][Height][BitWidth/8];
   
    for (i=0;i<Height;i++){
	    for (j=0;j<Width*BitWidth/8;j+=BitWidth/8){
            for(int k=0;k<BitWidth/8;k++)
               flip[jj][i][k] = ImageData[i][jj][k];
             ++jj;
	    }
        
        jj=0;
    }
    
    FILE* image;
    image=fopen(Path,"r");                            

    char fileheader[FileHeaderSize];
    char informationheader[InformationHeaderSize];
    fread(fileheader,1,FileHeaderSize,image);
    fread(informationheader,1,InformationHeaderSize,image);

    uint8_t photo[Height*Width*BitWidth/8];

  
    for (j=0;j<Width*BitWidth/8;j+=BitWidth/8){
	      for( i=0;i<Height;i++){
              for(int k=0;k<BitWidth/8;k++)
                photo[((Width*BitWidth/8)*i)+j+k]=flip[i][jj][k];
	    }       
        ++jj;
          
    }

    ofstream flip_image;
    flip_image.open("flippityflop.bmp");
    for(i=0;i<FileHeaderSize;i++){
        flip_image << fileheader[i];
    }
    for(i=0;i<InformationHeaderSize;i++){
        flip_image << informationheader[i];
    }

    for (i=0;i<Height*Width*BitWidth/8;i++){
	   	flip_image << photo[i];
    }
}

void rotate90(char* Path, uint8_t* Image, int Width, int Height, int BitWidth){
    int i,j;

    uint8_t ImageData[Height][Width][BitWidth/8];
    int jj=0;
    for (i=0;i<Height;i++){
	    for (j=0;j<Width*BitWidth/8;j+=BitWidth/8){
            for(int k=0;k<BitWidth/8;k++){
               ImageData[i][jj][k] = Image[((Width*BitWidth/8)*i)+j+k];
            }
                ++jj;
	    }
        jj=0;
    }

    uint8_t flip[Width][Height][BitWidth/8];
   
    for (i=0;i<Height;i++){
	    for (j=0;j<Width*BitWidth/8;j+=BitWidth/8){
            for(int k=0;k<BitWidth/8;k++)
               flip[jj][i][k] = ImageData[i][jj][k];
             ++jj;
	    }        
        jj=0;
    }
    
    FILE* image;
    image=fopen(Path,"r");                            

    char fileheader[FileHeaderSize];
    char informationheader[InformationHeaderSize];
    fread(fileheader,1,FileHeaderSize,image);
    fread(informationheader,1,InformationHeaderSize,image);

    uint8_t photo[Height*Width*BitWidth/8];

  
    for (j=0;j<Width*BitWidth/8;j+=BitWidth/8){
	      for( i=0;i<Height;i++){
              for(int k=0;k<BitWidth/8;k++)
                photo[((Width*BitWidth/8)*i)+j+k]=flip[Height-i][jj][k];
	    }       
        ++jj;
          
    }

    ofstream rotate90_image;
    rotate90_image.open("rotate90.bmp");
    for(i=0;i<FileHeaderSize;i++){
        rotate90_image << fileheader[i];
    }
    for(i=0;i<InformationHeaderSize;i++){
        rotate90_image << informationheader[i];
    }

    for (i=0;i<Height*Width*BitWidth/8;i++){
	   	rotate90_image << photo[i];
    }
}

uint8_t* read (char* Path, int &FileSize,int &DataOffset, int &Width, int &Height, int &BitWidth){
    FILE* image;
    image=fopen(Path,"r");                            
    if (image == NULL){                  
        cout << "Cannot open image" << endl;
    }

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
    cout << "BitWidth = " <<BitWidth<<" bits = "<<BitWidth/8<<" byte(s)"<< endl;
    int totalSize  = Height*Width*BitWidth/8;

    uint8_t *PixelData;
    PixelData = (uint8_t*) malloc(totalSize); 
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
    return PixelData;
}

void RGBtoGray(char* Path, uint8_t* Image, int Width, int Height, int BitWidth){

    int i,j;
    uint8_t grayscale[Height*Width*BitWidth/8];
    memset(grayscale, 255, Height*Width*BitWidth/8);
    for (i=0;i<Height*Width*BitWidth/8;i+=3){
        
        grayscale[i] = ((0.114*Image[i] + 0.587*Image[i+1] + 0.299*Image[i+2]));
        grayscale[i+1] = grayscale[i];
        grayscale[i+2] = grayscale[i];
        
    }
    write(Path, grayscale, "grayscale.bmp");
}

//write doesnt work if the image dimentions have changed
void write(char* Path, uint8_t* Image, string FileName){
    int Width, Height, BitWidth;
    FILE* image;
    image=fopen(Path,"r");                            

    char fileheader[FileHeaderSize];
    char informationheader[InformationHeaderSize];
    fread(fileheader,1,FileHeaderSize,image);
    fread(informationheader,1,InformationHeaderSize,image);

    Width = ((int)informationheader[4]) + (((int)informationheader[5]) << 8) + (((int)informationheader[6]) << 16) + (((int)informationheader[7]) << 24);
    Height = ((int)informationheader[8]) + (((int)informationheader[9]) << 8) + (((int)informationheader[10]) << 16) + (((int)informationheader[11]) << 24);
    BitWidth = ((int)informationheader[14]) + ((int)informationheader[15] << 8);

    ofstream output_image;
    output_image.open(FileName);
    for(int i=0;i<FileHeaderSize;i++){
        output_image << fileheader[i];
    }
    for(int i=0;i<InformationHeaderSize;i++){
        output_image << informationheader[i];
    }

    for (int i=0;i<Height*Width*BitWidth/8;i++){
	   	output_image << Image[i];
    }
}
