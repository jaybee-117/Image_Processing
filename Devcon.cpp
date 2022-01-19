#include<opencv2/opencv.hpp>
#include<iostream>
#include <fstream>
//using namespace cv;
 

void read(char* fileName) {
    fstream ft;
    ft.open(fileName);
    char c1, c2, c;
    unsigned int n;
    cout << sizeof(n) << endl;
    unsigned int file_size = 0, reserved = 0, data_offset = 0;
    unsigned int size_of_header = 0, width = 0, height = 0, planes, bit_width = 0;
    // while (ft)
    // {
    //     // ft >> c1>>c2;
    //     // ft >> file_size;
    //     // ft >> reserved;
    //     ft>>c;
    //     cout << c;

    // }

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
        file_size += (int)c;
        file_size <<= 8;
    }
    cout << "File Size = " << file_size/256 << endl;
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
        data_offset += (int)c;
        data_offset <<= 8;
    }
    cout << "Data offset = " << data_offset/256 << endl;
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
        width += (int)c;
        width <<= 8;
    }
    cout << "Width = " << width/256 << endl;
    // ft >> height;
    for (int i = 0; i < 4; i++)
    {
        ft >> c;
        height += (int)c;
        height <<= 8;
    }
    cout << "Height = " << height/256 << endl;
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
        bit_width += (int)c;
        bit_width <<= 8;
    }
    cout << "Bit Width = " << bit_width/256 << endl;
    //skip(ft, 24);
    n = 24;
    while (n--)
    {
        ft >> c;
    }
    int8_t r, g, b;


    ofstream fot;
    fot.open("dump.txt");
    for (int j = 0; j < height; j++)
    {
        for (int k = 0; k < width; k++)
        {
            ft >> b >> g >> r;
            fot << "[" << r << "," << g << "," << b << "] ";
        }
        fot << endl;
    }

    return;
}

int main() {
    char name[] = "lena_colored_256.bmp";
    read(name);
    char c='c';
    cout << (int)c << endl;
    return 0;
}