#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

struct COMPLEX{
    double real;
    double imag;
};

void displayFFT(COMPLEX** c, int rows, int columns , string fft_name){
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
   imshow(fft_name, img_fft);


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

COMPLEX** reorganise_quadrant(COMPLEX **c, int rows, int columns){
    int i,j;

    Mat img_fft(rows,columns,CV_8UC1,Scalar(0));
    COMPLEX quadrant_flip1[rows][columns];
   
    for(i=0;i<rows;i++){
        for(j=0;j<columns;j++){
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
    return quadrant_flip;
}

COMPLEX** lpf(COMPLEX **c, int rows, int columns,int r){
    COMPLEX** filtered = (COMPLEX**)malloc(rows * sizeof(COMPLEX));
    for(int i=0;i<rows;i++){
        filtered[i] = (COMPLEX*)malloc(columns * sizeof(COMPLEX));
    }
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            if(pow(i-rows/2,2)+pow(j-columns/2,2)<= (r*r)){
                filtered[i][j] = c[i][j];
            }
            else{
                filtered[i][j].real=0;
                filtered[i][j].imag=0;
            }
        }
    }
    return filtered;
}

COMPLEX** hpf(COMPLEX **c, int rows, int columns,int r){
    COMPLEX** filtered = (COMPLEX**)malloc(rows * sizeof(COMPLEX));
    for(int i=0;i<rows;i++){
        filtered[i] = (COMPLEX*)malloc(columns * sizeof(COMPLEX));
    }
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            if(pow(i-rows/2,2)+pow(j-columns/2,2)>= (r*r)){
                filtered[i][j] = c[i][j];
            }
            else{
                filtered[i][j].real=0;
                filtered[i][j].imag=0;
            }
        }
    }
    return filtered;
}

COMPLEX** gaussian_lpf(COMPLEX **c, int rows, int columns,double variance){
    COMPLEX** filtered = (COMPLEX**)malloc(rows * sizeof(COMPLEX));
    for(int i=0;i<rows;i++){
        filtered[i] = (COMPLEX*)malloc(columns * sizeof(COMPLEX));
    }

    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            double power = -0.5 * (pow( (i-rows/2)/variance, 2.0 ) + pow( (j-columns/2)/variance, 2.0 ));
            filtered[i][j].imag =c[i][j].imag*exp(power);
            filtered[i][j].real =c[i][j].real*exp(power);
        }
    }
    return filtered;
}

COMPLEX** gaussian_hpf(COMPLEX **c, int rows, int columns,double variance){
    COMPLEX** filtered = (COMPLEX**)malloc(rows * sizeof(COMPLEX));
    for(int i=0;i<rows;i++){
        filtered[i] = (COMPLEX*)malloc(columns * sizeof(COMPLEX));
    }

    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            double power = -0.5 * (pow( (i-rows/2)/variance, 2.0 ) + pow( (j-columns/2)/variance, 2.0 ));
            filtered[i][j].imag =c[i][j].imag*(1-exp(power));
            filtered[i][j].real =c[i][j].real*(1-exp(power));
        }
    }
    return filtered;
}

COMPLEX** butterworth_lpf(COMPLEX **c, int rows, int columns, double cutoff){
    COMPLEX** filtered = (COMPLEX**)malloc(rows * sizeof(COMPLEX));
    for(int i=0;i<rows;i++){
        filtered[i] = (COMPLEX*)malloc(columns * sizeof(COMPLEX));
    }
    int omega;
    for(int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++)
        {
            omega = sqrt(i*i + j*j);
            filtered[i][j].real = (cutoff*cutoff*c[i][j].real+omega*cutoff*c[i][j].imag)/(cutoff*cutoff+omega*omega);
            filtered[i][j].imag = (cutoff*cutoff*c[i][j].imag-omega*cutoff*c[i][j].real)/(cutoff*cutoff+omega*omega);
        }
    }
    return filtered;
}

COMPLEX** butterworth_hpf(COMPLEX **c, int rows, int columns,double cutoff){
    COMPLEX** filtered = (COMPLEX**)malloc(rows * sizeof(COMPLEX));
    for(int i=0;i<rows;i++){
        filtered[i] = (COMPLEX*)malloc(columns * sizeof(COMPLEX));
    }
    int omega;
    for(int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++)
        {
            omega = sqrt(i*i + j*j);
            filtered[i][j].real = (cutoff*cutoff*c[i][j].real + omega*cutoff*c[i][j].imag - omega*omega*c[i][j].imag)/(cutoff*cutoff + 2*omega*omega + 2*omega*cutoff);
            filtered[i][j].imag = (cutoff*cutoff*c[i][j].imag - omega*cutoff*c[i][j].real - omega*omega*c[i][j].real)/(cutoff*cutoff + 2*omega*omega + 2*omega*cutoff);
        }
    }
    return filtered;
}

int main(){
    string src;
    cout << "Enter the image name with the extention: ";
    cin >> src;
    Mat img = imread("Input_Images/"+src,0);
    imshow("Sample Image",img);
    int columns = img.cols;
    int rows = img.rows;
    int i,j;

    // Saving the image into a complex image (START)
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
    // Saving the image into a complex image (END)

    FFT2D(complex_img,rows,columns,1); 
    displayFFT(complex_img,rows,columns,"Raw FFT");

    //show the FFT of the original Image (START)
    COMPLEX** img_fft = reorganise_quadrant(complex_img, rows, columns); 
    displayFFT(img_fft,rows,columns,"Image FFT");
    //show the FFT of the original Image (END)

    // Filter and show the FFT (START)
    int filter_no;
    int radius;
    int variance;
    int cutoff;
    COMPLEX** filtered_img;
    cout << "Enter the number corrsponding to the following filters:"<< endl;
    cout <<"1. Low-Pass Filter(Ideal)"<<endl;
    cout <<"2. High-Pass Filter(Ideal)"<<endl;
    cout <<"3. Gaussian Low-Pass Filter"<<endl;
    cout <<"4. Gaussian High-Pass Filter"<<endl;
    cout <<"5. Butterworth Low-Pass Filter"<<endl;
    cout <<"6. Butterworth High-Pass Filter"<<endl;
    cin >> filter_no;
    switch(filter_no){
    case 1:
        cout << "Enter the radius of the LPF: ";
        cin >> radius;
        filtered_img = lpf(img_fft,rows,columns,radius);
        displayFFT(filtered_img,rows,columns,"LPF Filtered FFT");
        break;
    case 2:
        cout << "Enter the radius of the HPF: ";
        cin >> radius;
        filtered_img = hpf(img_fft,rows,columns,radius);
        displayFFT(filtered_img,rows,columns,"HPF Filtered FFT");
        break;
    case 3:
        cout << "Enter the variance of the Gaussian-LPF: ";
        cin >> variance;
        filtered_img = gaussian_lpf(img_fft,rows,columns,variance);
        displayFFT(filtered_img,rows,columns,"Gaussian LPF Filtered FFT");
        break;
    case 4:
        cout << "Enter the variance of the Gaussian-HPF: ";
        cin >> variance;
        filtered_img = gaussian_hpf(img_fft,rows,columns,variance);
        displayFFT(filtered_img,rows,columns,"Gaussian HPF Filtered FFT");
        break;
    case 5:
        cout << "Enter the cutoff of the Butterworth-LPF: ";
        cin >> cutoff;
        filtered_img = butterworth_lpf(img_fft,rows,columns,cutoff);
        displayFFT(filtered_img,rows,columns,"Butterworth LPF Filtered FFT");
        break;
    case 6:
        cout << "Enter the cutoff of the Butterworth-HPF: ";
        cin >> cutoff;
        filtered_img = butterworth_hpf(img_fft,rows,columns,cutoff);
        displayFFT(filtered_img,rows,columns,"Butterworth HPF Filtered FFT");
        break;
    default:
        cout << "Invalid filter number"<< endl;
        return 0;
    }
    // Filter and show the FFT (END)

    // Show the Raw filtered FFT (START)
    COMPLEX** raw_filtered_fft = reorganise_quadrant(filtered_img, rows,columns);
    displayFFT(raw_filtered_fft,rows,columns,"Raw Filtered FFT");
    // Show the Raw filtered FFT (END)

    FFT2D(raw_filtered_fft,rows,columns,-1);

    //Show the Filtered image (START)
    Mat filtered_image(rows,columns,CV_8UC1,Scalar(0));
    for(i=0;i<rows;i++){
        for(j=0;j<columns;j++){
            filtered_image.at<uchar>(i,j) = raw_filtered_fft[i][j].real;
        }
    }
    imshow("Filtered Image",filtered_image);
    //Show the Filtered image (END)

    waitKey(0);
    return 0;
}