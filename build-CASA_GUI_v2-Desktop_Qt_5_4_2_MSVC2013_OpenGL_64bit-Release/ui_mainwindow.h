/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionMenu;
    QAction *actionHere;
    QAction *actionOzcan;
    QAction *actionTest;
    QAction *actionAbout;
    QWidget *centralWidget;
    QLabel *timestampLabel;
    QGraphicsView *imageViewer;
    QPushButton *zoomOutButton;
    QSlider *zAxisSlider;
    QLabel *zAxisLabel;
    QSlider *timestampSlider;
    QPushButton *zoomInButton;
    QRadioButton *relativeStatsButton;
    QRadioButton *absoluteStatsButton;
    QListWidget *statsList;
    QLabel *statsDataLabel;
    QFrame *frame;
    QCustomPlot *statsPlot;
    QRadioButton *ampReconst_button;
    QRadioButton *phaseReconst_button;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *percentMotile_label;
    QHBoxLayout *horizontalLayout_4;
    QLabel *percentProg_label;
    QHBoxLayout *horizontalLayout_5;
    QLabel *percentNonProg_label;
    QHBoxLayout *horizontalLayout_6;
    QLabel *percentImmotile_label;
    QHBoxLayout *horizontalLayout_3;
    QLabel *percentHyper_label;
    QFrame *frame_2;
    QLabel *result_label;
    QSpinBox *timestamp_spinBox;
    QSpinBox *zAxis_spinBox;
    QPushButton *confirmButton;
    QRadioButton *rawHologramButton;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QDoubleSpinBox *percentMotile_spinBox;
    QDoubleSpinBox *percentProg_spinBox;
    QDoubleSpinBox *percentNonProg_spinBox;
    QDoubleSpinBox *percentImmotile_spinBox;
    QDoubleSpinBox *percentHyper_spinBox;
    QPushButton *restartButton;
    QPushButton *tutorialButton;
    QPushButton *helpButton;
    QPushButton *printButton;
    QWidget *tut_overlay_1;
    QWidget *tut_overlay_2;
    QWidget *tut_overlay_3;
    QWidget *tut_overlay_4;
    QFrame *tut_frame;
    QTextEdit *tut_msg;
    QPushButton *tut_ok_button;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QButtonGroup *buttonGroup_2;
    QButtonGroup *buttonGroup;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1920, 1080);
        MainWindow->setFocusPolicy(Qt::StrongFocus);
        MainWindow->setStyleSheet(QStringLiteral(""));
        actionMenu = new QAction(MainWindow);
        actionMenu->setObjectName(QStringLiteral("actionMenu"));
        actionHere = new QAction(MainWindow);
        actionHere->setObjectName(QStringLiteral("actionHere"));
        actionOzcan = new QAction(MainWindow);
        actionOzcan->setObjectName(QStringLiteral("actionOzcan"));
        actionTest = new QAction(MainWindow);
        actionTest->setObjectName(QStringLiteral("actionTest"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        timestampLabel = new QLabel(centralWidget);
        timestampLabel->setObjectName(QStringLiteral("timestampLabel"));
        timestampLabel->setGeometry(QRect(1050, 685, 71, 16));
        imageViewer = new QGraphicsView(centralWidget);
        imageViewer->setObjectName(QStringLiteral("imageViewer"));
        imageViewer->setGeometry(QRect(1050, 69, 800, 601));
        imageViewer->setStyleSheet(QStringLiteral(""));
        imageViewer->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        imageViewer->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        imageViewer->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        imageViewer->setDragMode(QGraphicsView::ScrollHandDrag);
        zoomOutButton = new QPushButton(centralWidget);
        zoomOutButton->setObjectName(QStringLiteral("zoomOutButton"));
        zoomOutButton->setGeometry(QRect(1790, 615, 31, 31));
        zoomOutButton->setFocusPolicy(Qt::NoFocus);
        zoomOutButton->setStyleSheet(QStringLiteral("background-color:rgba(255, 255, 255, 200);"));
        zAxisSlider = new QSlider(centralWidget);
        zAxisSlider->setObjectName(QStringLiteral("zAxisSlider"));
        zAxisSlider->setGeometry(QRect(1130, 715, 651, 20));
        zAxisSlider->setFocusPolicy(Qt::NoFocus);
        zAxisSlider->setMaximum(5000);
        zAxisSlider->setPageStep(1);
        zAxisSlider->setValue(1000);
        zAxisSlider->setOrientation(Qt::Horizontal);
        zAxisLabel = new QLabel(centralWidget);
        zAxisLabel->setObjectName(QStringLiteral("zAxisLabel"));
        zAxisLabel->setGeometry(QRect(1050, 715, 71, 16));
        timestampSlider = new QSlider(centralWidget);
        timestampSlider->setObjectName(QStringLiteral("timestampSlider"));
        timestampSlider->setGeometry(QRect(1130, 685, 651, 20));
        timestampSlider->setFocusPolicy(Qt::NoFocus);
        timestampSlider->setMaximum(74);
        timestampSlider->setPageStep(1);
        timestampSlider->setOrientation(Qt::Horizontal);
        timestampSlider->setTickPosition(QSlider::NoTicks);
        zoomInButton = new QPushButton(centralWidget);
        zoomInButton->setObjectName(QStringLiteral("zoomInButton"));
        zoomInButton->setGeometry(QRect(1790, 585, 31, 31));
        zoomInButton->setFocusPolicy(Qt::NoFocus);
        zoomInButton->setStyleSheet(QStringLiteral("background-color:rgba(255, 255, 255, 200);"));
        relativeStatsButton = new QRadioButton(centralWidget);
        buttonGroup = new QButtonGroup(MainWindow);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(relativeStatsButton);
        relativeStatsButton->setObjectName(QStringLiteral("relativeStatsButton"));
        relativeStatsButton->setEnabled(false);
        relativeStatsButton->setGeometry(QRect(200, 280, 111, 20));
        QFont font;
        font.setPointSize(9);
        relativeStatsButton->setFont(font);
        relativeStatsButton->setFocusPolicy(Qt::NoFocus);
        relativeStatsButton->setChecked(true);
        absoluteStatsButton = new QRadioButton(centralWidget);
        buttonGroup->addButton(absoluteStatsButton);
        absoluteStatsButton->setObjectName(QStringLiteral("absoluteStatsButton"));
        absoluteStatsButton->setEnabled(false);
        absoluteStatsButton->setGeometry(QRect(200, 300, 111, 20));
        absoluteStatsButton->setFont(font);
        absoluteStatsButton->setFocusPolicy(Qt::NoFocus);
        statsList = new QListWidget(centralWidget);
        statsList->setObjectName(QStringLiteral("statsList"));
        statsList->setGeometry(QRect(40, 80, 131, 401));
        QFont font1;
        font1.setFamily(QStringLiteral("MS Shell Dlg 2"));
        font1.setPointSize(10);
        statsList->setFont(font1);
        statsList->setFocusPolicy(Qt::WheelFocus);
        statsDataLabel = new QLabel(centralWidget);
        statsDataLabel->setObjectName(QStringLiteral("statsDataLabel"));
        statsDataLabel->setGeometry(QRect(30, 60, 151, 20));
        statsDataLabel->setFont(font1);
        statsDataLabel->setAlignment(Qt::AlignCenter);
        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(320, 70, 641, 481));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Plain);
        statsPlot = new QCustomPlot(frame);
        statsPlot->setObjectName(QStringLiteral("statsPlot"));
        statsPlot->setGeometry(QRect(10, 10, 620, 461));
        ampReconst_button = new QRadioButton(centralWidget);
        buttonGroup_2 = new QButtonGroup(MainWindow);
        buttonGroup_2->setObjectName(QStringLiteral("buttonGroup_2"));
        buttonGroup_2->addButton(ampReconst_button);
        ampReconst_button->setObjectName(QStringLiteral("ampReconst_button"));
        ampReconst_button->setGeometry(QRect(1050, 780, 181, 19));
        ampReconst_button->setFocusPolicy(Qt::NoFocus);
        ampReconst_button->setChecked(false);
        phaseReconst_button = new QRadioButton(centralWidget);
        buttonGroup_2->addButton(phaseReconst_button);
        phaseReconst_button->setObjectName(QStringLiteral("phaseReconst_button"));
        phaseReconst_button->setGeometry(QRect(1050, 800, 181, 19));
        phaseReconst_button->setFocusPolicy(Qt::NoFocus);
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(320, 580, 201, 165));
        layoutWidget->setFocusPolicy(Qt::NoFocus);
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        percentMotile_label = new QLabel(layoutWidget);
        percentMotile_label->setObjectName(QStringLiteral("percentMotile_label"));
        QFont font2;
        font2.setPointSize(8);
        percentMotile_label->setFont(font2);
        percentMotile_label->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(percentMotile_label);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        percentProg_label = new QLabel(layoutWidget);
        percentProg_label->setObjectName(QStringLiteral("percentProg_label"));
        percentProg_label->setFont(font2);
        percentProg_label->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_4->addWidget(percentProg_label);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        percentNonProg_label = new QLabel(layoutWidget);
        percentNonProg_label->setObjectName(QStringLiteral("percentNonProg_label"));
        percentNonProg_label->setFont(font2);
        percentNonProg_label->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_5->addWidget(percentNonProg_label);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        percentImmotile_label = new QLabel(layoutWidget);
        percentImmotile_label->setObjectName(QStringLiteral("percentImmotile_label"));
        percentImmotile_label->setFont(font2);
        percentImmotile_label->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_6->addWidget(percentImmotile_label);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        percentHyper_label = new QLabel(layoutWidget);
        percentHyper_label->setObjectName(QStringLiteral("percentHyper_label"));
        percentHyper_label->setFont(font2);
        percentHyper_label->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_3->addWidget(percentHyper_label);


        verticalLayout->addLayout(horizontalLayout_3);

        frame_2 = new QFrame(centralWidget);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(620, 620, 351, 80));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Plain);
        result_label = new QLabel(frame_2);
        result_label->setObjectName(QStringLiteral("result_label"));
        result_label->setGeometry(QRect(10, 10, 331, 61));
        QFont font3;
        font3.setPointSize(10);
        result_label->setFont(font3);
        result_label->setAlignment(Qt::AlignCenter);
        timestamp_spinBox = new QSpinBox(centralWidget);
        timestamp_spinBox->setObjectName(QStringLiteral("timestamp_spinBox"));
        timestamp_spinBox->setGeometry(QRect(1792, 680, 61, 22));
        zAxis_spinBox = new QSpinBox(centralWidget);
        zAxis_spinBox->setObjectName(QStringLiteral("zAxis_spinBox"));
        zAxis_spinBox->setGeometry(QRect(1792, 710, 61, 22));
        zAxis_spinBox->setMaximum(5000);
        zAxis_spinBox->setValue(1000);
        confirmButton = new QPushButton(centralWidget);
        confirmButton->setObjectName(QStringLiteral("confirmButton"));
        confirmButton->setGeometry(QRect(1790, 740, 61, 31));
        confirmButton->setFocusPolicy(Qt::StrongFocus);
        rawHologramButton = new QRadioButton(centralWidget);
        buttonGroup_2->addButton(rawHologramButton);
        rawHologramButton->setObjectName(QStringLiteral("rawHologramButton"));
        rawHologramButton->setGeometry(QRect(1050, 760, 181, 19));
        rawHologramButton->setFocusPolicy(Qt::NoFocus);
        rawHologramButton->setChecked(true);
        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(520, 580, 85, 171));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        percentMotile_spinBox = new QDoubleSpinBox(layoutWidget1);
        percentMotile_spinBox->setObjectName(QStringLiteral("percentMotile_spinBox"));
        percentMotile_spinBox->setFocusPolicy(Qt::NoFocus);
        percentMotile_spinBox->setFrame(true);
        percentMotile_spinBox->setReadOnly(true);
        percentMotile_spinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        percentMotile_spinBox->setMinimum(0);
        percentMotile_spinBox->setMaximum(100);

        verticalLayout_2->addWidget(percentMotile_spinBox);

        percentProg_spinBox = new QDoubleSpinBox(layoutWidget1);
        percentProg_spinBox->setObjectName(QStringLiteral("percentProg_spinBox"));
        percentProg_spinBox->setFocusPolicy(Qt::NoFocus);
        percentProg_spinBox->setFrame(true);
        percentProg_spinBox->setReadOnly(true);
        percentProg_spinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        percentProg_spinBox->setMinimum(0);
        percentProg_spinBox->setMaximum(100);

        verticalLayout_2->addWidget(percentProg_spinBox);

        percentNonProg_spinBox = new QDoubleSpinBox(layoutWidget1);
        percentNonProg_spinBox->setObjectName(QStringLiteral("percentNonProg_spinBox"));
        percentNonProg_spinBox->setFocusPolicy(Qt::NoFocus);
        percentNonProg_spinBox->setFrame(true);
        percentNonProg_spinBox->setReadOnly(true);
        percentNonProg_spinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        percentNonProg_spinBox->setMinimum(0);
        percentNonProg_spinBox->setMaximum(100);

        verticalLayout_2->addWidget(percentNonProg_spinBox);

        percentImmotile_spinBox = new QDoubleSpinBox(layoutWidget1);
        percentImmotile_spinBox->setObjectName(QStringLiteral("percentImmotile_spinBox"));
        percentImmotile_spinBox->setFocusPolicy(Qt::NoFocus);
        percentImmotile_spinBox->setFrame(true);
        percentImmotile_spinBox->setReadOnly(true);
        percentImmotile_spinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        percentImmotile_spinBox->setMinimum(0);
        percentImmotile_spinBox->setMaximum(100);

        verticalLayout_2->addWidget(percentImmotile_spinBox);

        percentHyper_spinBox = new QDoubleSpinBox(layoutWidget1);
        percentHyper_spinBox->setObjectName(QStringLiteral("percentHyper_spinBox"));
        percentHyper_spinBox->setFocusPolicy(Qt::NoFocus);
        percentHyper_spinBox->setFrame(true);
        percentHyper_spinBox->setReadOnly(true);
        percentHyper_spinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        percentHyper_spinBox->setMinimum(0);
        percentHyper_spinBox->setMaximum(100);

        verticalLayout_2->addWidget(percentHyper_spinBox);

        restartButton = new QPushButton(centralWidget);
        restartButton->setObjectName(QStringLiteral("restartButton"));
        restartButton->setGeometry(QRect(30, 920, 111, 41));
        restartButton->setFont(font2);
        tutorialButton = new QPushButton(centralWidget);
        tutorialButton->setObjectName(QStringLiteral("tutorialButton"));
        tutorialButton->setGeometry(QRect(1630, 20, 101, 31));
        helpButton = new QPushButton(centralWidget);
        helpButton->setObjectName(QStringLiteral("helpButton"));
        helpButton->setGeometry(QRect(1750, 20, 101, 31));
        printButton = new QPushButton(centralWidget);
        printButton->setObjectName(QStringLiteral("printButton"));
        printButton->setGeometry(QRect(1510, 20, 101, 31));
        tut_overlay_1 = new QWidget(centralWidget);
        tut_overlay_1->setObjectName(QStringLiteral("tut_overlay_1"));
        tut_overlay_1->setGeometry(QRect(0, 0, 21, 21));
        tut_overlay_2 = new QWidget(centralWidget);
        tut_overlay_2->setObjectName(QStringLiteral("tut_overlay_2"));
        tut_overlay_2->setGeometry(QRect(0, 20, 21, 21));
        tut_overlay_3 = new QWidget(centralWidget);
        tut_overlay_3->setObjectName(QStringLiteral("tut_overlay_3"));
        tut_overlay_3->setGeometry(QRect(0, 40, 21, 21));
        tut_overlay_4 = new QWidget(centralWidget);
        tut_overlay_4->setObjectName(QStringLiteral("tut_overlay_4"));
        tut_overlay_4->setGeometry(QRect(0, 60, 21, 21));
        tut_frame = new QFrame(centralWidget);
        tut_frame->setObjectName(QStringLiteral("tut_frame"));
        tut_frame->setEnabled(true);
        tut_frame->setGeometry(QRect(10, 490, 191, 101));
        QFont font4;
        font4.setFamily(QStringLiteral("MS Shell Dlg 2"));
        tut_frame->setFont(font4);
        tut_frame->setStyleSheet(QLatin1String("border: 3px solid grey;\n"
"border-radius: 10px;\n"
"background: Lightgoldenrodyellow;"));
        tut_frame->setFrameShape(QFrame::WinPanel);
        tut_frame->setFrameShadow(QFrame::Raised);
        tut_msg = new QTextEdit(tut_frame);
        tut_msg->setObjectName(QStringLiteral("tut_msg"));
        tut_msg->setEnabled(true);
        tut_msg->setGeometry(QRect(10, 10, 131, 81));
        QFont font5;
        font5.setFamily(QStringLiteral("MS Shell Dlg 2"));
        font5.setPointSize(8);
        tut_msg->setFont(font5);
        tut_msg->setStyleSheet(QLatin1String("border: 0px;\n"
"border-radius: 0px;"));
        tut_msg->setFrameShadow(QFrame::Plain);
        tut_msg->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tut_msg->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tut_msg->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        tut_msg->setUndoRedoEnabled(true);
        tut_msg->setReadOnly(true);
        tut_msg->setTextInteractionFlags(Qt::NoTextInteraction);
        tut_ok_button = new QPushButton(centralWidget);
        tut_ok_button->setObjectName(QStringLiteral("tut_ok_button"));
        tut_ok_button->setGeometry(QRect(210, 520, 30, 40));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1920, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(timestampSlider, SIGNAL(valueChanged(int)), timestamp_spinBox, SLOT(setValue(int)));
        QObject::connect(zAxisSlider, SIGNAL(valueChanged(int)), zAxis_spinBox, SLOT(setValue(int)));
        QObject::connect(timestamp_spinBox, SIGNAL(valueChanged(int)), timestampSlider, SLOT(setValue(int)));
        QObject::connect(zAxis_spinBox, SIGNAL(valueChanged(int)), zAxisSlider, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "CASA GUI", 0));
        actionMenu->setText(QApplication::translate("MainWindow", "menu", 0));
        actionHere->setText(QApplication::translate("MainWindow", "Here", 0));
        actionOzcan->setText(QApplication::translate("MainWindow", "Ozcan", 0));
        actionOzcan->setShortcut(QApplication::translate("MainWindow", "O, Z", 0));
        actionTest->setText(QApplication::translate("MainWindow", "Test", 0));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0));
        timestampLabel->setText(QApplication::translate("MainWindow", "Timestamp:", 0));
        zoomOutButton->setText(QApplication::translate("MainWindow", "-", 0));
        zAxisLabel->setText(QApplication::translate("MainWindow", "Z-axis (\302\265m):", 0));
        zoomInButton->setText(QApplication::translate("MainWindow", "+", 0));
        relativeStatsButton->setText(QApplication::translate("MainWindow", "Relative (%)", 0));
        absoluteStatsButton->setText(QApplication::translate("MainWindow", "Absolute (#)", 0));
        statsDataLabel->setText(QApplication::translate("MainWindow", "Motility Parameters", 0));
        ampReconst_button->setText(QApplication::translate("MainWindow", "Amplitude Reconstruction", 0));
        phaseReconst_button->setText(QApplication::translate("MainWindow", "Phase Reconstruction", 0));
        percentMotile_label->setText(QApplication::translate("MainWindow", "Percent Motile:", 0));
        percentProg_label->setText(QApplication::translate("MainWindow", "Percent Progressively Motile:", 0));
        percentNonProg_label->setText(QApplication::translate("MainWindow", "Percent Non-Progressively Motile:", 0));
        percentImmotile_label->setText(QApplication::translate("MainWindow", "Percent Immotile:", 0));
        percentHyper_label->setText(QApplication::translate("MainWindow", "Percent Hyperactivated: ", 0));
        result_label->setText(QString());
        confirmButton->setText(QApplication::translate("MainWindow", "Confirm", 0));
        rawHologramButton->setText(QApplication::translate("MainWindow", "Raw Hologram", 0));
        percentMotile_spinBox->setSuffix(QApplication::translate("MainWindow", "%", 0));
        percentProg_spinBox->setSuffix(QApplication::translate("MainWindow", "%", 0));
        percentNonProg_spinBox->setSuffix(QApplication::translate("MainWindow", "%", 0));
        percentImmotile_spinBox->setSuffix(QApplication::translate("MainWindow", "%", 0));
        percentHyper_spinBox->setSuffix(QApplication::translate("MainWindow", "%", 0));
        restartButton->setText(QApplication::translate("MainWindow", "Restart", 0));
        tutorialButton->setText(QApplication::translate("MainWindow", "Tutorial", 0));
        helpButton->setText(QApplication::translate("MainWindow", "Help", 0));
        printButton->setText(QApplication::translate("MainWindow", "Print", 0));
        tut_msg->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", 0));
        tut_ok_button->setText(QApplication::translate("MainWindow", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
