#include "imagecapturer.h"
#include <iostream>
#include <ctime>
#include <QCoreApplication>

// Include files to use the PYLON API.
#include <Base/GCString.h>
#ifdef PYLON_WIN_BUILD
#include <pylon/PylonGUI.h>
#endif

using namespace Pylon;
using namespace GenApi;
using namespace Basler_UsbCameraParams;
using namespace std;

// Constructors
ImageCapturer::ImageCapturer()
    : canDisplayImages(false), imageRetrieveTimeout(10000), numImagesToCapture(100), pixelFormat(PixelFormat_Mono12),
      exposureAuto(ExposureAuto_Continuous), exposureTime(20), gainAuto(GainAuto_Continuous), gain(16), gamma(1), fps(1000),
      offsetX(0), offsetY(0), width(2592), height(1944), filenamePrefix("Image"), imageNames(nullptr)
{
#ifdef PYLON_WIN_BUILD
    canDisplayImages = true;
#endif
}

ImageCapturer::ImageCapturer(int numImages, Basler_UsbCameraParams::PixelFormatEnums pf, Basler_UsbCameraParams::ExposureAutoEnums ea, double et,
                             Basler_UsbCameraParams::GainAutoEnums ga, double gn, double gamma, double fps, int64_t offX, int64_t offY, int64_t w, int64_t h,
                             string prefix, QString* imNames)
    : canDisplayImages(false), imageRetrieveTimeout(10000), numImagesToCapture(numImages), pixelFormat(pf), exposureAuto(ea),
      exposureTime(et), gainAuto(ga), gain(gn), gamma(gamma), fps(fps), offsetX(offX), offsetY(offY), width(w), height(h),
      filenamePrefix(prefix), imageNames(imNames)
{
#ifdef PYLON_WIN_BUILD
    canDisplayImages = true;
#endif
}

ImageCapturer::~ImageCapturer()
{}

void ImageCapturer::run()
{
    if (captureImages() < 0)
        emit deviceDisconnected();
}

int ImageCapturer::displayPreview()
{
    int retval = 0;

    Pylon::PylonAutoInitTerm autoInitTerm;
    try
    {
        CBaslerUsbInstantCamera camera(CTlFactory::GetInstance().CreateFirstDevice());
        camera.Open();
        applyCameraParameters(&camera);

        camera.StartGrabbing(numImagesToCapture);
        CGrabResultPtr captureResultPtr;
        CPylonImage currImage;

        while (camera.IsGrabbing())
        {
            camera.RetrieveResult(imageRetrieveTimeout, captureResultPtr, TimeoutHandling_ThrowException);

            if (captureResultPtr->GrabSucceeded())
            {
                // Display the captured image if possible.
                if (canDisplayImages)
                    Pylon::DisplayImage(1, captureResultPtr);
            }
            else
            {
                cerr << "Error: " << captureResultPtr->GetErrorCode() << " "
                     << captureResultPtr->GetErrorDescription() << endl;
            }
        }

        // Close the camera.
        camera.Close();
    }
    catch (GenICam::GenericException &e)
    {
        // Error handling
        cerr << "An exception occurred." << endl
             << e.GetDescription() << endl;
        retval = -1;
    }

    return retval;
}

int ImageCapturer::captureImages()
{
    int retval = 0;

    // Get the current time to place in the filenames
    time_t currentTime;
    struct tm* localTime;

    time(&currentTime);
    localTime = localtime(&currentTime);

    string second   = to_string(localTime->tm_sec);
    string minute   = to_string(localTime->tm_min);
    string hour     = to_string(localTime->tm_hour);
    string day      = to_string(localTime->tm_mday);
    string month    = to_string(localTime->tm_mon + 1);
    string year     = to_string(localTime->tm_year + 1900);
    string filenameTimeInfo = year + "-" + month + "-" + day + "-" + hour + "-" + minute + "-" + second;

    // Initialize Pylon runtime system
    Pylon::PylonAutoInitTerm autoInitTerm;

    try
    {
        // Create a Pylon instant camera object with the first camera device found.
        CBaslerUsbInstantCamera camera(CTlFactory::GetInstance().CreateFirstDevice());

        // Register the standard continuous acquisition configuration event handler.
        // camera.RegisterConfiguration(new CAcquireContinuousConfiguration, RegistrationMode_ReplaceAll, Cleanup_Delete);

        // Open the camera for accessing the parameters.
        camera.Open();
        applyCameraParameters(&camera);

        // printParams(); // TESTING

        // Start capturing images.
        camera.StartGrabbing(numImagesToCapture);

        // Smart pointer to receive the image data.
        CGrabResultPtr captureResultPtr;

        // Variable specifying how many images have been captured so far.
        int numImagesCaptured = 0;

        // To hold the current image.
        CPylonImage currImage;

        while (camera.IsGrabbing())
        {
            // Wait for image and then retrieve it. A timeout of 5000ms is used.
            camera.RetrieveResult(imageRetrieveTimeout, captureResultPtr, TimeoutHandling_ThrowException);
            numImagesCaptured++;

            // Check if the image was captured successfully.
            if (captureResultPtr->GrabSucceeded())
            {
                cout << camera.ResultingFrameRate.GetValue() << endl; // TESTING

                // Set the name of the file to hold the current image.
                QString currImagePath(QCoreApplication::applicationDirPath());
                string currImageNameStr = currImagePath.toStdString();
                currImageNameStr += "/Images/";
                currImageNameStr += filenamePrefix;
                currImageNameStr += "-";
                currImageNameStr += filenameTimeInfo;
                currImageNameStr += "-";
                currImageNameStr += to_string(fps);
                currImageNameStr += "fps";
                currImageNameStr += "-";
                currImageNameStr += to_string(numImagesCaptured);
                currImageNameStr += ".tiff";
                String_t currImageName((char*)currImageNameStr.c_str());

                // Add image name to imageName array if required
                if (imageNames)
                    imageNames[numImagesCaptured-1] = QString(currImageNameStr.c_str());

                // Save image to disk.
                currImage.AttachGrabResultBuffer(captureResultPtr);
                if (currImage.IsValid())
                    CImagePersistence::Save(ImageFileFormat_Tiff, currImageName, currImage);
                else
                    cerr << "Error: Invalid captured image." << endl;
            }
            // If the image was not succesffuly captured, output error message.
            else
            {
                cerr << "Error: " << captureResultPtr->GetErrorCode() << " "
                     << captureResultPtr->GetErrorDescription() << endl;
            }
        }

        // Close the camera.
        camera.Close();
    }
    catch (GenICam::GenericException &e)
    {
        // Error handling
        cerr << "An exception occurred." << endl
             << e.GetDescription() << endl;
        retval = -1;
    }

    return retval;
}

/*
int ImageCapturer::captureImagesWithPartition(string filenamePrefix)
{
    int retval= 0;

    Pylon::PylonAutoInitTerm autoInitTerm;
    try
    {
        CBaslerUsbInstantCamera camera(CTlFactory::GetInstance().CreateFirstDevice());
        camera.Open();
        camera.MaxNumBuffer.SetValue(numImagesToCapture);

        for (int y = 0; y < 3; y++)
        {
            for (int x = 0; x < 4; x++)
            {
                // Apply camera parameters
                camera.OffsetX.SetValue(648*x);
                camera.OffsetY.SetValue(648*y);
                camera.Width.SetValue(648);
                camera.Height.SetValue(648);
                camera.ExposureAuto.SetValue(exposureAuto);
                camera.ExposureTime.SetValue(exposureTime);
                camera.GainAuto.SetValue(gainAuto);
                camera.Gain.SetValue(gain);
                camera.Gamma.SetValue(gamma);
                camera.AcquisitionFrameRate.SetValue(fps);
                camera.PixelFormat.SetValue(pixelFormat);

                // Start capturing images.
                camera.StartGrabbing(numImagesToCapture + 1);
                CGrabResultPtr captureResultPtr;

                int numImagesCaptured = -1;
                CPylonImage currImage;

                while (camera.IsGrabbing())
                {
                    camera.RetrieveResult(imageRetrieveTimeout, captureResultPtr, TimeoutHandling_ThrowException);
                    numImagesCaptured++;

                    if (captureResultPtr->GrabSucceeded())
                    {
                        cout << x << "," << y << " " << camera.ResultingFrameRate.GetValue() << endl; // TESTING

                        if (numImagesCaptured > 0)
                        {
                            // Set the name of the file to hold the current image.
                            QString currImagePath(QCoreApplication::applicationDirPath());
                            string currImageNameStr = currImagePath.toStdString();
                            currImageNameStr += "/Images/";
                            currImageNameStr += filenamePrefix;
                            currImageNameStr += "-";
                            currImageNameStr += to_string(x);
                            currImageNameStr += ",";
                            currImageNameStr += to_string(y);
                            currImageNameStr += "-";
                            currImageNameStr += to_string(numImagesCaptured);
                            currImageNameStr += ".tiff";
                            String_t currImageName((char*)currImageNameStr.c_str());

                            // Save image to disk.
                            currImage.AttachGrabResultBuffer(captureResultPtr);
                            if (currImage.IsValid())
                                CImagePersistence::Save(ImageFileFormat_Tiff, currImageName, currImage);
                            else
                                cerr << "Error: Invalid captured image." << endl;
                        }
                    }
                    else
                    {
                        cerr << "Error: " << captureResultPtr->GetErrorCode() << " "
                             << captureResultPtr->GetErrorDescription() << endl;
                    }
                }
            }
        }

        camera.Close();
    }
    catch (GenICam::GenericException &e)
    {
        // Error handling
        cerr << "An exception occurred." << endl
             << e.GetDescription() << endl;
        retval = -1;
    }

    return retval;
}
*/

void ImageCapturer::applyCameraParameters(CBaslerUsbInstantCamera* camera)
{
    camera->MaxNumBuffer.SetValue(numImagesToCapture);
    camera->ExposureAuto.SetValue(exposureAuto);
    camera->ExposureTime.SetValue(exposureTime);
    camera->Gamma.SetValue(gamma);
    camera->AcquisitionFrameRate.SetValue(fps);
    camera->Width.SetValue(width);
    camera->Height.SetValue(height);
    camera->OffsetX.SetValue(offsetX);
    camera->OffsetY.SetValue(offsetY);
    camera->PixelFormat.SetValue(pixelFormat);
    camera->GainAuto.SetValue(gainAuto);
    camera->Gain.SetValue(gain);
}

void ImageCapturer::printParams() const
{
    cout << endl;
    cout << "Number of images to capture: " << numImagesToCapture << endl;
    cout << "Exposure auto: " << exposureAuto << endl;
    cout << "Exposure time: " << exposureTime << endl;
    cout << "Gain auto: " << gainAuto << endl;
    cout << "Gain: " << gain << endl;
    cout << "Gamma: " << gamma << endl;
    cout << "FPS: " << fps << endl;
    cout << "OffsetX: " << offsetX << endl;
    cout << "OffsetY: " << offsetY << endl;
    cout << "Width: " << width << endl;
    cout << "Height: " << height << endl;
}
