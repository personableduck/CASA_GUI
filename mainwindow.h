#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QString>

#include "qcustomplot.h"
#include "preparationwindow.h"
#include "imagecapturer.h"
#include "dataprocessor.h"
#include "backpropagationmethod.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //void showPreparationWindow(); /#/

protected:
    bool eventFilter(QObject* object, QEvent* event);
    void keyPressEvent(QKeyEvent* event);

private slots:
    //void display_preview(); /#/
    //void capture_images(); /#/
    void on_zoomInButton_clicked();
    void on_zoomOutButton_clicked();
    void on_timestampSlider_sliderReleased();
    void on_zAxisSlider_sliderReleased();
    void on_statsList_currentRowChanged(int currentRow);
    void on_relativeStatsButton_toggled(bool checked);
    void on_confirmButton_clicked();
    void on_rawHologramButton_toggled(bool checked);
    void on_ampReconst_button_toggled(bool checked);
    void on_phaseReconst_button_toggled(bool checked);
    void on_restartButton_clicked();
    void on_tutorialButton_clicked();
    void on_tut_ok_button_clicked();

private:
    /* member variables */
    Ui::MainWindow* ui;
    //ImageCapturer* ic; /#/
    DataProcessor* dp;
    // Other windows
    //PreparationWindow* pw; /#/

    QGraphicsScene* scene;
    QGraphicsPixmapItem* currImage;
    const double zoomAmt;
    int numTimesZoomedIn;

    int numImages;
    QString* imageNames;

    const double minPlotRange;
    const double maxPlotRange;

    enum distrType { CURVILINEAR_VEL, STRAIGHTLINE_VEL, AVGPATH_VEL, LINEARITY, STRAIGHTNESS,
                     WOBBLE, BEATCROSSFREQUENCY, ALHMAX, MEANANGULARDISP };

    enum tutorialState { OFF, RESULTS, P_MOT, P_PROGMOT, P_NONPROGMOT, P_IMMOT, P_HYPER, PLOT, PARAMS, IMAGES, ZOOM, TIMESTAMP, ZAXIS, TYPE };
    tutorialState currTutorialState;
    void initTutorialOverlays();
    std::vector<QWidget*> tut_overlays;
    void changeTutorialState(tutorialState t);
    void updateOkButtonLoc();

    //void setCameraParameters(); /#/
    //void captureBackgroundImages(); /#/
    //void captureSampleImages(); /#/
    void displaySampleImages();

    //void setResolution(int index); /#/
    //void setExposureMode(int index); /#/
    //void setGainMode(int index); /#/
    //void setPixelFormat(int index); /#/

    int addTracks();

    void displayDistrGraph(const QVector<double>& x, const QVector<double>& y, double barWidth);
    int getParam(distrType type, int trackIndex, double& currParam);
    int graphDistribution(distrType type, unsigned int numBars, bool percent);

    void displayStatsList();
};

#endif // MAINWINDOW_H
