#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

struct COMPLEX{
    double real;
    double imag;
};


void displayFFT(COMPLEX** c, int rows, int columns ){
    Mat img_fft(rows,columns,CV_8UC1,Scalar(0));
    double mag;
    int i;
    int j;
    for(i=0;i<rows;i++){
        for(j=0;j<columns;j++){
            mag = sqrt(pow(c[i][j].real,2) + pow(c[i][j].imag,2));         
            img_fft.at<uchar>(i,j)=255 * mag;
        }
    }
   imshow("Filtered FFT", img_fft);


}
int Powerof2(int n,int *m,int *twopm)
{
   if (n <= 1) {
      *m = 0;
      *twopm = 1;
      return(false);
   }

   *m = 1;
   *twopm = 2;
   do {
      (*m)++;
      (*twopm) *= 2;
   } while (2*(*twopm) <= n);

   if (*twopm != n)
      return(false);
   else
      return(true);
}

int FFT(int dir,int m,double *x,double *y)
{
   long nn,i,i1,j,k,i2,l,l1,l2;
   double c1,c2,tx,ty,t1,t2,u1,u2,z;

   /* Calculate the number of points */
   nn = 1;
   for (i=0;i<m;i++)
      nn *= 2;

   /* Do the bit reversal */
   i2 = nn >> 1;
   j = 0;
   for (i=0;i<nn-1;i++) {
      if (i < j) {
         tx = x[i];
         ty = y[i];
         x[i] = x[j];
         y[i] = y[j];
         x[j] = tx;
         y[j] = ty;
      }
      k = i2;
      while (k <= j) {
         j -= k;
         k >>= 1;
      }
      j += k;
   }

   /* Compute the FFT */
   c1 = -1.0;
   c2 = 0.0;
   l2 = 1;
   for (l=0;l<m;l++) {
      l1 = l2;
      l2 <<= 1;
      u1 = 1.0;
      u2 = 0.0;
      for (j=0;j<l1;j++) {
         for (i=j;i<nn;i+=l2) {
            i1 = i + l1;
            t1 = u1 * x[i1] - u2 * y[i1];
            t2 = u1 * y[i1] + u2 * x[i1];
            x[i1] = x[i] - t1;
            y[i1] = y[i] - t2;
            x[i] += t1;
            y[i] += t2;
         }
         z =  u1 * c1 - u2 * c2;
         u2 = u1 * c2 + u2 * c1;
         u1 = z;
      }
      c2 = sqrt((1.0 - c1) / 2.0);
      if (dir == 1)
         c2 = -c2;
      c1 = sqrt((1.0 + c1) / 2.0);
   }

   /* Scaling for forward transform */
   if (dir == 1) {
      for (i=0;i<nn;i++) {
         x[i] /= (double)nn;
         y[i] /= (double)nn;
      }
   }

   return(true);
}

int FFT2D(COMPLEX **c,int nx,int ny,int dir)
{
   int i,j;
   int m,twopm;
   double *real,*imag;

   /* Transform the rows */
   real = (double *)malloc(nx * sizeof(double));
   imag = (double *)malloc(nx * sizeof(double));
   if (real == NULL || imag == NULL)
      return(false);
   if (!Powerof2(nx,&m,&twopm) || twopm != nx)
      return(false);
   for (j=0;j<ny;j++) {
      for (i=0;i<nx;i++) {
         real[i] = c[i][j].real;
         imag[i] = c[i][j].imag;
      }
      FFT(dir,m,real,imag);
      for (i=0;i<nx;i++) {
         c[i][j].real = real[i];
         c[i][j].imag = imag[i];
      }
   }
   free(real);
   free(imag);

   /* Transform the columns */
   real = (double *)malloc(ny * sizeof(double));
   imag = (double *)malloc(ny * sizeof(double));
   if (real == NULL || imag == NULL)
      return(false);
   if (!Powerof2(ny,&m,&twopm) || twopm != ny)
      return(false);
   for (i=0;i<nx;i++) {
      for (j=0;j<ny;j++) {
         real[j] = c[i][j].real;
         imag[j] = c[i][j].imag;
      }
      FFT(dir,m,real,imag);
      for (j=0;j<ny;j++) {
         c[i][j].real = real[j];
         c[i][j].imag = imag[j];
      }
   }
   free(real);
   free(imag);

   return(true);
}

COMPLEX** showfft(COMPLEX **c, int rows, int columns){
    double maxi = 0;
    double mini = 999;
    double mag;
    int i,j;

    Mat img_fft(rows,columns,CV_8UC1,Scalar(0));
    COMPLEX quadrant_flip1[rows][columns];
   
    for(i=0;i<rows;i++){
        for(j=0;j<columns;j++){
            mag = sqrt(pow(c[i][j].real,2) + pow(c[i][j].imag,2));
            if (maxi < mag){
                maxi = mag;
            }
            if (mini> mag){
                mini = mag;
            }
            if (j<columns/2 ){
                quadrant_flip1[i][j+columns/2].real = c[i][j].real;
                quadrant_flip1[i][j+columns/2].imag = c[i][j].imag;
            }
            else{
                quadrant_flip1[i][j-columns/2].real = c[i][j].real;
                quadrant_flip1[i][j-columns/2].imag = c[i][j].imag;
            }
        }
    }
    cout<<rows<<" "<<columns<<endl; 
    COMPLEX **quadrant_flip= new COMPLEX*[rows];
    for(i=0;i<rows;i++){
        quadrant_flip[i] = new COMPLEX[columns];
    }

    
    for(i=0;i<rows;i++){
        for(j=0;j<columns;j++){

            if (i<rows/2 ){
               quadrant_flip[i+rows/2][j].real = quadrant_flip1[i][j].real;
               quadrant_flip[i+rows/2][j].imag = quadrant_flip1[i][j].imag;
            }
            else{

                quadrant_flip[i-rows/2][j].real = quadrant_flip1[i][j].real;
               quadrant_flip[i-rows/2][j].imag = quadrant_flip1[i][j].imag;
            }

        }
    }

    for(i=0;i<rows;i++){
        for(j=0;j<columns;j++){
        mag = sqrt(pow(quadrant_flip[i][j].real,2) + pow(quadrant_flip[i][j].imag,2));         
        img_fft.at<uchar>(i,j)=255 * mag;
        }
    }

    cout << maxi << " "<< mini<< endl;
   imshow("FFT of the image", img_fft);
   return quadrant_flip;
}

void lpf(COMPLEX **c,int rows, int columns,int r){
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            if(pow(i-rows/2,2)+pow(j-columns/2,2)<= (r*r)){

            }
            else{
                c[i][j].real=0;
                c[i][j].imag=0;
            }
        }
    }
}

void hpf(COMPLEX **c,int rows, int columns,int r){
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            if(pow(i-rows/2,2)+pow(j-columns/2,2)>= (r*r)){

            }
            else{
                c[i][j].real=0;
                c[i][j].imag=0;
            }
        }
    }
}

void gaussian_lpf(COMPLEX **c,int rows, int columns,double variance){
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            double power = -0.5 * (pow( (i-rows/2)/variance, 2.0 ) + pow( (j-columns/2)/variance, 2.0 ));
            c[i][j].imag *=exp(power);
            c[i][j].real *=exp(power);
        }
    }
}

int main(){
    Mat img = imread("Input_Images/Lena_gray_512.jpg",0);
    imshow("Sample Image",img);
    int columns = img.cols;
    int rows = img.rows;
    int i,j;

    COMPLEX** complex_img = (COMPLEX**)malloc(rows * sizeof(COMPLEX));
    for(i=0;i<rows;i++){
        complex_img[i] = (COMPLEX*)malloc(columns * sizeof(COMPLEX));
    }

    for (i=0;i<rows;i++){
        for(j=0;j<columns;j++){
            complex_img[i][j].real = (double)(img.at<uchar>(i,j));
            complex_img[i][j].imag = 0;
        }
    }

    FFT2D(complex_img,rows,columns,1); //forward transform
    COMPLEX** quadrant = showfft(complex_img, rows,columns);
    //displayFFT(quadrant,rows,columns);
    //lpf(quadrant, rows,columns,50);
    gaussian_lpf(quadrant,rows,columns,20);
    //hpf(quadrant, rows,columns,50);
    displayFFT(quadrant,rows,columns);
    COMPLEX **quadrant_flip= new COMPLEX*[rows];
    for(i=0;i<rows;i++){
        quadrant_flip[i] = new COMPLEX[columns];
    }
    COMPLEX **quadrant_flip1= new COMPLEX*[rows];
    for(i=0;i<rows;i++){
        quadrant_flip1[i] = new COMPLEX[columns];
    }
    for(i=0;i<rows;i++){
        for(j=0;j<columns;j++){
            if (j<columns/2 ){
                quadrant_flip1[i][j+columns/2].real = quadrant[i][j].real;
                quadrant_flip1[i][j+columns/2].imag = quadrant[i][j].imag;
            }
            else{
                quadrant_flip1[i][j-columns/2].real = quadrant[i][j].real;
                quadrant_flip1[i][j-columns/2].imag = quadrant[i][j].imag;
            }
        }
    }


    for(i=0;i<rows;i++){
        for(j=0;j<columns;j++){

            if (i<rows/2 ){
               quadrant_flip[i+rows/2][j].real = quadrant_flip1[i][j].real;
               quadrant_flip[i+rows/2][j].imag = quadrant_flip1[i][j].imag;
            }
            else{

                quadrant_flip[i-rows/2][j].real = quadrant_flip1[i][j].real;
               quadrant_flip[i-rows/2][j].imag = quadrant_flip1[i][j].imag;
            }

        }
    }
    displayFFT(quadrant_flip,rows,columns);
    FFT2D(quadrant_flip,rows,columns,-1);

    Mat filtered_image(rows,columns,CV_8UC1,Scalar(0));

    for(i=0;i<rows;i++){
        for(j=0;j<columns;j++){
            filtered_image.at<uchar>(i,j) = quadrant_flip[i][j].real;
        }
    }
    imshow("Filtered Image",filtered_image);
    waitKey(0);
    return 0;
}