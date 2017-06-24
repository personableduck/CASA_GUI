#include "preparationwindow.h"
#include "ui_preparationwindow.h"

using namespace std;

PreparationWindow::PreparationWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreparationWindow),
    settingsShortcut(nullptr),
    sw(new SettingsWindow),
    ic(new ImageCapturer),
    numImages(0),
    imageNames(nullptr),
    currState(OBTAIN_SAMPLE),
    scene(new QGraphicsScene),
    timer(new QTimer(this)),
    currImageNum(-1)
{
    ui->setupUi(this);

    setWindowTitle("Sample Preparation");

    // Create a shortcut to open the settings window
    settingsShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_O), this, SLOT(access_settings_window()));

    initTutImageNames();
    initGraphicsView();

    // Setup error message is camera disconnected while trying to capture images
    connect(ic, SIGNAL(deviceDisconnected()), this, SLOT(displayDisconnectError()));
    connect(ic, SIGNAL(finished()), this, SLOT(enableConfirmButton()));

    connect(timer, SIGNAL(timeout()), this, SLOT(update_image()));
    updatePreparationState();
}

PreparationWindow::~PreparationWindow()
{
    delete ui;
    delete scene;
    delete timer;
}

/* Preparation states */

void PreparationWindow::initTutImageNames()
{
    tutImageNames[OBTAIN_SAMPLE].push_back("dish.bmp");
    //tutImageNames[OBTAIN_SAMPLE].push_back("dish-sample.bmp");

    tutImageNames[DROPPER].push_back("dish-dropper1.bmp");
    tutImageNames[DROPPER].push_back("dish-dropper2.bmp");

    tutImageNames[PLACE_ON_SLIDE].push_back("slide-dropper1.bmp");
    tutImageNames[PLACE_ON_SLIDE].push_back("slide-dropper2.bmp");

    tutImageNames[COVER_SLIDE].push_back("slide-cover1.bmp");
    tutImageNames[COVER_SLIDE].push_back("slide-cover2.bmp");
}

void PreparationWindow::initGraphicsView()
{
    ui->GraphicsView->setScene(scene);

    currImage = scene->addPixmap(QPixmap());
    setImage("/TutorialImages/dish.bmp");
    // Calculate the image and image viewer parameters
    int imageWidth = currImage->pixmap().width();
    int imageHeight = currImage->pixmap().height();
    int imageViewerWidth = ui->GraphicsView->width();
    int imageViewerHeight = ui->GraphicsView->height();

    // Place the image at the center of the image viewer
    currImage->setPos(-imageWidth/2, -imageHeight/2);

    // Calculate the initial image view zoom
    double widthZoom = (double)imageViewerWidth/imageWidth;
    double heightZoom = (double)imageViewerHeight/imageHeight;
    double initZoomAmt = (widthZoom < heightZoom) ? widthZoom : heightZoom;
    ui->GraphicsView->scale(initZoomAmt, initZoomAmt);
}

void PreparationWindow::updatePreparationState()
{
    currImageNum = -1;
    timer->stop();
    timer->start(1000);
    update_image();

    switch (currState)
    {
    case OBTAIN_SAMPLE:
    {
        ui->InfoTextLabel->setText(
            "Prepare the semen sample by "
            "ejaculating into the dish provided."
        );
        break;
    }
    case DROPPER:
    {
        ui->InfoTextLabel->setText(
            "Use the dropper to draw up some "
            "of the semen sample."
        );
        break;
    }
    case PLACE_ON_SLIDE:
    {
        ui->InfoTextLabel->setText(
            "Dispense one drop of the sample "
            "onto the middle of the microscope slide."
        );
        break;
    }
    case COVER_SLIDE:
    {
        ui->InfoTextLabel->setText(
            "Gently place the cover slip over the semen sample."
        );
        break;
    }
    case PLUG_IN:
    {
        ui->InfoTextLabel->setText(
            "Plug the semen analysis device into your "
            "computer with the USB cable. Do not "
            "insert the microscope slide into the device yet."
        );
        break;
    }
    case CAPTURE_BACKGROUND:
    {
        setCameraParameters("BackgroundImage");
        ui->ConfirmButton->setDisabled(true);
        ic->start();
        ui->InfoTextLabel->setText(
            "Please stand by while the device captures preliminary "
            "background images without the sample. "
            "Do not disconnect the device from your computer."
        );
        break;
    }
    case INSERT_SLIDE:
    {
        ui->InfoTextLabel->setText(
            "Now, insert the microscope slide into the sample "
            "holder on the device."
        );
        break;
    }
    case CAPTURE_SAMPLE:
    {
        setCameraParameters("SampleImage");
        ui->ConfirmButton->setDisabled(true);
        ic->start();
        ui->InfoTextLabel->setText(
            "Please stand by while the device captures "
            "images of the semen sample. "
            "Do not disconnect the device from your computer."
        );
        break;
    }
    case PROCESS_IMAGES:
    {
        ui->InfoTextLabel->setText(
            "Please stand by while your images are being processed. "
            "This may take several minutes."
        );
        break;
    }
    default:
    {
        ui->InfoTextLabel->setText("DEFAULT");
        // Send signal to MainWindow
        break;
    }
    }
}

void PreparationWindow::update_image()
{
    if (tutImageNames[currState].size() <= 0)
        return;
    currImageNum++;
    if (currImageNum >= tutImageNames[currState].size())
        currImageNum = 0;
    QString path = "/TutorialImages/";
    setImage(path.append(tutImageNames[currState][currImageNum]));
}

void PreparationWindow::setImage(QString filename)
{
    currImage->setPixmap(
        QPixmap(QCoreApplication::applicationDirPath().append(filename))
    );
}

/* Image capturing */

void PreparationWindow::setCameraParameters(string filenamePrefix, QString* imageNames)
{
    setResolution();
    setGainMode();
    ic->setFps(sw->getFPS());
    setExposureMode();
    ic->setExposureTime(sw->getExposureTime());
    ic->setGain(sw->getGain());
    ic->setNumImagesToCapture(sw->getNumImages());
    ic->setOffsetX(sw->getOffsetX());
    ic->setOffsetY(sw->getOffsetY());
    ic->setGamma(sw->getGamma());
    setPixelFormat();
    ic->setFilenamePrefix(filenamePrefix);
    ic->setImageNames(imageNames);
}

void PreparationWindow::setResolution()
{
    switch (sw->getResolutionIndex())
    {
    case 0:
        ic->setWidth(2592);
        ic->setHeight(1944);
        break;
    case 1:
        ic->setWidth(2304);
        ic->setHeight(1728);
        break;
    case 2:
        ic->setWidth(1920);
        ic->setHeight(1440);
        break;
    case 3:
        ic->setWidth(1024);
        ic->setHeight(768);
        break;
    case 4:
        ic->setWidth(640);
        ic->setHeight(480);
        break;
    }
}

void PreparationWindow::setExposureMode()
{
    switch (sw->getExposureModeIndex())
    {
    case 0:
        ic->setExposureAuto(Basler_UsbCameraParams::ExposureAuto_Continuous);
        break;
    case 1:
        ic->setExposureAuto(Basler_UsbCameraParams::ExposureAuto_Once);
        break;
    case 2:
        ic->setExposureAuto(Basler_UsbCameraParams::ExposureAuto_Off);
        break;
    }
}

void PreparationWindow::setGainMode()
{
    switch (sw->getGainModeIndex())
    {
    case 0:
        ic->setGainAuto(Basler_UsbCameraParams::GainAuto_Continuous);
        break;
    case 1:
        ic->setGainAuto(Basler_UsbCameraParams::GainAuto_Once);
        break;
    case 2:
        ic->setGainAuto(Basler_UsbCameraParams::GainAuto_Off);
        break;
    }
}

void PreparationWindow::setPixelFormat()
{
    switch (sw->getPixelFormatIndex())
    {
    case 0:
        ic->setPixelFormat(Basler_UsbCameraParams::PixelFormat_Mono12);
        break;
    case 1:
        ic->setPixelFormat(Basler_UsbCameraParams::PixelFormat_Mono8);
        break;
    }
}

/*
void PreparationWindow::captureBackgroundImages()
{
    ic->captureImages("BackgroundImage");
    // TODO: check for error
}

void PreparationWindow::captureSampleImages()
{
    numImages = sw->getNumImages();

    if (imageNames != nullptr)
        delete[] imageNames;
    imageNames = new QString[numImages];

    ic->captureImages("SampleImage", imageNames);
    // TODO: check for error
}
*/

/* SLOTS */

void PreparationWindow::access_settings_window()
{
    sw->exec();
}

void PreparationWindow::on_ConfirmButton_clicked()
{
    if (currState == DEFAULT)
        return;

    int s = currState;
    currState = static_cast<preparationState>(++s);
    updatePreparationState();
}

void PreparationWindow::on_GoBackButton_clicked()
{
    if (currState == OBTAIN_SAMPLE)
        return;

    int s = currState;
    currState = static_cast<preparationState>(--s);
    updatePreparationState();
}

void PreparationWindow::displayDisconnectError()
{
    ui->InfoTextLabel->setText(
        "ERROR: The device is not properly connected to your computer. "
        "Please try reconnecting the device."
    );
}

void PreparationWindow::enableConfirmButton()
{
    ui->ConfirmButton->setEnabled(true);
}
