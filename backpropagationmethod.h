#ifndef BACKPROPAGATIONMETHOD_H
#define BACKPROPAGATIONMETHOD_H

#include <string>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <fftw3.h>

/*Function performs the FFT of an Image*/
fftwf_complex *FFT(cv::Mat mat);

fftwf_complex *FFT(fftwf_complex * in, int w, int h);

void calcTF(fftwf_complex* tfp, const int &h, const int &w, double lambda, const double &z, const double &dz);

/*Function creates the Back Propagation Transfer Function*/
fftwf_complex *transferFunction(int w, int h, int area, double distance, double pixelSize, double wavelength);

/*multiply two complex arrays (transfer function and the image in frequency domain)*/
fftwf_complex *complexMult(fftwf_complex *fft, fftwf_complex *transFunc, int area);

fftwf_complex *conjcomplexMult(fftwf_complex *fft, fftwf_complex *transFunc, int area);

/*Function performs iffShift*/
/*four cases: odd/odd, even/even, odd/even, even/odd*/
fftwf_complex *ifftshift(int w, int h, int area, fftwf_complex *in);

/*Function will normalize the Image*/
cv::Mat outputImg(int w, int h, fftwf_complex *in);

/*inverse fourier transform*/
fftwf_complex *IFFT(int w, int h, int area, fftwf_complex *finalIn);

fftwf_complex *backPropagation(cv::Mat mat, double distance, double pixelSize, double wavelength);

void BPTheImage(std::string input, std::string output, std::string outputPhase, double distance, double pixelSize, double wavelength);

void cropTheImage(std::string in, std::string out, int x, int y, int width, int height);

cv::Mat normalizeMat(cv::Mat mat, float max);

#endif // BACKPROPAGATIONMETHOD_H
