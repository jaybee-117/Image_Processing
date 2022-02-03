//#include<opencv2/opencv.hpp>
#include<iostream>
#include <fstream>
//using namespace cv;
using namespace std;
 

void read(char* fileName) {
    fstream ft;
    ft.open(fileName);
    char c1, c2, c;
    unsigned int n;
    cout << sizeof(n) << endl;
    unsigned int file_size = 0, reserved = 0, data_offset = 0;
    unsigned int size_of_header = 0, width = 0, height = 0, planes, bit_width = 0;

    // Check BM
    ft >> c1;
    ft >> c2;
    if (c1 == 'B' && c2 == 'M')
        cout << "It is a BMP file" << endl;
    else
    {
        cout << "It is not a BMP file" << endl;
        return;
    }
    // ft >> file_size;
    for (int i = 0; i < 4; i++)
    {
        ft >> c;
        file_size += (((int)c)<<(i*8));
        // file_size <<= 8;
    }
    cout << "File Size (in KB) = " << file_size/1024 << endl;
    //skip(ft, 4);
    n = 4;
    while (n--)
    {
        ft >> c;
    }
    // ft >> data_offset;
    for (int i = 0; i < 4; i++)
    {
        ft >> c;
        data_offset += (((int)c)<<(i*8));
        // data_offset <<= 8;
    }
    cout << "Data offset = " << data_offset << endl;
    // Skip header size
   // skip(ft, 4);
    n = 4;
    while (n--)
    {
        ft >> c;
    }
    // ft >> width;
    for (int i = 0; i < 4; i++)
    {
        ft >> c;
        width += (((int)c)<<(i*8));
        // width <<= 8;
    }
    cout << "Width = " << width << endl;
    // ft >> height;
    for (int i = 0; i < 4; i++)
    {
        ft >> c;
        height += (((int)c)<<(i*8));
        // height <<= 8;
    }
    cout << "Height = " << height << endl;
    //skip(ft, 2);
    n = 2;
    while (n--)
    {
        ft >> c;
    }
    // ft >> bit_width;
    for (int i = 0; i < 4; i++)
    {
        ft >> c;
        bit_width += (((int)c)<<(i*8));
        // bit_width <<= 8;
    }
    cout << "Bit Width = " << bit_width << endl;
    //skip(ft, 24);
    n = 24;
    while (n--)
    {
        ft >> c;
    }
    uint8_t r, g, b;


    ofstream fot;
    fot.open("dump.txt");
    for (int j = 0; j < height; j++)
    {
        for (int k = 0; k < width; k++)
        {
            r=0,g=0,b=0;
            // ft >> b >> g >> r;
            for (int i = 0; i < 1; i++)
            {
                ft >> c;
                b += (((int)c)<<(i*8));
            }
            for (int i = 0; i < 1; i++)
            {
                ft >> c;
                g += (((int)c)<<(i*8));
            }
            for (int i = 0; i < 1; i++)
            {
                ft >> c;
                r += (((int)c)<<(i*8));
            }
            fot << "[" << to_string(r) << "," << to_string(g) << "," << to_string(b) << "] "<<endl;
        }
        fot << endl;
    }

    return;
}

int main() {
    char name[] = "lena_colored_256.bmp";
    read(name);
    return 0;
}