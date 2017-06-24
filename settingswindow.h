#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDialog>

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = 0);
    ~SettingsWindow();

    // Getters
    int getFPS() const;
    double getGamma() const;
    int getExposureTime() const;
    int getGain() const;
    int getNumImages() const;
    int getOffsetX() const;
    int getOffsetY() const;
    int getExposureModeIndex() const;
    int getResolutionIndex() const;
    int getPixelFormatIndex() const;
    int getGainModeIndex() const;

private slots:
    void on_resBox_activated(int index);
    void on_dvButton_clicked();
    void on_expoOptionsComboBox_activated(int index);

    void on_gainOptionsComboBox_activated(int index);

private:
    Ui::SettingsWindow *ui;

    void updateOffset(int index);
    void setFPSMax (int val);
    void setOffsetDisabled(bool value);
    void setOffsetMaximum(int maxX, int maxY);
};


#endif // SETTINGSWINDOW_H
