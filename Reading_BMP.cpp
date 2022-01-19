//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
#include<bits/stdc++.h>
#include<fstream>

using namespace std;
//using namespace cv;


void Read(const char* path)
{
    ifstream f;
    f.open(path, ios::in | ios::binary);
    if (!f.is_open())
    {
        cout << "file could not be opened" << endl;
        return;
    }
    const int fileheadersize = 14;
    const int informationheadersize = 40;

    unsigned char fileheader[fileheadersize];
    f.read(reinterpret_cast<char*>(fileheader), fileheadersize);

    unsigned char informationheader[informationheadersize];
    f.read(reinterpret_cast<char*>(informationheader), informationheadersize);

    if (fileheader[0] != 'B' || fileheader[1] != 'M')
    {
        cout << "Image is not a .bmp file" << endl;
        return;
    }

    int m_height = informationheader[8] + (informationheader[9] << 8) + (informationheader[10] << 16) + (informationheader[11] << 24);
    int m_width = informationheader[4] + (informationheader[5] << 8) + (informationheader[6] << 16) + (informationheader[7] << 24);
    int bit_width = informationheader[14] + (informationheader[15] << 8);
    int filesize = fileheader[2] + (fileheader[3] << 8) + (fileheader[4] << 16) + (fileheader[5] << 24);
    int offset = fileheader[10];

    vector<vector<float> > m_colors(m_width * m_height, vector<float>(3));
    const int paddingAmount = ((4 - (m_width * 3) % 4) % 4);
    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            unsigned char color[3];
            f.read(reinterpret_cast<char*>(color), 3);

            m_colors[y * m_width + x][2] = static_cast<float>(color[2]) / 255.0f;
            m_colors[y * m_width + x][1] = static_cast<float>(color[1]) / 255.0f;
            m_colors[y * m_width + x][0] = static_cast<float>(color[0]) / 255.0f;
        }
        f.ignore(paddingAmount);
    }

    cout << "file size = " << filesize/1024 <<" KB" << endl;
    cout << "Image height = " << m_height << endl;
    cout<<"Image width = " << m_width << endl;
    cout << "Bit Width = " << bit_width << endl;
    cout << "OFFSET size = " << offset <<endl;

    cout << "Image Pixels are(in R_G_B): " << endl;
    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            cout << m_colors[y * m_width + x][2] <<"_"<< m_colors[y * m_width + x][1] << "_" << m_colors[y * m_width + x][0];
            cout << "   ";
        }
    }
}

int main()
{
    char path[] = "C:\\Users\\JayBee\\Downloads\\DIP Experiment 1\\DIP Experiment 1\\lena_colored_256.bmp";
    Read(path);
	return 0;
}