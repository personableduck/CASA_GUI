#include "settingswindow.h"
#include "ui_settingswindow.h"

#include <QSlider>
#include <QSpinBox>

SettingsWindow::SettingsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
    setFixedSize(size());
    ui->expoLabel->setDisabled(true);
    ui->expoSlider->setDisabled(true);
    ui->expoSpinBox->setDisabled(true);
    updateOffset(0);
    on_dvButton_clicked();
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

/* Getters implementation begin */
int SettingsWindow::getFPS() const
{
    return ui->fpsSlider->value();
}

int SettingsWindow::getExposureTime() const
{
    return ui->expoSlider->value();
}

int SettingsWindow::getGain() const
{
    return ui->gainSlider->value();
}

double SettingsWindow::getGamma() const
{
    return ((double)(ui->gammaSlider->value()) / 100);
}

int SettingsWindow::getNumImages() const
{
    return ui->frameSlider->value();
}

int SettingsWindow::getOffsetX() const
{
    return ui->offsetXSpinBox->value();
}

int SettingsWindow::getOffsetY() const
{
    return ui->offsetYSpinBox->value();
}

int SettingsWindow::getExposureModeIndex() const
{
    return ui->expoOptionsComboBox->currentIndex();
}

int SettingsWindow::getResolutionIndex() const
{
    return ui->resBox->currentIndex();
}

int SettingsWindow::getPixelFormatIndex() const
{
    return ui->pixelFormatComboBox->currentIndex();
}

int SettingsWindow::getGainModeIndex() const
{
    return ui->gainOptionsComboBox->currentIndex();
}

/* Getters implementation end */

/* Slots implemetation begin */

void SettingsWindow::on_resBox_activated(int index)
{
    switch (index)
    {
    case 0:
        setFPSMax(14);
        break;
    case 1:
        setFPSMax(18);
        break;
    case 2:
        setFPSMax(24);
        break;
    case 3:
        setFPSMax(65);
        break;
    case 4:
        setFPSMax(128);
        break;
    }

    updateOffset(index);
}

void SettingsWindow::on_dvButton_clicked()
{
    ui->resBox->setCurrentIndex(0);
    setFPSMax(14);
    ui->offsetXSpinBox->setValue(0);
    ui->offsetYSpinBox->setValue(0);

    ui->expoOptionsComboBox->setCurrentIndex(2);
    ui->expoLabel->setDisabled(false);
    ui->expoSlider->setDisabled(false);
    ui->expoSpinBox->setDisabled(false);
    ui->expoSlider->setValue(40000);

    ui->gainOptionsComboBox->setCurrentIndex(2);
    ui->gainLabel->setDisabled(false);
    ui->gainSlider->setDisabled(false);
    ui->gainSpinBox->setDisabled(false);
    ui->gainSlider->setValue(0);

    ui->fpsSlider->setValue(5);
    ui->frameSlider->setValue(50);
    ui->gammaSlider->setValue(100);
    ui->pixelFormatComboBox->setCurrentIndex(0);
}

void SettingsWindow::on_expoOptionsComboBox_activated(int index)
{
    switch (index)
    {
    case 0:
        ui->expoLabel->setDisabled(true);
        ui->expoSlider->setDisabled(true);
        ui->expoSpinBox->setDisabled(true);
        ui->expoSlider->setValue(150000);
        break;
    case 1:
    case 2:
        ui->expoLabel->setDisabled(false);
        ui->expoSlider->setDisabled(false);
        ui->expoSpinBox->setDisabled(false);
        break;
    }
}

void SettingsWindow::on_gainOptionsComboBox_activated(int index)
{
    switch (index)
    {
    case 0:
        ui->gainLabel->setDisabled(true);
        ui->gainSlider->setDisabled(true);
        ui->gainSpinBox->setDisabled(true);
        ui->gainSlider->setValue(16);
        break;
    case 1:
    case 2:
        ui->gainLabel->setDisabled(false);
        ui->gainSlider->setDisabled(false);
        ui->gainSpinBox->setDisabled(false);
        break;
    }
}

/* Slots implemetation end */

/* Private member functions implementation begin */

void SettingsWindow::setOffsetDisabled(bool value)
{
    ui->offsetXLabel->setDisabled(value);
    ui->offsetXSpinBox->setDisabled(value);
    ui->offsetYLabel->setDisabled(value);
    ui->offsetYSpinBox->setDisabled(value);
}

void SettingsWindow::setFPSMax(int val)
{
    ui->fpsSlider->setMaximum(val);
    ui->fpsSpinBox->setMaximum(val);
    ui->fpsSlider->setValue(val);
    ui->fpsSpinBox->setValue(val);
}

void SettingsWindow::setOffsetMaximum(int maxX, int maxY)
{
    ui->offsetXSpinBox->setMaximum(maxX);
    ui->offsetYSpinBox->setMaximum(maxY);
}

void SettingsWindow::updateOffset(int index)
{
    switch (index)
    {
    case 0:
        setOffsetDisabled(true);
        ui->offsetXSpinBox->setValue(0);
        ui->offsetYSpinBox->setValue(0);
        break;
    case 1:
        setOffsetDisabled(false);
        setOffsetMaximum(288,216);
        break;
    case 2:
        setOffsetDisabled(false);
        setOffsetMaximum(672,504);
        break;
    case 3:
        setOffsetDisabled(false);
        setOffsetMaximum(1568,1176);
        break;
    case 4:
        setOffsetDisabled(false);
        setOffsetMaximum(1952,1464);
        break;
    }
}

/* Private member functions implementation end */
