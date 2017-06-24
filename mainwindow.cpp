/*
 * paths changed
 * captureSampleImages changed
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "globals.h"
#include "backpropagationmethod.h"

#include <iostream>
#include <string>
#include <pylon/PylonIncludes.h>
#include <QDataStream>
#include <QFile>
#include <QPointF>
#include <QCoreApplication>
#include <QVector>
#include <limits>
#include <ctime>

using namespace std;

/* Constructor */
MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    //ic(new ImageCapturer), /#/
    dp(new DataProcessor),
    //pw(new PreparationWindow), /#/
    scene(new QGraphicsScene),
    currImage(nullptr),
    zoomAmt(1.1),
    numTimesZoomedIn(0),
    numImages(0),
    imageNames(nullptr),
    minPlotRange(0),
    maxPlotRange(5000),
    currTutorialState(OFF)
{
    srand(time(NULL));

    // Connect the main window to the preview window
    //connect(cw, SIGNAL(captureButtonClicked()), this, SLOT(capture_images())); /#/
    //connect(cw, SIGNAL(previewButtonClicked()), this, SLOT(display_preview())); /#/

    // Set up the UI
    ui->setupUi(this);
    delete ui->mainToolBar;
    this->statusBar()->setSizeGripEnabled(false);
    this->statusBar()->setDisabled(true);
    setFixedSize(size());
    ui->statusBar->showMessage("Standby");

    ui->statsPlot->xAxis->setRange(0, 10);
    ui->statsPlot->yAxis->setRange(0, 10);
    ui->imageViewer->viewport()->installEventFilter(this);
    ui->imageViewer->setFocusPolicy(Qt::NoFocus);

    ui->imageViewer->setScene(scene);
    currImage = scene->addPixmap(QPixmap());

    initTutorialOverlays();
}

MainWindow::~MainWindow()
{
    delete ui;
    //delete ic; /#/
    delete dp;
    //if (cw != nullptr) /#/
        //delete cw; /#/
    scene->clear();
    delete scene;
    if (imageNames != nullptr)
        delete[] imageNames;
}

// Tutorial BEGIN
void MainWindow::initTutorialOverlays()
{
    QPalette p;
    int cVal = 100;
    p.setColor(QPalette::Window, QColor(cVal, cVal, cVal, cVal));

    tut_overlays = {    ui->tut_overlay_1, ui->tut_overlay_2,
                        ui->tut_overlay_3, ui->tut_overlay_4  };
    for (QWidget* overlay : tut_overlays)
    {
        overlay->setAutoFillBackground(true);
        overlay->setPalette(p);
    }

    updateOkButtonLoc();

    changeTutorialState(OFF);
}

void MainWindow::updateOkButtonLoc()
{
    ui->tut_ok_button->move(    ui->tut_frame->x() +
                                ui->tut_frame->width() -
                                ui->tut_ok_button->width() -
                                10
                                ,
                                ui->tut_frame->y() +
                                (
                                    ui->tut_frame->height() -
                                    ui->tut_ok_button->height()
                                ) / 2
                            );
}

void MainWindow::changeTutorialState(tutorialState t)
{
    currTutorialState = t;
    switch(t)
    {
    case OFF:
        for (QWidget* overlay : tut_overlays)
            overlay->hide();
        ui->tut_frame->hide();
        ui->tut_ok_button->hide();
        break;
    case RESULTS:
        for (QWidget* overlay : tut_overlays)
            overlay->show();

        ui->tut_frame->move(640, 730);
        updateOkButtonLoc();
        ui->tut_frame->show();
        ui->tut_ok_button->show();
        ui->tut_msg->setText("Here are the results of your sample.");

        ui->tut_overlay_1->move(0, 0);
        ui->tut_overlay_1->resize(310, 1080);

        ui->tut_overlay_2->move(980, 0);
        ui->tut_overlay_2->resize(940, 1080);

        ui->tut_overlay_3->move(310, 0);
        ui->tut_overlay_3->resize(670, 570);

        ui->tut_overlay_4->move(310, 760);
        ui->tut_overlay_4->resize(670, 320);
        break;
    case P_MOT:
        for (QWidget* overlay : tut_overlays)
            overlay->show();

        ui->tut_frame->move(110, 600);
        updateOkButtonLoc();
        ui->tut_frame->show();
        ui->tut_ok_button->show();
        ui->tut_msg->setText("Percent of sperm moving in the sample.");

        ui->tut_overlay_1->move(0, 0);
        ui->tut_overlay_1->resize(310, 1080);

        ui->tut_overlay_2->move(610, 0);
        ui->tut_overlay_2->resize(1310, 1080);

        ui->tut_overlay_3->move(310, 0);
        ui->tut_overlay_3->resize(300, 580);

        ui->tut_overlay_4->move(310, 610);
        ui->tut_overlay_4->resize(300, 470);
        break;
    case P_PROGMOT:
        for (QWidget* overlay : tut_overlays)
            overlay->show();

        ui->tut_frame->move(110, 600);
        updateOkButtonLoc();
        ui->tut_frame->show();
        ui->tut_ok_button->show();
        ui->tut_msg->setText("Percent of sperm moving actively, either linearly or in a large circle.");

        ui->tut_overlay_1->move(0, 0);
        ui->tut_overlay_1->resize(310, 1080);

        ui->tut_overlay_2->move(610, 0);
        ui->tut_overlay_2->resize(1310, 1080);

        ui->tut_overlay_3->move(310, 0);
        ui->tut_overlay_3->resize(300, 615);

        ui->tut_overlay_4->move(310, 645);
        ui->tut_overlay_4->resize(300, 435);
        break;
    case P_NONPROGMOT:
        for (QWidget* overlay : tut_overlays)
            overlay->show();

        ui->tut_frame->move(110, 600);
        updateOkButtonLoc();
        ui->tut_frame->show();
        ui->tut_ok_button->show();
        ui->tut_msg->setText("Percent of sperm moving with an absence of progression.");

        ui->tut_overlay_1->move(0, 0);
        ui->tut_overlay_1->resize(310, 1080);

        ui->tut_overlay_2->move(610, 0);
        ui->tut_overlay_2->resize(1310, 1080);

        ui->tut_overlay_3->move(310, 0);
        ui->tut_overlay_3->resize(300, 650);

        ui->tut_overlay_4->move(310, 680);
        ui->tut_overlay_4->resize(300, 400);
        break;
    case P_IMMOT:
        for (QWidget* overlay : tut_overlays)
            overlay->show();

        ui->tut_frame->move(110, 600);
        updateOkButtonLoc();
        ui->tut_frame->show();
        ui->tut_ok_button->show();
        ui->tut_msg->setText("Percent of sperm showing no or negligible movement.");

        ui->tut_overlay_1->move(0, 0);
        ui->tut_overlay_1->resize(310, 1080);

        ui->tut_overlay_2->move(610, 0);
        ui->tut_overlay_2->resize(1310, 1080);

        ui->tut_overlay_3->move(310, 0);
        ui->tut_overlay_3->resize(300, 685);

        ui->tut_overlay_4->move(310, 715);
        ui->tut_overlay_4->resize(300, 365);
        break;
    case P_HYPER:
        for (QWidget* overlay : tut_overlays)
            overlay->show();

        ui->tut_frame->move(110, 600);
        updateOkButtonLoc();
        ui->tut_frame->show();
        ui->tut_ok_button->show();
        ui->tut_msg->setText("Percent of sperm moving rapidly, potentially critical to the success of fertilization.");

        ui->tut_overlay_1->move(0, 0);
        ui->tut_overlay_1->resize(310, 1080);

        ui->tut_overlay_2->move(610, 0);
        ui->tut_overlay_2->resize(1310, 1080);

        ui->tut_overlay_3->move(310, 0);
        ui->tut_overlay_3->resize(300, 720);

        ui->tut_overlay_4->move(310, 750);
        ui->tut_overlay_4->resize(300, 320);
        break;
    case PLOT:
        for (QWidget* overlay : tut_overlays)
            overlay->show();

        ui->tut_frame->move(110, 340);
        updateOkButtonLoc();
        ui->tut_frame->show();
        ui->tut_ok_button->show();
        ui->tut_msg->setText("This graph displays a statistical plot of the selected motility parameter.");

        ui->tut_overlay_1->move(0, 0);
        ui->tut_overlay_1->resize(310, 1080);

        ui->tut_overlay_2->move(970, 0);
        ui->tut_overlay_2->resize(950, 1080);

        ui->tut_overlay_3->move(310, 0);
        ui->tut_overlay_3->resize(660, 60);

        ui->tut_overlay_4->move(310, 560);
        ui->tut_overlay_4->resize(660, 520);
        break;
    case PARAMS:
        for (QWidget* overlay : tut_overlays)
            overlay->show();

        ui->tut_frame->move(190, 100);
        updateOkButtonLoc();
        ui->tut_frame->show();
        ui->tut_ok_button->show();
        ui->tut_msg->setText("Select the motility parameter you want to view using this list.");

        ui->tut_overlay_1->move(0, 0);
        ui->tut_overlay_1->resize(30, 1080);

        ui->tut_overlay_2->move(180, 0);
        ui->tut_overlay_2->resize(1740, 1080);

        ui->tut_overlay_3->move(30, 0);
        ui->tut_overlay_3->resize(150, 50);

        ui->tut_overlay_4->move(30, 490);
        ui->tut_overlay_4->resize(150, 590);
        break;
    case IMAGES:
        for (QWidget* overlay : tut_overlays)
            overlay->show();

        ui->tut_frame->move(840, 300);
        updateOkButtonLoc();
        ui->tut_frame->show();
        ui->tut_ok_button->show();
        ui->tut_msg->setText("Images of your sample can be viewed here.");

        ui->tut_overlay_1->move(0, 0);
        ui->tut_overlay_1->resize(1040, 1080);

        ui->tut_overlay_2->move(1860, 0);
        ui->tut_overlay_2->resize(60, 1080);

        ui->tut_overlay_3->move(1040, 0);
        ui->tut_overlay_3->resize(820, 60);

        ui->tut_overlay_4->move(1040, 680);
        ui->tut_overlay_4->resize(820, 400);
        break;
    case ZOOM:
	    for (QWidget* overlay : tut_overlays)
            overlay->show();

        ui->tut_frame->move(1580, 565);
        updateOkButtonLoc();
        ui->tut_frame->show();
        ui->tut_ok_button->show();
        ui->tut_msg->setText("Click here to zoom in or out on the image.");

        ui->tut_overlay_1->move(0, 0);
        ui->tut_overlay_1->resize(1780, 1080);

        ui->tut_overlay_2->move(1830, 0);
        ui->tut_overlay_2->resize(90, 1080);

        ui->tut_overlay_3->move(1780, 0);
        ui->tut_overlay_3->resize(50, 570);

        ui->tut_overlay_4->move(1780, 660);
        ui->tut_overlay_4->resize(50, 420);
        break;
    case TIMESTAMP:
		for (QWidget* overlay : tut_overlays)
            overlay->show();

        ui->tut_frame->move(840, 660);
        updateOkButtonLoc();
        ui->tut_frame->show();
        ui->tut_ok_button->show();
        ui->tut_msg->setText("Scroll through the images using the timestamp slider.");

        ui->tut_overlay_1->move(0, 0);
        ui->tut_overlay_1->resize(1040, 1080);

        ui->tut_overlay_2->move(1860, 0);
        ui->tut_overlay_2->resize(90, 1080);

        ui->tut_overlay_3->move(1040, 0);
        ui->tut_overlay_3->resize(820, 675);

        ui->tut_overlay_4->move(1040, 710);
        ui->tut_overlay_4->resize(820, 340);
        break;
    case ZAXIS:
        for (QWidget* overlay : tut_overlays)
            overlay->show();

        ui->tut_frame->move(840, 660);
        updateOkButtonLoc();
        ui->tut_frame->show();
        ui->tut_ok_button->show();
        ui->tut_msg->setText("Focus the image using the Z-axis slider.");

        ui->tut_overlay_1->move(0, 0);
        ui->tut_overlay_1->resize(1040, 1080);

        ui->tut_overlay_2->move(1860, 0);
        ui->tut_overlay_2->resize(90, 1080);

        ui->tut_overlay_3->move(1040, 0);
        ui->tut_overlay_3->resize(820, 705);

        ui->tut_overlay_4->move(1040, 738);
        ui->tut_overlay_4->resize(820, 340);
        break;
    case TYPE:
        for (QWidget* overlay : tut_overlays)
            overlay->show();

        ui->tut_frame->move(840, 740);
        updateOkButtonLoc();
        ui->tut_frame->show();
        ui->tut_ok_button->show();
        ui->tut_msg->setText("Select the type of processing to perform on the image here.");

        ui->tut_overlay_1->move(0, 0);
        ui->tut_overlay_1->resize(1040, 1080);

        ui->tut_overlay_2->move(1230, 0);
        ui->tut_overlay_2->resize(690, 1080);

        ui->tut_overlay_3->move(1040, 0);
        ui->tut_overlay_3->resize(190, 750);

        ui->tut_overlay_4->move(1040, 830);
        ui->tut_overlay_4->resize(190, 250);
        break;
    default:
        break;
    }
}

void MainWindow::on_tutorialButton_clicked()
{
    changeTutorialState(RESULTS);
}

void MainWindow::on_tut_ok_button_clicked()
{
    switch(currTutorialState)
    {
    case RESULTS:
        changeTutorialState(P_MOT);
        break;
    case P_MOT:
        changeTutorialState(P_PROGMOT);
        break;
    case P_PROGMOT:
        changeTutorialState(P_NONPROGMOT);
        break;
    case P_NONPROGMOT:
        changeTutorialState(P_IMMOT);
        break;
    case P_IMMOT:
        changeTutorialState(P_HYPER);
        break;
    case P_HYPER:
        changeTutorialState(PLOT);
        break;
    case PLOT:
        changeTutorialState(PARAMS);
        break;
    case PARAMS:
        changeTutorialState(IMAGES);
        break;
    case IMAGES:
        changeTutorialState(ZOOM);
        break;
    case ZOOM:
        changeTutorialState(TIMESTAMP);
        break;
    case TIMESTAMP:
        changeTutorialState(ZAXIS);
        break;
    case ZAXIS:
        changeTutorialState(TYPE);
        break;
    case TYPE:
        changeTutorialState(OFF);
        break;
    default:
        break;
    }
}
// Tutorial END

/* /#/
void MainWindow::showPreparationWindow()
{
    pw->show();
}
*/

bool MainWindow::eventFilter(QObject* object, QEvent* event)
{
    if (object == ui->imageViewer->viewport() && event->type() == QEvent::Wheel)
        return true;

    return false;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int value = ui->timestampSlider->value();
    if (event->key() == Qt::Key_Right)
    {
        if (value < ui->timestampSlider->maximum())
        {
            ui->timestampSlider->setValue(value + 1);
            on_timestampSlider_sliderReleased();
        }
    }
    else if (event->key() == Qt::Key_Left)
    {
        if (value > 0)
        {
            ui->timestampSlider->setValue(value - 1);
            on_timestampSlider_sliderReleased();
        }
    }
}

/* /#/
void MainWindow::setCameraParameters()
{
    setResolution(cw->getResolutionIndex());
    setGainMode(cw->getGainModeIndex());
    ic->setFps(cw->getFPS());
    setExposureMode(cw->getExposureModeIndex());
    ic->setExposureTime(cw->getExposureTime());
    ic->setGain(cw->getGain());
    ic->setNumImagesToCapture(cw->getNumImages());
    ic->setOffsetX(cw->getOffsetX());
    ic->setOffsetY(cw->getOffsetY());
    ic->setGamma(cw->getGamma());
    setPixelFormat(cw->getPixelFormatIndex());
}

void MainWindow::display_preview()
{
    cw->clearErrorMsg();
    setCameraParameters();
    if (ic->displayPreview() < 0)
        cw->displayErrorMsg();
    cw->enablePreviewButton();
}

void MainWindow::capture_images()
{
    setCameraParameters();

    CaptureWindow::captureState s = cw->getCurrCaptureState();
    switch (s)
    {
    case CaptureWindow::BACKGROUND:
       captureBackgroundImages();
       break;
    case CaptureWindow::SAMPLE:
       captureSampleImages();
       break;
    }
}

void MainWindow::captureBackgroundImages()
{
    cw->clearErrorMsg();
    // Capture images and save them to disk
    if (cw->getResolutionIndex() != 0)
    {
        if (ic->captureImages("BackgroundImage") < 0)
            cw->displayErrorMsg();
    }
    else
    {
        if (ic->captureImagesWithPartition("BackgroundImage") < 0)
            cw->displayErrorMsg();
    }

    cw->changeCaptureState(CaptureWindow::SAMPLE);
    cw->enableCaptureButton();
}

void MainWindow::captureSampleImages()
{
    numImages = cw->getNumImages();

    cw->clearErrorMsg();
    // Capture images and save them to disk
    if (cw->getResolutionIndex() != 0)
    {
        if (imageNames != nullptr)
            delete[] imageNames;
        imageNames = new QString[numImages];

        if (ic->captureImages("SampleImage", imageNames) < 0)
            cw->displayErrorMsg();
    }
    else
    {
        if (ic->captureImagesWithPartition("SampleImage") < 0)
            cw->displayErrorMsg();
    }

    dp->clearTracks();
    if (addTracks() < 0)
    {
        cerr << "Error: Could not analyze tracking images." << endl;
        return;
    }

    // dp->printTracks(); // TESTING

    ui->statsList->clear();
    displayStatsList();

    // Display curvilinear velocity distribution graph
    ui->statsList->setCurrentRow(0);

    // Enable stats radio buttons
    ui->relativeStatsButton->setEnabled(true);
    ui->absoluteStatsButton->setEnabled(true);

    displaySampleImages();

    delete cw;
    cw = nullptr;

    showMaximized();
}
*/

void MainWindow::displaySampleImages()
{
    ui->timestampSlider->setValue(0);
    ui->timestampSlider->setMaximum(numImages - 1);
    ui->timestamp_spinBox->setMaximum(numImages - 1);

//    if (imageNames != nullptr)
//        delete[] imageNames;
//    imageNames = new QString[numImages];

//    // Place image filenames into and array
//    for (int i = 0; i < numImages; i++)
//    {
//        QString currImagePath(QCoreApplication::applicationDirPath());
//        currImagePath.append("/Images/");
//        currImagePath.append("SampleImage");
//        currImagePath.append(QString::number(i + 1));
//        currImagePath.append(".tiff");
//        imageNames[i] = currImagePath;
//    }

    // Place the first image into the image viewer
    on_timestampSlider_sliderReleased();

    // Calculate the image and image viewer parameters
    int imageWidth = currImage->pixmap().width();
    int imageHeight = currImage->pixmap().height();
    int imageViewerWidth = ui->imageViewer->width();
    int imageViewerHeight = ui->imageViewer->height();

    // Place the image at the center of the image viewer
    currImage->setPos(-imageWidth/2, -imageHeight/2);

    // Calculate the initial image view zoom
    double widthZoom = (double)imageViewerWidth/imageWidth;
    double heightZoom = (double)imageViewerHeight/imageHeight;
    double initZoomAmt = (widthZoom < heightZoom) ? widthZoom : heightZoom;
    (imageWidth > imageHeight) ?
        scene->setSceneRect(-1.25*imageWidth, -1.25*imageWidth, 2.5*imageWidth, 2.5*imageWidth) :
        scene->setSceneRect(-1.25*imageHeight, -1.25*imageHeight, 2.5*imageHeight, 2.5*imageHeight);
    ui->imageViewer->scale(initZoomAmt, initZoomAmt);

    // Zoom out once more to be able to view the entire image
    on_zoomOutButton_clicked();
}

/* /#/
void MainWindow::setResolution(int index)
{
    switch (index)
    {
    case 1:
        ic->setWidth(2592);
        ic->setHeight(1944);
        break;
    case 2:
        ic->setWidth(2304);
        ic->setHeight(1728);
        break;
    case 3:
        ic->setWidth(1920);
        ic->setHeight(1440);
        break;
    case 4:
        ic->setWidth(1024);
        ic->setHeight(768);
        break;
    case 5:
        ic->setWidth(640);
        ic->setHeight(480);
        break;
    }
}

void MainWindow::setExposureMode(int index)
{
    switch (index)
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

void MainWindow::setGainMode(int index)
{
    switch (index)
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

void MainWindow::setPixelFormat(int index)
{
    switch (index)
    {
    case 0:
        ic->setPixelFormat(Basler_UsbCameraParams::PixelFormat_Mono12);
        break;
    case 1:
        ic->setPixelFormat(Basler_UsbCameraParams::PixelFormat_Mono8);
        break;
    }
}
*/

/* Graphing functions begin */

int MainWindow::addTracks()
{
    int retval;
    int currTrackNum;
    for (currTrackNum = 1; ; currTrackNum++)
    {
        QString appPath(QCoreApplication::applicationDirPath());
        string coordsFile = appPath.toStdString() + "/TrackCoords/Sperm";
        coordsFile += to_string(currTrackNum);

        string framesFile = coordsFile;
        coordsFile += "Coordinates.dat";
        framesFile += "StartEndFram.dat";

        if ((retval = dp->addTrack(coordsFile, framesFile, true)) < 0)
        {
            if (retval == CANNOT_OPEN_FILE)
                break;
            else
            {
                cerr << "Error: Unable to process Track #" << currTrackNum << "." << endl;
                return retval;
            }
        }
    }

    if (dp->calcAllSampleMotilityValues() < 0)
        return CALCULATION_ERROR;

    double percentMotile;
    double percentImmotile;
    double percentHyper;
    double percentProg;
    double percentNonProg;
    double percentRapidLinear;

    dp->getPercentMotile(percentMotile);
    dp->getPercentImmotile(percentImmotile);
    dp->getPercentHyperactivated(percentHyper);
    dp->getPercentProgMotile(percentProg);
    dp->getPercentNonProgMotile(percentNonProg);
    dp->getPercentRapidAndLinear(percentRapidLinear);

    ui->percentMotile_spinBox->setValue(percentMotile);
    ui->percentImmotile_spinBox->setValue(percentImmotile);
    ui->percentHyper_spinBox->setValue(percentHyper);
    ui->percentProg_spinBox->setValue(percentProg);
    ui->percentNonProg_spinBox->setValue(percentNonProg);
    // ui->percentRapidAndLinear_spinBox->setValue(percentRapidLinear);

    if (percentMotile > 40 && percentProg > 32)
        ui->result_label->setText("Result: The sample is normal.");
    else
        ui->result_label->setText("Result: The sample is not healthy.");

    return 0;
}

void MainWindow::displayDistrGraph(const QVector<double>& x, const QVector<double>& y, double barWidth)
{
    ui->statsPlot->clearPlottables();
    QCPBars* barPlot = new QCPBars(ui->statsPlot->xAxis, ui->statsPlot->yAxis);
    ui->statsPlot->addPlottable(barPlot);
    barPlot->setData(x, y);
    barPlot->setWidthType(QCPBars::wtPlotCoords);
    barPlot->setWidth(barWidth);
    ui->statsPlot->replot();
}

int MainWindow::getParam(distrType type, int trackIndex, double& currParam)
{
    int retval = 0;

    switch(type)
    {
    case CURVILINEAR_VEL:
        retval = dp->getCurvilinearVel(trackIndex, currParam);
        break;
    case STRAIGHTLINE_VEL:
        retval = dp->getStraightLineVel(trackIndex, currParam);
        break;
    case AVGPATH_VEL:
        retval = dp->getAvgPathVel(trackIndex, currParam);
        break;
    case LINEARITY:
        retval = dp->getLinearity(trackIndex, currParam);
        break;
    case STRAIGHTNESS:
        retval = dp->getStraightness(trackIndex, currParam);
        break;
    case WOBBLE:
        retval = dp->getWobble(trackIndex, currParam);
        break;
    case BEATCROSSFREQUENCY:
        retval = dp->getBeatCrossFrequency(trackIndex, currParam);
        break;
    case ALHMAX:
        retval = dp->getAmplitudeLateralHeadDisplacement(trackIndex, currParam);
        break;
    case MEANANGULARDISP:
        retval = dp->getMeanAngularDisplacement(trackIndex, currParam);
        break;
    default:
        retval = ILLEGAL_ARGUMENT;
    }

    return retval;
}

int MainWindow::graphDistribution(distrType type, unsigned int numBars, bool percent)
{
    int retval;

    double maxParam = 0;
    unsigned int numTracks = (unsigned int)dp->getNumTracks();
    for (unsigned int i = 0; i < numTracks; i++)
    {
        double currParam = numeric_limits<double>::quiet_NaN();
        if ((retval = getParam(type, i, currParam)) < 0)
            return retval;

        if (currParam > maxParam)
            maxParam = currParam;
    }

    double barWidth = maxParam/numBars;

    QVector<double> param(numBars, 0);
    for (unsigned int i = 0; i < numBars; i++)
    {
        param[i] = i*(barWidth) + 0.5*(barWidth);
    }

    QVector<double> tracks(numBars, 0);
    for (unsigned int i = 0; i < numTracks; i++)
    {
        double currParam = numeric_limits<double>::quiet_NaN();
        if ((retval = getParam(type, i, currParam)) < 0)
            return retval;

        double paramRatio = currParam/maxParam;
        int index = numBars*paramRatio;
        double intpart;
        if (currParam != 0 && modf(paramRatio, &intpart) == 0.0)
            index--;
        tracks[index]++;
    }

    double maxY = 0;
    for (unsigned int i = 0; i < numBars; i++)
    {
        if (percent)
            tracks[i] = (100*tracks[i]/numTracks);
        if (tracks[i] > maxY)
            maxY = tracks[i];
    }

    switch(type)
    {
    case CURVILINEAR_VEL:
        ui->statsPlot->xAxis->setLabel("curvilnear velocity (µm/s)");
        break;
    case STRAIGHTLINE_VEL:
        ui->statsPlot->xAxis->setLabel("straight-line velocity (µm/s)");
        break;
    case AVGPATH_VEL:
        ui->statsPlot->xAxis->setLabel("average path velocity (µm/s)");
        break;
    case LINEARITY:
        ui->statsPlot->xAxis->setLabel("linearity (%)");
        break;
    case STRAIGHTNESS:
        ui->statsPlot->xAxis->setLabel("straightness (%)");
        break;
    case WOBBLE:
        ui->statsPlot->xAxis->setLabel("wobble (%)");
        break;
    case BEATCROSSFREQUENCY:
        ui->statsPlot->xAxis->setLabel("beat cross frequency (beats/s)");
        break;
    case ALHMAX:
        ui->statsPlot->xAxis->setLabel("amplitude of lateral head displacement (µm)");
        break;
    case MEANANGULARDISP:
        ui->statsPlot->xAxis->setLabel("mean angular displacement (degrees/s)");
        break;
    default:
        return ILLEGAL_ARGUMENT;
        break;
    }

    if (percent)
        ui->statsPlot->yAxis->setLabel("percent tracks (%)");
    else
        ui->statsPlot->yAxis->setLabel("number of tracks");

    ui->statsPlot->xAxis->setRange(0, 1.01*maxParam);

    maxY = 1.25*maxY;
    if (percent && maxY > 100)
        maxY = 100;
    ui->statsPlot->yAxis->setRange(0, maxY);

    displayDistrGraph(param, tracks, barWidth);

    return 0;
}

/* Graphing functions end */

void MainWindow::displayStatsList()
{
    ui->statsList->addItem("VCL");
    ui->statsList->addItem("VSL");
    ui->statsList->addItem("VAP");
    ui->statsList->addItem("LIN");
    ui->statsList->addItem("STR");
    ui->statsList->addItem("WOB");
    ui->statsList->addItem("BCF");
    ui->statsList->addItem("ALH");
    ui->statsList->addItem("MAD");
}

/* Slots Begin */

void MainWindow::on_zoomInButton_clicked()
{
    QGraphicsView* gv = ui->imageViewer;
    // Determine the center point of the image viewer
    QPointF centerPoint = gv->mapToScene(gv->viewport()->rect().center());
    // Scale (zoom in) the image viewer accordingly and center the view to where it was previously
    gv->scale(zoomAmt, zoomAmt);
    gv->centerOn(centerPoint);
    numTimesZoomedIn++;
}

void MainWindow::on_zoomOutButton_clicked()
{
    QGraphicsView* gv = ui->imageViewer;

    // Do not zoom out passed the initial zoom amount
    if (numTimesZoomedIn < 0)
        return;

    // Determine the center point of the image viewer
    QPointF centerPoint = gv->mapToScene(gv->viewport()->rect().center());
    // Scale (zoom out) the image viewer accordingly and center the view to where it was previously
    gv->scale(1/zoomAmt, 1/zoomAmt);
    gv->centerOn(centerPoint);
    numTimesZoomedIn--;
}

void MainWindow::on_timestampSlider_sliderReleased()
{
    int value = ui->timestampSlider->value();
    // Get the path to the image to be displayed
    QString imagePath(imageNames[value]);

    // Set the pixmap of the current image accordingly
    if (ui->rawHologramButton->isChecked())
        currImage->setPixmap(QPixmap(imagePath));
    else
    {
        QString tempImagePath(QCoreApplication::applicationDirPath());
        tempImagePath.append("/TempImages/");

        QString amplitudePath = tempImagePath;
        amplitudePath.append("amplitude.bmp");
        QString phasePath = tempImagePath;
        phasePath.append("phase.bmp");

        BPTheImage(imagePath.toStdString(), amplitudePath.toStdString(), phasePath.toStdString(), ui->zAxisSlider->value(), 2.2, 645);

        if (ui->ampReconst_button->isChecked())
            //currImage->setPixmap(QPixmap(imagePath));
            currImage->setPixmap(QPixmap(amplitudePath));
        else
            currImage->setPixmap(QPixmap(phasePath));
    }
}

void MainWindow::on_zAxisSlider_sliderReleased()
{
    int value = ui->zAxisSlider->value();

    // Get the path to the image to be processed
    QString imagePath(imageNames[ui->timestampSlider->value()]);

    // Set the pixmap of the current image accordingly
    if (!ui->rawHologramButton->isChecked())
    {
        QString tempImagePath(QCoreApplication::applicationDirPath());
        tempImagePath.append("/TempImages/");

        QString amplitudePath = tempImagePath;
        amplitudePath.append("amplitude.bmp");
        QString phasePath = tempImagePath;
        phasePath.append("phase.bmp");
        BPTheImage(imagePath.toStdString(), amplitudePath.toStdString(), phasePath.toStdString(), value, 2.2, 645);

        if (ui->ampReconst_button->isChecked())
            //currImage->setPixmap(QPixmap(imagePath));
            currImage->setPixmap(QPixmap(amplitudePath));
        else
            currImage->setPixmap(QPixmap(phasePath));
    }
}

void MainWindow::on_statsList_currentRowChanged(int currentRow)
{
    int retval = 0;
    int numBars = 40;
    if (dp->getNumTracks() < 20)
        numBars = 25;
    bool relativeStats = ui->relativeStatsButton->isChecked();
    switch (currentRow)
    {
    case 0:
        retval = graphDistribution(CURVILINEAR_VEL, numBars, relativeStats);
        break;
    case 1:
        retval = graphDistribution(STRAIGHTLINE_VEL, numBars, relativeStats);
        break;
    case 2:
        retval = graphDistribution(AVGPATH_VEL, numBars, relativeStats);
        break;
    case 3:
        retval = graphDistribution(LINEARITY, numBars, relativeStats);
        break;
    case 4:
        retval = graphDistribution(STRAIGHTNESS, numBars, relativeStats);
        break;
    case 5:
        retval = graphDistribution(WOBBLE, numBars, relativeStats);
        break;
    case 6:
        retval = graphDistribution(BEATCROSSFREQUENCY, numBars, relativeStats);
        break;
    case 7:
        retval = graphDistribution(ALHMAX, numBars, relativeStats);
        break;
    case 8:
        retval = graphDistribution(MEANANGULARDISP, numBars, relativeStats);
        break;
    default:
        cerr << "Error. Row is out of range." << endl;
    }

    if (retval < 0)
        cerr << "Error " << retval << ": Could not graph distribution." << endl;
}

void MainWindow::on_relativeStatsButton_toggled(bool checked)
{
    checked;
    on_statsList_currentRowChanged(ui->statsList->currentRow());
}

void MainWindow::on_confirmButton_clicked()
{
    on_timestampSlider_sliderReleased();
}

/* Slots End */

void MainWindow::on_rawHologramButton_toggled(bool checked)
{
    if (checked)
        on_timestampSlider_sliderReleased();
}

void MainWindow::on_ampReconst_button_toggled(bool checked)
{
    if (checked)
        on_timestampSlider_sliderReleased();
}

void MainWindow::on_phaseReconst_button_toggled(bool checked)
{
    if (checked)
        on_timestampSlider_sliderReleased();
}

void MainWindow::on_restartButton_clicked()
{
    QStringList args = QApplication::arguments();
    args.removeFirst();
    QProcess::startDetached(QApplication::applicationFilePath(), args);
    QCoreApplication::quit();
}

