/* BackPropagationMethod.cpp
   Methods that related to backpropagation
   author: Michael Wu, "Raymond" Yan-Lok Chan
 */

#include "backpropagationmethod.h"
//#include <tchar.h>

#include <cmath>
#include <iostream>
#include <fstream>

//#include <stdlib.h>
//#include <stdio.h>

using namespace cv;

//perform FFT to matrix
fftwf_complex *FFT(Mat mat)
{
    /*Allocate input and output arrays for FFT*/
    fftwf_complex *in = (fftwf_complex*) fftwf_malloc(sizeof(fftwf_complex) * mat.size().area());
    fftwf_complex *out = (fftwf_complex*) fftwf_malloc(sizeof(fftwf_complex) * mat.size().area());

    /*Create plan for FFT */
    fftwf_plan plan = fftwf_plan_dft_2d(mat.size().height, mat.size().width, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    /*Load data from original image (imgFT) into the input data (in) - row major order*/
    int k = 0;
    float* p;
    Size matsize = mat.size();
    for(int i = 0; i < matsize.height ; i++) {
        p = mat.ptr<float>(i);
        for(int j = 0 ; j < matsize.width ; j++) {
            in[k][0] = p[j];
            in[k][1] = 0.0;
            k++;
        }
    }

    /*Execute the plan to get the FFT of the image*/
    fftwf_execute(plan);


    /*Destroy Plan and Free memory allocated to input array*/
    fftwf_destroy_plan(plan);
    fftwf_free(in);

    /*return output of the FFT*/
    return(out);
}

//perform FFT to matrix(complex plane)
fftwf_complex *FFT(fftwf_complex * in, int w, int h)
{
    /*Declarations*/

    /*Allocate input and output arrays for FFT*/
    fftwf_complex *out = (fftwf_complex*) fftwf_malloc(sizeof(fftwf_complex) * w*h);

    /*Create plan for FFT */
    fftwf_plan plan = fftwf_plan_dft_2d(h, w, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    /*Load data from original image (imgFT) into the input data (in) - row major order*/

    /*Execute the plan to get the FFT of the image*/
    fftwf_execute(plan);

    /*Destroy Plan and Free memory allocated to input array*/
    fftwf_destroy_plan(plan);
    fftwf_free(in);

    /*return output of the FFT*/
    return(out);
}

//simple threshold
float heaviside(float input)
{
    if(input < 0)
        return 0;
    else if(input > 0)
        return 1;
    else
        return 0.5;
}

//caluclate backpropagation transfer function
void calcTF(fftwf_complex* tfp, const int &h, const int &w, double lambda, const double &z, const double &dz)
{
    float fsdh, fsdw;
    float fs = (float)(1/dz), temp, mag;
    int i, j;
    float x , y;

    // Load fftr into image
    fsdw = fs/(w-1);
    fsdh = fs/(h-1);
    lambda = 1/(lambda*lambda);

    // For top left corner:
    for( i = 0, x = fs/2*(-1+float(h)/(h-1)); i*2< h; i++, x += fsdh)    {
        for( j = 0, y = fs/2*(-1+float(w)/(w-1)); j*2< w; j++, y += fsdw)    {
            temp = float(lambda - x*x - y*y);
            if (temp < 0)    {
                mag = float(sqrt(-temp) * 6.283185307179586 * z);
                tfp[i*w+j][0] = exp(mag * heaviside(temp)) - heaviside(-temp);
                tfp[i*w+j][1] = 0;
            }
            else {
                mag = float(sqrt(temp) * 6.28318530717958 * -z);
                tfp[i*w+j][0] = cosf(mag * heaviside(temp)) - heaviside(-temp);
                tfp[i*w+j][1] = sinf(mag);
            }
        }
    }

    // For top right corner:
    for( i = 0, x = float(fs/2*(-1+double(h)/(h-1))); i< h/2; i++, x += fsdh)    {
        for( j = w/2, y = -fs/2; j< w; j++, y += fsdw)    {
            temp = float(lambda - x*x - y*y);
            if (temp < 0)    {
                mag = float(sqrt(-temp) * 6.283185307179586 * z);
                tfp[i*w+j][0] = exp(mag * heaviside(temp)) - heaviside(-temp);
                tfp[i*w+j][1] = 0;
            }
            else {
                mag = float(sqrt(temp) * 6.28318530717958 * -z);
                tfp[i*w+j][0] = cosf(mag * heaviside(temp)) - heaviside(-temp);
                tfp[i*w+j][1] = sinf(mag);
            }
        }
    }

    // For bottom left corner:
    for( i = h/2, x = -fs/2; i< h; i++, x += fsdh)    {
        for( j = 0, y = float(fs/2*(-1+double(w)/(w-1))); j< w/2; j++, y += fsdw)    {
            temp = float(lambda - x*x - y*y);
            if (temp < 0)    {
                mag = float(sqrt(-temp) * 6.283185307179586 * z);
                tfp[i*w+j][0] = exp(mag * heaviside(temp)) - heaviside(-temp);
                tfp[i*w+j][1] = 0;
            }
            else {
                mag = float(sqrt(temp) * 6.28318530717958 * -z);
                tfp[i*w+j][0] = cosf(mag * heaviside(temp)) - heaviside(-temp);
                tfp[i*w+j][1] = sinf(mag);
            }
        }
    }

    // For bottom right corner:
    for( i = h/2, x = -fs/2; i< h; i++, x += fsdh)    {
        for( j = w/2, y = -fs/2; j< w; j++, y += fsdw)    {
            temp = float(lambda - x*x - y*y);
            if (temp < 0)    {
                mag = float(sqrt(-temp) * 6.283185307179586 * z);
                tfp[i*w+j][0] = exp(mag * heaviside(temp)) - heaviside(-temp);
                tfp[i*w+j][1] = 0;
            }
            else {
                mag = float(sqrt(temp) * 6.28318530717958 * -z);
                tfp[i*w+j][0] = cosf(mag * heaviside(temp)) - heaviside(-temp);
                tfp[i*w+j][1] = sinf(mag);
            }
        }
    }
    return;
}

//create backpropagation transfer function
fftwf_complex *transferFunction(int w, int h, int area, double distance, double pixelSize, double wavelength){
    /*Declarations*/

    /*Calculation for parameters*/
    /*refIndex = 1.5*/
    const double refIndex = 1.5;
    /*lamda = 300nm*/
    const double lamda = (wavelength/(refIndex));
    /*Sample Frequency*/
    fftwf_complex *transFunc = (fftwf_complex*) fftwf_malloc(sizeof(fftwf_complex) * area);
    calcTF(transFunc, h, w, lamda, distance, pixelSize);
    return transFunc;
}

//complex multipy
fftwf_complex *complexMult(fftwf_complex *fft, fftwf_complex *transFunc, int area){
    /*Allocate array for the output*/
    fftwf_complex *output = (fftwf_complex*) fftwf_malloc(sizeof(fftwf_complex) * area);

    /*Multiplication*/
    for(int k = 0; k < area; k++)
    {
        output[k][0] = (fft[k][0] * transFunc[k][0]) - (fft[k][1] * transFunc[k][1]);
        output[k][1] = (fft[k][0] * transFunc[k][1]) + (fft[k][1] * transFunc[k][0]);
    }

    /*Return the product of the two complex arrays*/
    return(output);
}

//complex conjugate multipy
fftwf_complex *conjcomplexMult(fftwf_complex *fft, fftwf_complex *transFunc, int area){
    /*Allocate array for the output*/
    fftwf_complex *output = (fftwf_complex*) fftwf_malloc(sizeof(fftwf_complex) * area);

    /*Multiplication*/
    for(int k = 0; k < area; k++){
        output[k][0] = (fft[k][0] * transFunc[k][0]) + (fft[k][1] * transFunc[k][1]);
        output[k][1] = (-fft[k][0] * transFunc[k][1]) + (fft[k][1] * transFunc[k][0]);
    }

    /*Return the product of the two complex arrays*/
    return(output);
}

//generate output amplitude
Mat outputImg(int w, int h, fftwf_complex *in){
    /*Declarations*/
    int k = 0;
    float* p;
     /* Allocate array for storing magnitude*/
    Mat magnMatrix = Mat::zeros(h, w, CV_32F);

    /*Find Magnitude and input to magnMatrix*/
    for(int i = 0; i < h ; i++) {
        p = magnMatrix.ptr<float>(i);
        for(int j = 0 ; j < w ; j++) {
            p[j] = (float)sqrt(in[k][0]*in[k][0] + in[k][1]*in[k][1]);
            //p[j] = (float)in[k][0];
            k++;
        }
    }
    /*Normalize (0 to 1)*/
    magnMatrix = normalizeMat(magnMatrix, 1.0);

    /*Returns the Image as final output*/
    return(magnMatrix*255);
}

//generate output phase
Mat outputImgPhase(int w, int h, fftwf_complex *in)
{
    int k = 0;
    float sumReal = 0;
    float sumImg = 0;
    float* p;
     /* Allocate array for storing magnitude*/
    Mat phaseMatrix = Mat::zeros(h, w, CV_32F);
    for(int i = 0; i < h ; i++) {
        for(int j = 0 ; j < w ; j++) {
            sumReal += in[k][0];
            sumImg += in[k][1];
            k++;
        }
    }
    sumReal = sumReal / (w*h);
    sumImg = sumImg / (w*h);
    float denominator = sumReal*sumReal + sumImg*sumImg;
    k = 0;
    for(int i = 0; i < h ; i++) {
        p = phaseMatrix.ptr<float>(i);
        for(int j = 0 ; j < w ; j++) {
            float tempReal = (in[k][0]*sumReal + in[k][1]*sumImg) / denominator;
            float tempImg = (in[k][0]*-1*sumImg + in[k][1]*sumReal) / denominator;
            p[j] = atan2(tempImg, tempReal);
            k++;
        }
    }
    /*Normalize (0 to 1)*/
    phaseMatrix = normalizeMat(phaseMatrix, 1.0);

    /*Returns the Image as final output*/
    return(phaseMatrix*255);
}

//perform invert fft to input
fftwf_complex *IFFT(int w, int h, int area, fftwf_complex *finalIn){
    /* Allocate output array for IFFT (one unnormalized, one normalized)*/
    fftwf_complex *out = (fftwf_complex*) fftwf_malloc(sizeof(fftwf_complex) * area);

    /*create plan for IFFT*/
    fftwf_plan invPlan = fftwf_plan_dft_2d(h, w, finalIn, out, FFTW_BACKWARD, FFTW_ESTIMATE);

    /*IFFT*/
    fftwf_execute(invPlan);
    /*Destroy Plan and Free memory allocated to input array*/
    fftwf_destroy_plan(invPlan);
    fftwf_free(finalIn);

    /*return output after inverse fourier transform*/
    return(out);
}

//perform backpropagation to matrix
fftwf_complex *backPropagation(Mat mat, double distance, double pixelSize, double wavelength){
    Size size = mat.size();
    int width = size.width;
    int height = size.height;
    int area = size.area();

    /*Create Transfer Function using given Parameters*/
    fftwf_complex *transFunc = transferFunction(width, height, area, distance, pixelSize, wavelength);

    //Mat tf = outputImg(width, height, transFunc);
    //imwrite("tf.bmp", tf);

    fftwf_complex *fft, *finalIn, *outFinal;
    Mat outImage = mat;

    /*Perform FFT function and return output*/
    fft = FFT(outImage);

    /*multiply fft image with Transfer function after it has been put through iffShift*/
    finalIn = complexMult(fft, transFunc, area);

    /*Inverse Fourier Transform*/
    outFinal = IFFT(width, height, area, finalIn);

    fftwf_free(transFunc);
    fftwf_free(fft);

    /*Return the Image after it has been Back Propagated*/
    return(outFinal);
}

//perform backpropagation to image and generate output amplitude and phase
void BPTheImage(string inputPicturePath, string outputPicturePath, string outputPhasePicturePath, double distance, double pixelSize, double wavelength) {

    /*import image*/
    Mat mat = cv::imread(inputPicturePath, CV_LOAD_IMAGE_GRAYSCALE);

    mat.convertTo(mat, CV_32F);
    //mat = normalizeMat(mat, 1.0);
    mat = mat/255;
    std::cout <<  mat.at<float>(0,0);
    for(int i = 0; i < mat.size().height; i++)
        for(int j = 0; j < mat.size().width; j++)
            if(mat.ptr<float>(i)[j] < 0)
                std::cout << mat.ptr<float>(i)[j] << std::endl;

    /*Run back Propagation Function*/
    //distance: units are in um
    distance = distance / (1000000);
    //Pixel Size: units are in um
    pixelSize = pixelSize / (1000000);
    //Wavelength: units are in nm
    wavelength = wavelength / (1000000000);

    Size size = mat.size();
    int width = size.width;
    int height = size.height;

    fftwf_complex *outFinal = backPropagation(mat, distance, pixelSize, wavelength);

    /*Output Image*/
    Mat backPropImg = outputImg(width, height, outFinal);
    backPropImg.convertTo(backPropImg,CV_8U);

    Mat backPropImgPhase = outputImgPhase(width, height, outFinal);
    backPropImgPhase.convertTo(backPropImgPhase,CV_8U);

    imwrite(outputPicturePath, backPropImg);
    imwrite(outputPhasePicturePath, backPropImgPhase);

    fftwf_free(outFinal);

    return;
}

//crop image with correspoding ROI
void cropTheImage(string in, string out, int x, int y, int width, int height) {
    // use your string
    Mat matImage = imread(in);
    imwrite(out, matImage(Rect(x, y, width, height )) );
}

//normalize matrix base on min and max
Mat normalizeMat(Mat mat, float max)
{
    double minVal;
    double maxVal;
    minMaxLoc( mat, &minVal, &maxVal);
    for(int i = 0; i < mat.size().height; i++)
        for(int j = 0; j < mat.size().width; j++)
            mat.ptr<float>(i)[j] = (float)(max* (mat.ptr<float>(i)[j] - minVal) / (maxVal - minVal));
    return mat;
}
