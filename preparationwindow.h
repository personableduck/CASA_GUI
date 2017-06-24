#ifndef PREPARATIONWINDOW_H
#define PREPARATIONWINDOW_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QString>
#include <QTimer>
#include <vector>
#include <string>

#include <QShortcut>
#include "settingswindow.h"
#include "imagecapturer.h"

namespace Ui {
class PreparationWindow;
}

class PreparationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PreparationWindow(QWidget *parent = 0);
    ~PreparationWindow();

private slots:
    void access_settings_window();
    void on_ConfirmButton_clicked();
    void on_GoBackButton_clicked();
    void update_image();

    void displayDisconnectError();
    void enableConfirmButton();

private:
    Ui::PreparationWindow *ui;
    QShortcut* settingsShortcut;
    SettingsWindow* sw;

    ImageCapturer* ic;
    int numImages;
    QString* imageNames;

    QGraphicsScene* scene;
    QGraphicsPixmapItem* currImage;
    QTimer* timer;

    // Preparation states
    enum preparationState { OBTAIN_SAMPLE = 0, DROPPER, PLACE_ON_SLIDE, COVER_SLIDE, PLUG_IN,
                            CAPTURE_BACKGROUND, INSERT_SLIDE, CAPTURE_SAMPLE, PROCESS_IMAGES, DEFAULT };
    preparationState currState;
    std::vector<QString> tutImageNames[DEFAULT + 1];
    int currImageNum;

    void initTutImageNames();
    void initGraphicsView();

    void updatePreparationState();
    void setImage(QString filename);

    // Image capturing
    void setCameraParameters(std::string filenamePrefix, QString* imageNames = nullptr);
    void setResolution();
    void setExposureMode();
    void setGainMode();
    void setPixelFormat();

    /*
    void captureBackgroundImages();
    void captureSampleImages();
    */
};

#endif // PREPARATIONWINDOW_H
