/********************************************************************************
** Form generated from reading UI file 'preparationwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREPARATIONWINDOW_H
#define UI_PREPARATIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_PreparationWindow
{
public:
    QPushButton *ConfirmButton;
    QPushButton *GoBackButton;
    QGraphicsView *GraphicsView;
    QFrame *InfoTextFrame;
    QLabel *InfoTextLabel;

    void setupUi(QDialog *PreparationWindow)
    {
        if (PreparationWindow->objectName().isEmpty())
            PreparationWindow->setObjectName(QStringLiteral("PreparationWindow"));
        PreparationWindow->resize(800, 480);
        PreparationWindow->setStyleSheet(QStringLiteral(""));
        ConfirmButton = new QPushButton(PreparationWindow);
        ConfirmButton->setObjectName(QStringLiteral("ConfirmButton"));
        ConfirmButton->setGeometry(QRect(330, 350, 141, 61));
        QFont font;
        font.setPointSize(10);
        ConfirmButton->setFont(font);
        GoBackButton = new QPushButton(PreparationWindow);
        GoBackButton->setObjectName(QStringLiteral("GoBackButton"));
        GoBackButton->setGeometry(QRect(40, 410, 91, 41));
        GoBackButton->setFont(font);
        GraphicsView = new QGraphicsView(PreparationWindow);
        GraphicsView->setObjectName(QStringLiteral("GraphicsView"));
        GraphicsView->setGeometry(QRect(290, 30, 480, 272));
        GraphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        GraphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        GraphicsView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        InfoTextFrame = new QFrame(PreparationWindow);
        InfoTextFrame->setObjectName(QStringLiteral("InfoTextFrame"));
        InfoTextFrame->setEnabled(true);
        InfoTextFrame->setGeometry(QRect(30, 30, 241, 271));
        QFont font1;
        font1.setFamily(QStringLiteral("MS Shell Dlg 2"));
        InfoTextFrame->setFont(font1);
        InfoTextFrame->setStyleSheet(QLatin1String("border: 3px solid grey;\n"
"border-radius: 10px;\n"
"background: Dimgray;"));
        InfoTextFrame->setFrameShape(QFrame::WinPanel);
        InfoTextFrame->setFrameShadow(QFrame::Raised);
        InfoTextLabel = new QLabel(InfoTextFrame);
        InfoTextLabel->setObjectName(QStringLiteral("InfoTextLabel"));
        InfoTextLabel->setGeometry(QRect(10, 10, 221, 251));
        QFont font2;
        font2.setFamily(QStringLiteral("Calibri"));
        font2.setPointSize(14);
        font2.setBold(false);
        font2.setWeight(50);
        InfoTextLabel->setFont(font2);
        InfoTextLabel->setLayoutDirection(Qt::LeftToRight);
        InfoTextLabel->setStyleSheet(QLatin1String("border: 0px;\n"
"border-radius: 0px;\n"
"color: Ghostwhite;\n"
"qproperty-wordWrap: true;"));
        InfoTextLabel->setAlignment(Qt::AlignCenter);
        InfoTextLabel->setWordWrap(true);

        retranslateUi(PreparationWindow);

        QMetaObject::connectSlotsByName(PreparationWindow);
    } // setupUi

    void retranslateUi(QDialog *PreparationWindow)
    {
        PreparationWindow->setWindowTitle(QApplication::translate("PreparationWindow", "Dialog", 0));
        ConfirmButton->setText(QApplication::translate("PreparationWindow", "Confirm", 0));
        GoBackButton->setText(QApplication::translate("PreparationWindow", "Go Back", 0));
        InfoTextLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class PreparationWindow: public Ui_PreparationWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREPARATIONWINDOW_H
