#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <bits/stdc++.h>

using namespace cv;
using namespace std;

//--------Start of Global Variables----------//
const int num_images = 13;
const int num_kernels = 4;
const int num_filters = 8;
const int image_slider_max = num_images - 1;
const int size_slider_max = num_kernels-1;
const int filter_slider_max = num_filters-1;
const int photo_slider_max = num_images - 1;
const int sigma_slider_max = 250;
int image_slider;
int size_slider;
int filter_slider;
int photo_slider;
int sigma_slider;
Mat dst;
Mat img;
Mat photo;
Mat new_img;
vector< vector <vector <vector <float> > > > allfilter;

vector<string> images ={"Noisy_Images/Cameraman_Salt&Pepper_0.02.jpg",
                        "Noisy_Images/Cameraman_Salt&Pepper_0.005.jpg",
                        "Noisy_Images/Cameraman_Salt&Pepper_0.005.jpg",
                        "Noisy_Images/Cameraman_Salt&Pepper_0.02.jpg",
                        "Noisy_Images/Cameraman_Salt&Pepper_0.08.jpg",
                        "Noisy_Images/Camerman_Gaussian_0.005.jpg",
                        "Noisy_Images/Camerman_Gaussian_0.05.jpg",
                        "Noisy_Images/Pepper_Gaussian_0.005.jpg",
                        "Noisy_Images/Pepper_Gaussian_0.01.jpg",
                        "Noisy_Images/Pepper_Salt&Pepper_0.005.jpg",
                        "Noisy_Images/Pepper_Salt&Pepper_0.02.jpg",
                        "Noisy_Images/Pepper_Salt&Pepper_0.08.jpg",
                        "external-content.duckduckgo.com.jpg",
                        "Normal_Images/jetplane.jpg",
                        "Normal_Images/lake.jpg",
                        "Normal_Images/lena_gray_512.jpg",
                        "Normal_Images/livingroom.jpg",
                        "Normal_Images/mandril_gray.jpg",
                        "Normal_Images/pirate.jpg",
                        "Normal_Images/walkbridge.jpg"};

vector<int> kernelSize = {3,5,7,9};

vector<vector<int>>hp = {{-1,-1,-1},
                        {-1,8,-1},
                        {-1,-1,-1}};

vector<vector<vector<float> > >mean1{ 
{       {1}},

{       {1/9.0, 1/9.0, 1/9.0},
        {1/9.0, 1/9.0, 1/9.0},
        {1/9.0, 1/9.0, 1/9.0}},

{       {1/25.0, 1/25.0, 1/25.0, 1/25.0, 1/25.0},
        {1/25.0, 1/25.0, 1/25.0, 1/25.0, 1/25.0},
        {1/25.0, 1/25.0, 1/25.0, 1/25.0, 1/25.0},
        {1/25.0, 1/25.0, 1/25.0, 1/25.0, 1/25.0},
        {1/25.0, 1/25.0, 1/25.0, 1/25.0, 1/25.0}},

{       {1/49.0, 1/49.0, 1/49.0, 1/49.0, 1/49.0, 1/49.0, 1/49.0},
        {1/49.0, 1/49.0, 1/49.0, 1/49.0, 1/49.0, 1/49.0, 1/49.0},
        {1/49.0, 1/49.0, 1/49.0, 1/49.0, 1/49.0, 1/49.0, 1/49.0},
        {1/49.0, 1/49.0, 1/49.0, 1/49.0, 1/49.0, 1/49.0, 1/49.0},
        {1/49.0, 1/49.0, 1/49.0, 1/49.0, 1/49.0, 1/49.0, 1/49.0},
        {1/49.0, 1/49.0, 1/49.0, 1/49.0, 1/49.0, 1/49.0, 1/49.0},
        {1/49.0, 1/49.0, 1/49.0, 1/49.0, 1/49.0, 1/49.0, 1/49.0}}
};

vector<vector<vector<float> > >prewitt_V{
{       {1}},

{       {1, 0 ,-1},
        {1, 0, -1},
        {1, 0, -1}},

{       {1, 1, 0, -1, -1},
        {1, 1, 0, -1, -1},
        {1, 1, 0, -1, -1},
        {1, 1, 0, -1, -1},
        {1, 1, 0, -1, -1}},

{       {1, 1, 1, 0, -1, -1, -1},
        {1, 1, 1, 0, -1, -1, -1},
        {1, 1, 1, 0, -1, -1, -1},
        {1, 1, 1, 0, -1, -1, -1},
        {1, 1, 1, 0, -1, -1, -1},
        {1, 1, 1, 0, -1, -1, -1},
        {1, 1, 1, 0, -1, -1, -1}}
};

vector<vector<vector<float> > >prewitt_H{
{       {1}},

{       {-1, -1, -1},
        { 0,  0,  0},
        { 1,  1,  1}},

{       {-1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1},
        { 0,  0,  0,  0,  0},
        { 1,  1,  1,  1,  1},
        { 1,  1,  1,  1,  1}},

{       {-1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1},
        { 0,  0,  0,  0,  0,  0,  0},
        { 1,  1,  1,  1,  1,  1,  1},
        { 1,  1,  1,  1,  1,  1,  1},
        { 1,  1,  1,  1,  1,  1,  1}}
};

vector<vector<vector<float> > >laplacian{
{       {1}},

{	    {-1, -1, -1},
        {-1,  8, -1},
        {-1, -1, -1}},

{       {-1, 3, -4, -3, -1},
        {-3, 0,  6,  0, -3},
        {-4, 6, 20,  6, -4},
        {-3, 0,  6,  0, -3},
        {-1,-3, -4, -3, -1}},

{       {-2, -3, -4, -6, -4, -3, -2},
        {-3, -5, -4, -3, -4, -5, -3},
        {-4, -4,  9, 20,  9, -4, -4},
        {-6, -3, 20, 36, 20, -3, -6},
        {-4, -4,  9, 20,  9, -4, -4},
        {-3, -5, -4, -3, -4, -5, -3},
        {-2, -3, -4, -6, -4, -3, -2}}
};

vector<vector<vector<float> > > sobel_H{
{       {1}} ,

{       {  1,  2,  1},
        {  0,  0,  0},
        { -1, -2, -1} },

 {      { 1,   4,   7,   4,  1},
        { 2,  10,  17,  10,  2},
        { 0,   0,   0,   0,  0},
        {-2, -10, -17, -10, -2},
        { -1, -4, -7, -4, -1 } },

 {      {  1,  4,  9,  13,  9,  4,  1},
        {  3, 11, 26,  34, 26, 11,  3},
        {  3, 13, 30,  40, 30, 13,  3},
        {  0,  0,  0,   0,  0,  0,  0},
        { -3, -13,-30,-40,-30,-13, -3},
        { -3, -11,-26, 34,-26,-11, -3},
        { -1, -4, -9, -13, -9, -4, -1}}
};

vector<vector<vector<float> > > sobel_V = { 
{       {1}},

{       { -1, 0, 1 },
        { -2, 0, 2 },
        { -1, 0, 1 } },

{       { -1,  -2, 0,  2, 1 },
        { -4, -10, 0, 10, 4 },
        { -7, -17, 0, 17, 7 },
        { -4, -10, 0, 10, 4 },
        { -1,  -2, 0, -2, 1 } },

 {      { -1,  -3,  -3, 0, 3,  3,   1},
        { -4, -11, -13, 0, 13, 11,  4},
        { -9, -26, -30, 0, 30, 26,  9},
        { -13, -34,-40, 0, 40, 34, 13},
        {  -9, -26,-30, 0, 30, 26,  9},
        {  -4, -11,-13, 0, 13, 11,  4},
        {   1,  -3, -3, 0,  3,  3,  1}}
};

vector<vector<vector<float> > > sobel_D = { 
{       {1}},

{       { 0,  1, 2},
        { -1, 0, 1},
        { -2,-1, 0} },

{       {1/16.0, 2/16.0, 1/16.0},
        {2/16.0, 4/16.0, 2/16.0},
        {1/16.0, 2/16.0, 1/16.0}}
};

vector<vector<vector<float> > > gaussian = {
{       {1}},

{       {1/273.0, 4/273.0, 7/273.0, 4/273.0, 1/273.0},
        {4/273.0, 16/273.0, 26/273.0, 16/273.0, 4/273.0},
        {7/273.0, 26/273.0, 41/273.0, 26/273.0, 7/273.0},
        {4/273.0, 16/273.0, 26/273.0, 16/273.0, 4/273.0},
        {1/273.0, 4/273.0, 7/273.0, 4/273.0, 1/273.0}},

{       {0/1003.0,  0/1003.0,  1/1003.0,   2/1003.0,  1/1003.0,  0/1003.0, 0/1003.0},
        {0/1003.0,  3/1003.0, 13/1003.0,  22/1003.0, 13/1003.0,  3/1003.0, 0/1003.0},
        {1/1003.0, 13/1003.0, 59/1003.0,  97/1003.0, 59/1003.0, 13/1003.0, 1/1003.0},
        {2/1003.0, 22/1003.0, 97/1003.0, 159/1003.0, 97/1003.0, 22/1003.0, 2/1003.0},
        {1/1003.0, 13/1003.0, 59/1003.0,  97/1003.0, 59/1003.0, 13/1003.0, 1/1003.0},
        {0/1003.0,  3/1003.0, 13/1003.0,  22/1003.0, 13/1003.0,  3/1003.0, 0/1003.0},
        {0/1003.0,  0/1003.0,  1/1003.0,   2/1003.0,  1/1003.0,  0/1003.0, 0/1003.0}}
};

vector<vector<vector<float> > > LoG = {
{       {1}},

{       {0, 1, 0},
        {1,-4, 1},
        {0, 1, 0}},

{       {0, 0, 1, 0, 0},
        {0, 1, 2, 1, 0},
        {1, 2,-16, 2, 1},
        {0, 1, 2, 1, 0},
        {0, 0, 1, 0, 0}},

{       {0, 0, 0, 1, 0, 0, 0},
        {0, 0, 1, 2, 1, 0, 0},
        {0, 1, 2, 4, 2, 1, 0},
        {1, 2, 4, -64, 4, 2, 1},
        {0, 1, 2, 4, 2, 1, 0},
        {0, 0, 1, 2, 1, 0, 0},
        {0, 0, 0, 1, 0, 0, 0}}
};
//------End of Global Variables--------//


//------Start of Adaptive High pass filter------//
vector<vector<int>> hpf(Mat img)
{
    vector<vector<int>>filter = hp;
    int filter_size = 3;
    vector<vector<int>>new_img(img.rows, vector<int>(img.cols,0));
    for(int i=0; i<img.rows; i++)
    {
        for(int j=0; j<img.cols; j++)
        {
            int temp = 0;
            for(int k=-1; k<filter_size-1; k++)
            {
                for(int l=-1; l<filter_size-1; l++)
                {
                    // cout<<i<<" "<<j<<" "<<k<<" "<<l<<endl;
                    if(i+k>=0 && j+l>=0 && i+k<img.rows && j+l<img.cols)
                    {
                        int t = img.at<uchar>(i+k,j+l);
                        // cout<<t<<endl;
                        temp += t*filter[k+1][l+1];                    
                    } 
                }
            }
            new_img[i][j] = temp;
            // if(new_img[i][j] < 0)
            //     cout<<"hpf "<<i<<" "<<j<<" "<<new_img[i][j]<<endl;
        }
    }
    return new_img;
}

vector<vector<float>> aw(vector<vector<int>>hpf, int sigma)
{
    int n = hpf.size();
    int m = hpf[0].size();
    vector<vector<float>>ans(n, vector<float>(m,0));
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            ans[i][j] = 1.0 - exp(-(1.0*abs(hpf[i][j]))/(1.0*(2*sigma*sigma)));
            // cout<<"ans "<<i<<" "<<j<<" "<<ans[i][j]<<endl;
            //cout<<"ans "<<i<<" "<<j<<" "<<abs(hpf[i][j])/(2*sigma*sigma)<<" "<<(1.0*abs(hpf[i][j]))/(1.0*(2*sigma*sigma))<<endl;
        }
    }
    return ans;
}

Mat ahb(Mat img, float b, int sigma)
{
    vector<vector<int>> fhp = hpf(img);
    vector<vector<float>>awa = aw(fhp,sigma);
    int n = fhp.size();
    int m = fhp[0].size();
    Mat new_img(n , m , CV_8UC1, 1);
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            new_img.at<uchar>(i,j) = (uint8_t)(img.at<uchar>(i,j) + round(b*awa[i][j]*fhp[i][j]));
        }
    }
    return new_img;
}
//------End of Adaptive High pass filter------//


static void on_trackbar( int, void* ){

    int ima = image_slider<images.size()?image_slider:images.size()-1;
    dst = imread(images[ima], 0);
    imshow( "Spatial Filtering", dst );

    int k = size_slider<allfilter[0].size()?size_slider:allfilter[0].size()-1;
    int f = filter_slider<allfilter.size()?filter_slider:allfilter.size()-1;

    vector<vector<float> >filter = allfilter[f][k]; 
    int filter_size = filter.size();
    Mat new_dst(dst.rows - filter_size+1, dst.cols- filter_size+1, CV_8UC1, 1);
    for(int i=0; i<new_dst.rows; i++)
    {
        for(int j=0; j<new_dst.cols; j++)
        {
            float temp = 0;
            for(int k=0; k<filter_size; k++)
            {
                for(int l=0; l<filter_size; l++)
                {
                    if(i+k<dst.rows && j+l<dst.cols)
                    {
                        int t = dst.at<uchar>(i+k,j+l);
                        temp += t*filter[k][l];                    
                    }
                }
            }
            new_dst.at<uchar>(i,j) = (uint8_t)temp;
        }
    }
    imshow( "Spatial Filtering", new_dst );
}

static void on_hpff( int, void* )
{
    int pho = photo_slider<images.size()?photo_slider:images.size()-1;
    photo = imread(images[pho], 0);
    imshow( "Adaptive Filter", photo );
    new_img = ahb(photo, 0.4, sigma_slider*5);
    imshow( "Adaptive Filter", new_img );
}

int main( void )
{

    allfilter.push_back(mean1);
    allfilter.push_back(prewitt_V);
    allfilter.push_back(prewitt_H);
    allfilter.push_back(laplacian);
    allfilter.push_back(sobel_H);
    allfilter.push_back(sobel_V);
    allfilter.push_back(sobel_D);
    allfilter.push_back(gaussian);
    allfilter.push_back(LoG);

    char Image[50];
    char Kernel[50];
    char Filter[50];
    char Photo[50];
    char Sigma[50];

    //********************Spatial Filter************************//
    namedWindow("Spatial Filtering", WINDOW_AUTOSIZE);

    sprintf( Image, "Image no." );
    createTrackbar( Image, "Spatial Filtering", &image_slider, image_slider_max, on_trackbar );

    sprintf( Kernel, "Size: {1,3,5,7}");
    createTrackbar( Kernel, "Spatial Filtering", &size_slider, size_slider_max, on_trackbar );

    sprintf( Filter, "Filter no. %d", filter_slider_max );
    createTrackbar( Filter, "Spatial Filtering", &filter_slider, filter_slider_max, on_trackbar);

    on_trackbar( image_slider, 0 );
    on_trackbar( size_slider, 0 );
    on_trackbar( filter_slider, 0 );
    //******************************************************//


    //********Adaptive High Passs Filter***********//
    
    namedWindow("Adaptive Filter", WINDOW_AUTOSIZE);

    sprintf( Photo, "Image no.");
    createTrackbar( Photo, "Adaptive Filter", &photo_slider, photo_slider_max, on_hpff );

    sprintf(Sigma, "Sigma x 5");
    createTrackbar( Sigma, "Adaptive Filter", &sigma_slider, sigma_slider_max, on_hpff );

    on_hpff( photo_slider, 0 );
    on_hpff( sigma_slider, 0 );
    //********************************************//
    waitKey(0);
    return 0;
}