// #include <opencv2/core/core.hpp>
// #include <opencv2/imgproc/imgproc.hpp>
// #include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void imhist_g(Mat image, int histogram[]);
void imhist_c(Mat image, int h[]);
void histDisplay_c(int histogram[], const char* name);
void histDisplay_errror404(vector < Vec3b> histogram, const char* name);
Mat histequalize_g(Mat image, int h[]);
Mat histogram_matching(Mat src, Mat trg);

int main()
{
    
    string s = "C:\\Users\\Rahul\\Desktop\\IP_LAB\\DIP Experiment 2\\Images for Histogram Equalization\\";
    string t, source, target;
    char gray;
    /*
    cout << "Enter the image name with the extention: ";
    cin >> t;
    Mat image = imread(s + t, 1);
    imshow("Display Window", image);
    int h[256];      
    imhist_c(image, h);
    histDisplay_c(h, "OG_Histogram");
    Mat Eq_Image = histequalize_c(image, h);
    int h_eq[256];
    imhist_c(Eq_Image, h_eq);
    histDisplay_c(h_eq, "Eq_Histogram");
    */
    cout << "Enter the name of source: ";
    cin >> source;
    cout << "Enter the name of target: ";
    cin >> target;
    Mat src = imread(s + source, 1);
    Mat trg = imread(s + target, 1);
    histogram_matching(src, trg);

    waitKey(0);
	return 0;
}

void imhist_g(Mat image, int histogram[])
{

    // initialize all intensity values to 0
    for (int i = 0; i < 256; i++)
    {
        histogram[i] = 0;
    }

    // calculate the no of pixels for each intensity values
    for (int y = 0; y < image.rows; y++)
        for (int x = 0; x < image.cols; x++) {
            int index = (int)image.at<uchar>(y, x);
            histogram[index]++;
        }
}

void imhist_c(Mat image, int h[])
{
    int i;
    for (i = 0; i < 256; i++)
        h[i] = 0;

    int b, g, r;
    int intensity;
    // calculate the no of pixels for each intensity values
    for (int y = 0; y < image.rows; y++) {
        for (int x = 0; x < image.cols; x++) {
            Vec3b& bgr = image.at<Vec3b>(y, x);
            intensity = round(0.114 * bgr[0] + 0.587 * bgr[1] + 0.299 * bgr[2]);
            h[intensity]++;           
        }
    }
}

void histDisplay_c(int histogram[], const char* name)
{
    int hist[256];
    for (int i = 0; i < 256; i++)
    {
        hist[i] = histogram[i];
    }
    // draw the histograms
    int hist_w = 512; int hist_h = 400;
    int bin_w = round((double)hist_w / 256);

    Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(255, 255, 255));

    // find the maximum intensity element from histogram
    int max = hist[0];
    for (int i = 1; i < 256; i++) {
        if (max < hist[i]) {
            max = hist[i];
        }
    }

    // normalize the histogram between 0 and histImage.rows
    for (int i = 0; i < 256; i++)
    {
        hist[i] = ((double)hist[i] / max) * histImage.rows;
    }


    // draw the intensity line for histogram
    for (int i = 0; i < 256; i++)
    {
        line(histImage, Point(bin_w * (i), hist_h), Point(bin_w * (i), hist_h - hist[i]), Scalar(0, 0, 0), 1, 8, 0);
    }

    // display histogram
    //namedWindow(name);
    imshow(name, histImage);
}

void histDisplay_errror404(vector < Vec3b> histogram, const char* name)
{
    for (int i = 0; i < 256; i++)
    {
        cout<< histogram[i][0] << " " << histogram[i][1] <<" " << histogram[i][2]<<endl;
        
    }
    int hist_b[256];
    int hist_g[256];
    int hist_r[256];

    int max_b = histogram[0][0];
    int max_g = histogram[0][1];
    int max_r = histogram[0][2];
    for (int i = 0; i < 256; i++)
    {
        hist_b[i] = histogram[i][0];
        if (max_b < hist_b[i]) {
            max_b = hist_b[i];
        }
        hist_g[i] = histogram[i][1];
        if (max_g < hist_g[i]) {
            max_g = hist_g[i];
        }
        hist_r[i] = histogram[i][2];
        if (max_r < hist_r[i]) {
            max_r = hist_r[i];
        }
    }

    // draw the histograms
    int hist_w = 512; int hist_h = 400;
    int bin_w = round((double)hist_w / 256);

    // normalize the histogram between 0 and histImage.rows
    for (int i = 0; i < 256; i++)
    {
        hist_b[i] = ((double)hist_b[i] / max_b) * hist_h;
        hist_g[i] = ((double)hist_g[i] / max_g) * hist_h;
        hist_r[i] = ((double)hist_r[i] / max_r) * hist_h;
    }

    Mat histImage_b(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));
    Mat histImage_g(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));
    Mat histImage_r(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));

    // draw the intensity line for histogram
    for (int i = 0; i < 256; i++)
    {
        line(histImage_b, Point(bin_w * (i), hist_h), Point(bin_w * (i), hist_h - hist_b[i]), Scalar(0, 0, 255), 1, 8, 0);
        line(histImage_g, Point(bin_w * (i), hist_h), Point(bin_w * (i), hist_h - hist_g[i]), Scalar(0, 255, 0), 1, 8, 0);
        line(histImage_r, Point(bin_w * (i), hist_h), Point(bin_w * (i), hist_h - hist_r[i]), Scalar(255, 0, 0), 1, 8, 0);
    }

    // display histogram
    //namedWindow(name);
    imshow("Hist_B", histImage_b);
    imshow("Hist_G", histImage_g);
    imshow("Hist_R", histImage_r);
}

Mat histequalize_g(Mat image, int h[]) {
    float cdf[256];
    int sum = 0;
    float temp = 0.0;
    for (int i = 0; i < 256; i++)
        sum += h[i];
    for (int i = 0; i < 256; i++) {
        cdf[i] = (1.0 * h[i]) / (sum * 1.0);
        cdf[i] += temp;
        temp = cdf[i];
    }
    int eq[256], df[256];
    for (int i = 0; i < 256; ++i) {
        eq[i] = 255 * cdf[i];
    }
    Mat histeq(image.rows, image.cols, CV_8UC1, 255);

    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            histeq.at<uchar>(i, j) = (uchar)eq[image.at<uchar>(i, j)];
        }
    }
    imshow("hello", histeq);
    return histeq;
}

Mat histequalize_c(Mat image, int h[]) {
    float cdf[256];
    int sum = 0;
    float temp = 0.0;
    for (int i = 0; i < 256; i++)
        sum += h[i];
    for (int i = 0; i < 256; i++) {
        cdf[i] = (1.0 * h[i]) / (sum * 1.0);
        cdf[i] += temp;
        temp = cdf[i];
    }
    int eq[256];
    for (int i = 0; i < 256; ++i) {
        eq[i] = 255 * cdf[i];
    }
    Mat histeq(image.rows, image.cols, CV_8UC3, 255);

    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            Vec3b color = image.at<Vec3b>(i, j);
            Vec3b & e_color = histeq.at<Vec3b>(i, j);
            e_color[0] = eq[color[0]];
            e_color[1] = eq[color[1]];
            e_color[2] = eq[color[2]];
        }
    }
    imshow("Equalized_Image", histeq);
    moveWindow("Equalized_Image", 40, 30);
    return histeq;
}

Mat histogram_matching(Mat src, Mat trg) {
    int src_hist[256];
    imhist_c(src, src_hist);

    float cdf[256];
    int sum = 0;
    float temp = 0.0;
    for (int i = 0; i < 256; i++)
        sum += src_hist[i];
    for (int i = 0; i < 256; i++) {
        cdf[i] = (1.0 * src_hist[i]) / (sum * 1.0);
        cdf[i] += temp;
        temp = cdf[i];
    }
    int src_eq[256];
    for (int i = 0; i < 256; ++i) {
        src_eq[i] = 255 * cdf[i];
    }

    int trg_hist[256];
    imhist_c(trg, trg_hist);

    float trg_cdf[256];
    sum = 0;
    temp = 0.0;
    for (int i = 0; i < 256; i++)
        sum += trg_hist[i];
    for (int i = 0; i < 256; i++) {
        trg_cdf[i] = (1.0 * trg_hist[i]) / (sum * 1.0);
        trg_cdf[i] += temp;
        temp = trg_cdf[i];
    }
    int trg_eq[256];
    for (int i = 0; i < 256; ++i) {
        trg_eq[i] = 255 * trg_cdf[i];
    }

    int min, min_index[256];
    for (int i = 0; i < 256; i++)
    {
        min = 255;
        for (int j = 0; j < 256; j++)
        {
            if (abs(src_eq[i] - trg_eq[j]) < min)
            {
                min = abs(src_eq[i] - trg_eq[j]);
                min_index[i] = j;
            }
        }
    }
    Mat Matched_Image(src.rows, src.cols, CV_8UC3, 255);
    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            Vec3b color = src.at<Vec3b>(i, j);
            Vec3b& e_color = Matched_Image.at<Vec3b>(i, j);
            e_color[0] = min_index[color[0]];
            e_color[1] = min_index[color[1]];
            e_color[2] = min_index[color[2]];
        }
    }
    imshow("Matched_Image", Matched_Image);
    moveWindow("Matched_Image", 40, 30);
    return Matched_Image;
}
