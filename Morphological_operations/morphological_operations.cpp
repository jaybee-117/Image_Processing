#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

vector<vector <bool> > structure1 = {   {0,0,0},
                                        {0,1,1},
                                        {0,0,0}};

vector<vector <bool> > structure2 = {   {0,1,0},
                                        {1,1,1},
                                        {0,1,0}};

vector<vector <bool> > structure3 = {   {1,1,1},
                                        {1,1,1},
                                        {1,1,1}};

void printbin(Mat, string);
Mat erode(Mat, vector<vector<bool> >);
Mat dilate(Mat, vector<vector<bool> >);
Mat open_bin(Mat, vector<vector<bool> >);
Mat close_bin(Mat, vector<vector<bool> >);

int main(){
    Mat og_img = imread("ricegrains_mono.bmp",0);
    imshow("Original Image",og_img);
    printbin(og_img,"original.bin");

    Mat eroded_img = erode(og_img, structure2);
    printbin(eroded_img,"eroded.bin");
    imshow("Eroded Image", eroded_img);

    Mat dilated_img = dilate(og_img, structure2);
    printbin(dilated_img,"dilated.bin");
    imshow("Dilated Image", dilated_img);

    Mat opened_img = open_bin(og_img, structure2);
    printbin(opened_img,"opened.bin");
    imshow("Opened Image", opened_img);

    Mat closed_img = close_bin(og_img, structure2);
    printbin(closed_img,"closed.bin");
    imshow("Closed Image", closed_img);

    waitKey(0);
    return 0;
}

void printbin(Mat img, String filename){
    ofstream dump(filename);
    for (int i =0; i< img.rows; i++){
        for (int j=0; j< img.cols; j++){
            dump << (bool)img.at<uchar>(i,j) << " ";
        }
        dump << endl;
    }
}

Mat erode(Mat img, vector<vector<bool> > structure){
    bool image[img.rows][img.cols];
    Mat eroded_image(img.rows, img.cols, CV_8UC1, 1);
    for (int i = 0; i< img.rows; i++){
        for(int j = 0; j< img.cols; j++){
            image[i][j] = (bool)img.at<uchar>(i,j);
            eroded_image.at<uchar>(i,j) = 255;
        }
    }

    for (int i = 1; i< img.rows - 1; i++){
        for(int j = 1; j< img.cols - 1; j++){
            
            for(int k = 0; k< 3 ;k++){
                for(int l = 0; l<3 ; l++){
                    if (structure[k][l]){
                        if (!image[i+k][j+l]){
                            eroded_image.at<uchar>(i,j) = 0;
                            break;
                        }
                    }
                }
                if (eroded_image.at<uchar>(i,j) == 0) break;
            }

        }
    }
    return eroded_image;
}

Mat dilate(Mat img, vector<vector<bool> > structure){
    bool image[img.rows][img.cols];
    Mat dilated_image(img.rows, img.cols, CV_8UC1, 1);
    for (int i = 0; i< img.rows; i++){
        for(int j = 0; j< img.cols; j++){
            image[i][j] = (bool)img.at<uchar>(i,j);
            dilated_image.at<uchar>(i,j) = 0;
        }
    }

    for (int i = 1; i< img.rows - 1; i++){
        for(int j = 1; j< img.cols - 1; j++){
            if(image[i][j]){
                for(int k = 0; k< 3 ;k++){
                    for(int l = 0; l<3 ; l++){
                        if (structure[k][l]){
                            dilated_image.at<uchar>(i+k,j+l) = 255;
                        }
                    }
                }   
            }
        }
    }
    return dilated_image;
}

Mat open_bin(Mat img, vector<vector<bool> > structure){
    Mat temp = erode(img, structure);
    Mat opened_image = dilate(temp, structure);
    return opened_image;
}

Mat close_bin(Mat img, vector<vector<bool> > structure){
    Mat temp = dilate(img, structure);
    Mat dilated_image = erode(temp, structure);
    return dilated_image;
}