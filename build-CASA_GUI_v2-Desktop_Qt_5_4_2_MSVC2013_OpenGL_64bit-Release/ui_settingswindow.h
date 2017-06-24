/********************************************************************************
** Form generated from reading UI file 'settingswindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSWINDOW_H
#define UI_SETTINGSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingsWindow
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *bottomButtons;
    QPushButton *dvButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *okButton;
    QWidget *layoutWidget1;
    QVBoxLayout *sliders;
    QVBoxLayout *fpsBar;
    QLabel *fpsLabel;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QSlider *fpsSlider;
    QSpinBox *fpsSpinBox;
    QVBoxLayout *frameBar;
    QLabel *frameLabel;
    QHBoxLayout *horizontalLayout_7;
    QSlider *frameSlider;
    QSpinBox *frameSpinBox;
    QVBoxLayout *gammaBar;
    QLabel *gammaLabel;
    QHBoxLayout *horizontalLayout_4;
    QSlider *gammaSlider;
    QSpinBox *gammaSpinBox;
    QVBoxLayout *expoTimeBar;
    QLabel *expoLabel;
    QHBoxLayout *horizontalLayout_5;
    QSlider *expoSlider;
    QSpinBox *expoSpinBox;
    QVBoxLayout *expoTimeBar_2;
    QLabel *gainLabel;
    QHBoxLayout *horizontalLayout_6;
    QSlider *gainSlider;
    QSpinBox *gainSpinBox;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *resolution;
    QLabel *resLabel;
    QComboBox *resBox;
    QHBoxLayout *offset;
    QVBoxLayout *offsetLabels;
    QLabel *offsetXLabel;
    QLabel *offsetYLabel;
    QVBoxLayout *offsetSpinBoxes;
    QSpinBox *offsetXSpinBox;
    QSpinBox *offsetYSpinBox;
    QVBoxLayout *pixelFormat;
    QLabel *pixelFormatLabel;
    QComboBox *pixelFormatComboBox;
    QVBoxLayout *expoOptions;
    QLabel *expoOptionsLabel;
    QComboBox *expoOptionsComboBox;
    QVBoxLayout *expoOptions_2;
    QLabel *gainOptionsLabel;
    QComboBox *gainOptionsComboBox;

    void setupUi(QDialog *SettingsWindow)
    {
        if (SettingsWindow->objectName().isEmpty())
            SettingsWindow->setObjectName(QStringLiteral("SettingsWindow"));
        SettingsWindow->setWindowModality(Qt::ApplicationModal);
        SettingsWindow->resize(496, 351);
        SettingsWindow->setStyleSheet(QStringLiteral(""));
        layoutWidget = new QWidget(SettingsWindow);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 310, 351, 27));
        bottomButtons = new QHBoxLayout(layoutWidget);
        bottomButtons->setObjectName(QStringLiteral("bottomButtons"));
        bottomButtons->setContentsMargins(0, 0, 0, 0);
        dvButton = new QPushButton(layoutWidget);
        dvButton->setObjectName(QStringLiteral("dvButton"));

        bottomButtons->addWidget(dvButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        bottomButtons->addItem(horizontalSpacer);

        okButton = new QPushButton(layoutWidget);
        okButton->setObjectName(QStringLiteral("okButton"));

        bottomButtons->addWidget(okButton);

        layoutWidget1 = new QWidget(SettingsWindow);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(12, 15, 251, 292));
        sliders = new QVBoxLayout(layoutWidget1);
        sliders->setObjectName(QStringLiteral("sliders"));
        sliders->setContentsMargins(0, 0, 0, 0);
        fpsBar = new QVBoxLayout();
        fpsBar->setObjectName(QStringLiteral("fpsBar"));
        fpsLabel = new QLabel(layoutWidget1);
        fpsLabel->setObjectName(QStringLiteral("fpsLabel"));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        fpsLabel->setPalette(palette);
        QFont font;
        font.setFamily(QStringLiteral("MS Shell Dlg 2"));
        font.setBold(false);
        font.setWeight(50);
        fpsLabel->setFont(font);

        fpsBar->addWidget(fpsLabel);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        fpsSlider = new QSlider(layoutWidget1);
        fpsSlider->setObjectName(QStringLiteral("fpsSlider"));
        fpsSlider->setMinimum(1);
        fpsSlider->setMaximum(90);
        fpsSlider->setPageStep(2);
        fpsSlider->setValue(90);
        fpsSlider->setSliderPosition(90);
        fpsSlider->setOrientation(Qt::Horizontal);
        fpsSlider->setTickPosition(QSlider::NoTicks);

        horizontalLayout->addWidget(fpsSlider);

        fpsSpinBox = new QSpinBox(layoutWidget1);
        fpsSpinBox->setObjectName(QStringLiteral("fpsSpinBox"));
        fpsSpinBox->setMinimum(1);
        fpsSpinBox->setMaximum(90);
        fpsSpinBox->setValue(90);

        horizontalLayout->addWidget(fpsSpinBox);


        horizontalLayout_2->addLayout(horizontalLayout);


        fpsBar->addLayout(horizontalLayout_2);


        sliders->addLayout(fpsBar);

        frameBar = new QVBoxLayout();
        frameBar->setObjectName(QStringLiteral("frameBar"));
        frameLabel = new QLabel(layoutWidget1);
        frameLabel->setObjectName(QStringLiteral("frameLabel"));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        frameLabel->setPalette(palette1);
        QFont font1;
        font1.setFamily(QStringLiteral("MS Shell Dlg 2"));
        frameLabel->setFont(font1);

        frameBar->addWidget(frameLabel);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        frameSlider = new QSlider(layoutWidget1);
        frameSlider->setObjectName(QStringLiteral("frameSlider"));
        frameSlider->setMinimum(1);
        frameSlider->setMaximum(1000);
        frameSlider->setValue(10);
        frameSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_7->addWidget(frameSlider);

        frameSpinBox = new QSpinBox(layoutWidget1);
        frameSpinBox->setObjectName(QStringLiteral("frameSpinBox"));
        frameSpinBox->setMinimum(1);
        frameSpinBox->setMaximum(1000);
        frameSpinBox->setValue(10);

        horizontalLayout_7->addWidget(frameSpinBox);


        frameBar->addLayout(horizontalLayout_7);


        sliders->addLayout(frameBar);

        gammaBar = new QVBoxLayout();
        gammaBar->setObjectName(QStringLiteral("gammaBar"));
        gammaLabel = new QLabel(layoutWidget1);
        gammaLabel->setObjectName(QStringLiteral("gammaLabel"));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        gammaLabel->setPalette(palette2);
        gammaLabel->setFont(font1);

        gammaBar->addWidget(gammaLabel);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        gammaSlider = new QSlider(layoutWidget1);
        gammaSlider->setObjectName(QStringLiteral("gammaSlider"));
        gammaSlider->setCursor(QCursor(Qt::ArrowCursor));
        gammaSlider->setMouseTracking(false);
        gammaSlider->setMinimum(25);
        gammaSlider->setMaximum(200);
        gammaSlider->setSingleStep(1);
        gammaSlider->setPageStep(10);
        gammaSlider->setValue(100);
        gammaSlider->setOrientation(Qt::Horizontal);
        gammaSlider->setInvertedAppearance(false);
        gammaSlider->setInvertedControls(false);

        horizontalLayout_4->addWidget(gammaSlider);

        gammaSpinBox = new QSpinBox(layoutWidget1);
        gammaSpinBox->setObjectName(QStringLiteral("gammaSpinBox"));
        gammaSpinBox->setMinimum(25);
        gammaSpinBox->setMaximum(200);
        gammaSpinBox->setSingleStep(1);
        gammaSpinBox->setValue(100);

        horizontalLayout_4->addWidget(gammaSpinBox);


        gammaBar->addLayout(horizontalLayout_4);


        sliders->addLayout(gammaBar);

        expoTimeBar = new QVBoxLayout();
        expoTimeBar->setObjectName(QStringLiteral("expoTimeBar"));
        expoLabel = new QLabel(layoutWidget1);
        expoLabel->setObjectName(QStringLiteral("expoLabel"));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        expoLabel->setPalette(palette3);
        expoLabel->setFont(font);

        expoTimeBar->addWidget(expoLabel);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        expoSlider = new QSlider(layoutWidget1);
        expoSlider->setObjectName(QStringLiteral("expoSlider"));
        expoSlider->setMinimum(10);
        expoSlider->setMaximum(1000000);
        expoSlider->setPageStep(50);
        expoSlider->setValue(20);
        expoSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(expoSlider);

        expoSpinBox = new QSpinBox(layoutWidget1);
        expoSpinBox->setObjectName(QStringLiteral("expoSpinBox"));
        expoSpinBox->setMinimum(10);
        expoSpinBox->setMaximum(1000000);
        expoSpinBox->setValue(20);

        horizontalLayout_5->addWidget(expoSpinBox);


        expoTimeBar->addLayout(horizontalLayout_5);


        sliders->addLayout(expoTimeBar);

        expoTimeBar_2 = new QVBoxLayout();
        expoTimeBar_2->setObjectName(QStringLiteral("expoTimeBar_2"));
        gainLabel = new QLabel(layoutWidget1);
        gainLabel->setObjectName(QStringLiteral("gainLabel"));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        gainLabel->setPalette(palette4);
        gainLabel->setFont(font);

        expoTimeBar_2->addWidget(gainLabel);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        gainSlider = new QSlider(layoutWidget1);
        gainSlider->setObjectName(QStringLiteral("gainSlider"));
        gainSlider->setMinimum(0);
        gainSlider->setMaximum(24);
        gainSlider->setPageStep(5);
        gainSlider->setValue(20);
        gainSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_6->addWidget(gainSlider);

        gainSpinBox = new QSpinBox(layoutWidget1);
        gainSpinBox->setObjectName(QStringLiteral("gainSpinBox"));
        gainSpinBox->setMinimum(0);
        gainSpinBox->setMaximum(24);
        gainSpinBox->setValue(20);

        horizontalLayout_6->addWidget(gainSpinBox);


        expoTimeBar_2->addLayout(horizontalLayout_6);


        sliders->addLayout(expoTimeBar_2);

        layoutWidget2 = new QWidget(SettingsWindow);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(280, 10, 201, 287));
        verticalLayout = new QVBoxLayout(layoutWidget2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        resolution = new QVBoxLayout();
        resolution->setObjectName(QStringLiteral("resolution"));
        resLabel = new QLabel(layoutWidget2);
        resLabel->setObjectName(QStringLiteral("resLabel"));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        resLabel->setPalette(palette5);

        resolution->addWidget(resLabel);

        resBox = new QComboBox(layoutWidget2);
        resBox->setObjectName(QStringLiteral("resBox"));

        resolution->addWidget(resBox);


        verticalLayout->addLayout(resolution);

        offset = new QHBoxLayout();
        offset->setObjectName(QStringLiteral("offset"));
        offsetLabels = new QVBoxLayout();
        offsetLabels->setObjectName(QStringLiteral("offsetLabels"));
        offsetXLabel = new QLabel(layoutWidget2);
        offsetXLabel->setObjectName(QStringLiteral("offsetXLabel"));
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette6.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        offsetXLabel->setPalette(palette6);

        offsetLabels->addWidget(offsetXLabel);

        offsetYLabel = new QLabel(layoutWidget2);
        offsetYLabel->setObjectName(QStringLiteral("offsetYLabel"));
        QPalette palette7;
        palette7.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette7.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        offsetYLabel->setPalette(palette7);

        offsetLabels->addWidget(offsetYLabel);


        offset->addLayout(offsetLabels);

        offsetSpinBoxes = new QVBoxLayout();
        offsetSpinBoxes->setObjectName(QStringLiteral("offsetSpinBoxes"));
        offsetXSpinBox = new QSpinBox(layoutWidget2);
        offsetXSpinBox->setObjectName(QStringLiteral("offsetXSpinBox"));
        offsetXSpinBox->setMaximum(2592);
        offsetXSpinBox->setSingleStep(2);

        offsetSpinBoxes->addWidget(offsetXSpinBox);

        offsetYSpinBox = new QSpinBox(layoutWidget2);
        offsetYSpinBox->setObjectName(QStringLiteral("offsetYSpinBox"));
        offsetYSpinBox->setMaximum(1944);
        offsetYSpinBox->setSingleStep(2);

        offsetSpinBoxes->addWidget(offsetYSpinBox);


        offset->addLayout(offsetSpinBoxes);


        verticalLayout->addLayout(offset);

        pixelFormat = new QVBoxLayout();
        pixelFormat->setObjectName(QStringLiteral("pixelFormat"));
        pixelFormatLabel = new QLabel(layoutWidget2);
        pixelFormatLabel->setObjectName(QStringLiteral("pixelFormatLabel"));

        pixelFormat->addWidget(pixelFormatLabel);

        pixelFormatComboBox = new QComboBox(layoutWidget2);
        pixelFormatComboBox->setObjectName(QStringLiteral("pixelFormatComboBox"));

        pixelFormat->addWidget(pixelFormatComboBox);


        verticalLayout->addLayout(pixelFormat);

        expoOptions = new QVBoxLayout();
        expoOptions->setObjectName(QStringLiteral("expoOptions"));
        expoOptionsLabel = new QLabel(layoutWidget2);
        expoOptionsLabel->setObjectName(QStringLiteral("expoOptionsLabel"));
        QPalette palette8;
        palette8.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette8.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette8.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        expoOptionsLabel->setPalette(palette8);

        expoOptions->addWidget(expoOptionsLabel);

        expoOptionsComboBox = new QComboBox(layoutWidget2);
        expoOptionsComboBox->setObjectName(QStringLiteral("expoOptionsComboBox"));

        expoOptions->addWidget(expoOptionsComboBox);


        verticalLayout->addLayout(expoOptions);

        expoOptions_2 = new QVBoxLayout();
        expoOptions_2->setObjectName(QStringLiteral("expoOptions_2"));
        gainOptionsLabel = new QLabel(layoutWidget2);
        gainOptionsLabel->setObjectName(QStringLiteral("gainOptionsLabel"));
        QPalette palette9;
        palette9.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette9.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette9.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        gainOptionsLabel->setPalette(palette9);

        expoOptions_2->addWidget(gainOptionsLabel);

        gainOptionsComboBox = new QComboBox(layoutWidget2);
        gainOptionsComboBox->setObjectName(QStringLiteral("gainOptionsComboBox"));

        expoOptions_2->addWidget(gainOptionsComboBox);


        verticalLayout->addLayout(expoOptions_2);


        retranslateUi(SettingsWindow);
        QObject::connect(expoSpinBox, SIGNAL(valueChanged(int)), expoSlider, SLOT(setValue(int)));
        QObject::connect(expoSlider, SIGNAL(valueChanged(int)), expoSpinBox, SLOT(setValue(int)));
        QObject::connect(fpsSpinBox, SIGNAL(valueChanged(int)), fpsSlider, SLOT(setValue(int)));
        QObject::connect(fpsSlider, SIGNAL(valueChanged(int)), fpsSpinBox, SLOT(setValue(int)));
        QObject::connect(gammaSlider, SIGNAL(valueChanged(int)), gammaSpinBox, SLOT(setValue(int)));
        QObject::connect(gammaSpinBox, SIGNAL(valueChanged(int)), gammaSlider, SLOT(setValue(int)));
        QObject::connect(okButton, SIGNAL(clicked()), SettingsWindow, SLOT(accept()));
        QObject::connect(frameSlider, SIGNAL(valueChanged(int)), frameSpinBox, SLOT(setValue(int)));
        QObject::connect(frameSpinBox, SIGNAL(valueChanged(int)), frameSlider, SLOT(setValue(int)));
        QObject::connect(gainSlider, SIGNAL(valueChanged(int)), gainSpinBox, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(SettingsWindow);
    } // setupUi

    void retranslateUi(QDialog *SettingsWindow)
    {
        SettingsWindow->setWindowTitle(QApplication::translate("SettingsWindow", "Settings", 0));
        dvButton->setText(QApplication::translate("SettingsWindow", "Default Values", 0));
        okButton->setText(QApplication::translate("SettingsWindow", "OK", 0));
#ifndef QT_NO_WHATSTHIS
        fpsLabel->setWhatsThis(QApplication::translate("SettingsWindow", "<html><head/><body><p>Changes the amount of frames that the chip captures per second. The maximum value will change according to the resolution selected.</p></body></html>", 0));
#endif // QT_NO_WHATSTHIS
        fpsLabel->setText(QApplication::translate("SettingsWindow", "FPS:", 0));
#ifndef QT_NO_WHATSTHIS
        fpsSlider->setWhatsThis(QApplication::translate("SettingsWindow", "<html><head/><body><p>Changes the amount of frames that the chip captures per second. The maximum value will change according to the resolution selected.</p></body></html>", 0));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_WHATSTHIS
        fpsSpinBox->setWhatsThis(QApplication::translate("SettingsWindow", "<html><head/><body><p>Changes the amount of frames that the chip captures per second. The maximum value will change according to the resolution selected.</p></body></html>", 0));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_WHATSTHIS
        frameLabel->setWhatsThis(QApplication::translate("SettingsWindow", "<html><head/><body><p>Adjusting this variable will change the amount of total frames that the camera will capture.</p></body></html>", 0));
#endif // QT_NO_WHATSTHIS
        frameLabel->setText(QApplication::translate("SettingsWindow", "Number of Images To Capture:", 0));
#ifndef QT_NO_WHATSTHIS
        frameSlider->setWhatsThis(QApplication::translate("SettingsWindow", "<html><head/><body><p>Adjusting this variable will change the amount of total frames that the camera will capture.</p></body></html>", 0));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_WHATSTHIS
        frameSpinBox->setWhatsThis(QApplication::translate("SettingsWindow", "<html><head/><body><p>Adjusting this variable will change the amount of total frames that the camera will capture.</p></body></html>", 0));
#endif // QT_NO_WHATSTHIS
        gammaLabel->setText(QApplication::translate("SettingsWindow", "Gamma:", 0));
        gammaSpinBox->setSuffix(QString());
        gammaSpinBox->setPrefix(QString());
#ifndef QT_NO_WHATSTHIS
        expoLabel->setWhatsThis(QApplication::translate("SettingsWindow", "This value determines how long will the sensor activate to capture images. The larger this value becomes, more photons will strike the sensor to cause a brighter image.", 0));
#endif // QT_NO_WHATSTHIS
        expoLabel->setText(QApplication::translate("SettingsWindow", "Exposure Time:", 0));
#ifndef QT_NO_WHATSTHIS
        expoSlider->setWhatsThis(QApplication::translate("SettingsWindow", "<html><head/><body><p>This value determines how long will the sensor activate to capture images. The larger this value becomes, more photons will strike the sensor to cause a brighter image.</p></body></html>", 0));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_WHATSTHIS
        expoSpinBox->setWhatsThis(QApplication::translate("SettingsWindow", "This value determines how long will the sensor activate to capture images. The larger this value becomes, more photons will strike the sensor to cause a brighter image.", 0));
#endif // QT_NO_WHATSTHIS
        expoSpinBox->setSuffix(QApplication::translate("SettingsWindow", "us", 0));
#ifndef QT_NO_WHATSTHIS
        gainLabel->setWhatsThis(QApplication::translate("SettingsWindow", "This value determines how long will the sensor activate to capture images. The larger this value becomes, more photons will strike the sensor to cause a brighter image.", 0));
#endif // QT_NO_WHATSTHIS
        gainLabel->setText(QApplication::translate("SettingsWindow", "Gain:", 0));
#ifndef QT_NO_WHATSTHIS
        gainSlider->setWhatsThis(QApplication::translate("SettingsWindow", "<html><head/><body><p>This value determines how long will the sensor activate to capture images. The larger this value becomes, more photons will strike the sensor to cause a brighter image.</p></body></html>", 0));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_WHATSTHIS
        gainSpinBox->setWhatsThis(QApplication::translate("SettingsWindow", "This value determines how long will the sensor activate to capture images. The larger this value becomes, more photons will strike the sensor to cause a brighter image.", 0));
#endif // QT_NO_WHATSTHIS
        gainSpinBox->setSuffix(QApplication::translate("SettingsWindow", "dB", 0));
        resLabel->setText(QApplication::translate("SettingsWindow", "Resolution:", 0));
        resBox->clear();
        resBox->insertItems(0, QStringList()
         << QApplication::translate("SettingsWindow", "2592 x 1944", 0)
         << QApplication::translate("SettingsWindow", "2304 x 1728", 0)
         << QApplication::translate("SettingsWindow", "1920 x 1440", 0)
         << QApplication::translate("SettingsWindow", "1024 x 768", 0)
         << QApplication::translate("SettingsWindow", "640 x 480", 0)
        );
        offsetXLabel->setText(QApplication::translate("SettingsWindow", "Offset X:", 0));
        offsetYLabel->setText(QApplication::translate("SettingsWindow", "Offset Y:", 0));
        pixelFormatLabel->setText(QApplication::translate("SettingsWindow", "Pixel Format:", 0));
        pixelFormatComboBox->clear();
        pixelFormatComboBox->insertItems(0, QStringList()
         << QApplication::translate("SettingsWindow", "Mono 12", 0)
         << QApplication::translate("SettingsWindow", "Mono 8", 0)
        );
        expoOptionsLabel->setText(QApplication::translate("SettingsWindow", "Exposure Options:", 0));
        expoOptionsComboBox->clear();
        expoOptionsComboBox->insertItems(0, QStringList()
         << QApplication::translate("SettingsWindow", "Continuous", 0)
         << QApplication::translate("SettingsWindow", "Once", 0)
         << QApplication::translate("SettingsWindow", "Manual", 0)
        );
        gainOptionsLabel->setText(QApplication::translate("SettingsWindow", "Gain Options:", 0));
        gainOptionsComboBox->clear();
        gainOptionsComboBox->insertItems(0, QStringList()
         << QApplication::translate("SettingsWindow", "Continuous", 0)
         << QApplication::translate("SettingsWindow", "Once", 0)
         << QApplication::translate("SettingsWindow", "Manual", 0)
        );
    } // retranslateUi

};

namespace Ui {
    class SettingsWindow: public Ui_SettingsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSWINDOW_H
