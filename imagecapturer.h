#ifndef IMAGECAPTURER
#define IMAGECAPTURER

#include <string>
#include <QString>
#include <cstdint>
#include <pylon/PylonIncludes.h>
#include <pylon/usb/BaslerUsbInstantCamera.h>

#include <QThread>

class ImageCapturer : public QThread
{
    Q_OBJECT

public:
    ImageCapturer();
    ImageCapturer(int numImages, Basler_UsbCameraParams::PixelFormatEnums pf, Basler_UsbCameraParams::ExposureAutoEnums ea, double et,
                  Basler_UsbCameraParams::GainAutoEnums ga, double gn, double gamma, double fps, int64_t offX, int64_t offY, int64_t w, int64_t h,
                  std::string prefix, QString* imNames);
    ~ImageCapturer();

    // function called when thread started
    void run();

    // Getters
    int getNumImagesToCapture() const { return numImagesToCapture; }
    Basler_UsbCameraParams::PixelFormatEnums getPixelFormat() const { return pixelFormat; }
    Basler_UsbCameraParams::ExposureAutoEnums getExposureAuto() const { return exposureAuto; }
    double getExposureTime() const { return exposureTime; }
    double getGamma() const { return gamma; }
    double getFps() const { return fps; }
    int64_t getOffsetX() const { return offsetX; }
    int64_t getOffsetY() const { return offsetY; }
    int64_t getWidth() const { return width; }
    int64_t getHeight() const { return height; }

    // Setters
    void setNumImagesToCapture(int num) { numImagesToCapture = num; }
    void setPixelFormat(Basler_UsbCameraParams::PixelFormatEnums pf) { pixelFormat = pf; }
    void setExposureAuto(Basler_UsbCameraParams::ExposureAutoEnums ea) { exposureAuto = ea; }
    void setExposureTime(double et) { exposureTime = et; }
    void setGainAuto(Basler_UsbCameraParams::GainAutoEnums ga) { gainAuto = ga; }
    void setGain(double g) { gain = g; }
    void setGamma(double gamma) { this->gamma = gamma; }
    void setFps(double fps) { this->fps = fps; }
    void setOffsetX(int x) { offsetX = x; }
    void setOffsetY(int y) { offsetY = y; }
    void setWidth(int w) { width = w; }
    void setHeight(int h) { height = h; }
    void setFilenamePrefix(std::string prefix) { filenamePrefix = prefix; }
    void setImageNames(QString* imNames) { imageNames = imNames; }

private:
    void applyCameraParameters(Pylon::CBaslerUsbInstantCamera* camera);

    bool canDisplayImages;
    int imageRetrieveTimeout;

    // Camera parameters
    int numImagesToCapture;

    Basler_UsbCameraParams::PixelFormatEnums pixelFormat;
    Basler_UsbCameraParams::ExposureAutoEnums exposureAuto;
    Basler_UsbCameraParams::GainAutoEnums gainAuto;
    double exposureTime;
    double gain;

    double gamma;
    double fps;
    int64_t offsetX;
    int64_t offsetY;
    int64_t width;
    int64_t height;

    std::string filenamePrefix;
    QString* imageNames;

    // Image capturing
    int displayPreview();
    int captureImages();
    //int captureImages(std::string filenamePrefix, QString* imageNames = nullptr);
    //int captureImagesWithPartition(std::string filenamePrefix);

    // Debugging function
    void printParams() const;

signals:
    void deviceDisconnected();
};

#endif // IMAGECAPTURER

