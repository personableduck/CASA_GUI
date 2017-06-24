#-------------------------------------------------
#
# Project created by QtCreator 2015-08-25T12:42:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = CASA_GUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dataprocessor.cpp \
    imagecapturer.cpp \
    qcustomplot.cpp \
    settingswindow.cpp \
    backpropagationmethod.cpp \
    preparationwindow.cpp

HEADERS  += mainwindow.h \
    dataprocessor.h \
    imagecapturer.h \
    globals.h \
    qcustomplot.h \
    settingswindow.h \
    backpropagationmethod.h \
    preparationwindow.h

FORMS    += mainwindow.ui \
    settingswindow.ui \
    preparationwindow.ui

INCLUDEPATH += "D:\Basler\pylon 4\pylon\include"
INCLUDEPATH += "D:\Basler\pylon 4\genicam\library\cpp\include"

INCLUDEPATH += "D:\opencv\opencv\build\include"
INCLUDEPATH += "D:\opencv\opencv\build\include\opencv"
INCLUDEPATH += "D:\opencv\opencv\build\include\opencv2"

INCLUDEPATH += "D:\fftw\fftw-3.3.4-dll64"

LIBS += "D:\Basler\pylon 4\pylon\lib\x64\Pylon1394_MD_VC100_TL.lib"
LIBS += "D:\Basler\pylon 4\pylon\lib\x64\PylonBase_MD_VC100.lib"
LIBS += "D:\Basler\pylon 4\pylon\lib\x64\PylonBootstrapper.lib"
LIBS += "D:\Basler\pylon 4\pylon\lib\x64\PylonCLSer_MD_VC100_TL.lib"
LIBS += "D:\Basler\pylon 4\pylon\lib\x64\PylonGigE_MD_VC100_TL.lib"
LIBS += "D:\Basler\pylon 4\pylon\lib\x64\PylonGUI_MD_VC100.lib"
LIBS += "D:\Basler\pylon 4\pylon\lib\x64\PylonUsb_MD_VC100_TL.lib"
LIBS += "D:\Basler\pylon 4\pylon\lib\x64\PylonUtility_MD_VC100.lib"

LIBS += "D:\Basler\pylon 4\genicam\library\cpp\lib\win64_x64\CLAllSerial_MD_VC100_v2_3.lib"
LIBS += "D:\Basler\pylon 4\genicam\library\cpp\lib\win64_x64\CLProtocol_MD_VC100_v2_3.lib"
LIBS += "D:\Basler\pylon 4\genicam\library\cpp\lib\win64_x64\CLSerCOM.lib"
LIBS += "D:\Basler\pylon 4\genicam\library\cpp\lib\win64_x64\GCBase_MD_VC100_v2_3.lib"
LIBS += "D:\Basler\pylon 4\genicam\library\cpp\lib\win64_x64\GenApi_MD_VC100_v2_3.lib"
LIBS += "D:\Basler\pylon 4\genicam\library\cpp\lib\win64_x64\Log_MD_VC100_v2_3.lib"
LIBS += "D:\Basler\pylon 4\genicam\library\cpp\lib\win64_x64\log4cpp_MD_VC100_v2_3.lib"
LIBS += "D:\Basler\pylon 4\genicam\library\cpp\lib\win64_x64\MathParser_MD_VC100_v2_3.lib"

win32:CONFIG(release, debug|release): LIBS += "D:\opencv\opencv\build\x64\vc11\lib\opencv_calib3d249.lib"
else:win32:CONFIG(debug, debug|release): LIBS += "D:\opencv\opencv\build\x64\vc11\lib\opencv_calib3d249d.lib"
win32:CONFIG(release, debug|release): LIBS += "D:\opencv\opencv\build\x64\vc11\lib\opencv_core249.lib"
else:win32:CONFIG(debug, debug|release): LIBS += "D:\opencv\opencv\build\x64\vc11\lib\opencv_core249d.lib"
win32:CONFIG(release, debug|release): LIBS += "D:\opencv\opencv\build\x64\vc11\lib\opencv_features2d249.lib"
else:win32:CONFIG(debug, debug|release): LIBS += "D:\opencv\opencv\build\x64\vc11\lib\opencv_features2d249d.lib"
win32:CONFIG(release, debug|release): LIBS += "D:\opencv\opencv\build\x64\vc11\lib\opencv_flann249.lib"
else:win32:CONFIG(debug, debug|release): LIBS += "D:\opencv\opencv\build\x64\vc11\lib\opencv_flann249d.lib"
win32:CONFIG(release, debug|release): LIBS += "D:\opencv\opencv\build\x64\vc11\lib\opencv_highgui249.lib"
else:win32:CONFIG(debug, debug|release): LIBS += "D:\opencv\opencv\build\x64\vc11\lib\opencv_highgui249d.lib"
win32:CONFIG(release, debug|release): LIBS += "D:\opencv\opencv\build\x64\vc11\lib\opencv_imgproc249.lib"
else:win32:CONFIG(debug, debug|release): LIBS += "D:\opencv\opencv\build\x64\vc11\lib\opencv_imgproc249d.lib"
win32:CONFIG(release, debug|release): LIBS += "D:\opencv\opencv\build\x64\vc11\lib\opencv_ml249.lib"
else:win32:CONFIG(debug, debug|release): LIBS += "D:\opencv\opencv\build\x64\vc11\lib\opencv_ml249d.lib"
win32:CONFIG(release, debug|release): LIBS += "D:\opencv\opencv\build\x64\vc11\lib\opencv_objdetect249.lib"
else:win32:CONFIG(debug, debug|release): LIBS += "D:\opencv\opencv\build\x64\vc11\lib\opencv_objdetect249d.lib"
win32:CONFIG(release, debug|release): LIBS += "D:\opencv\opencv\build\x64\vc11\lib\opencv_photo249.lib"
else:win32:CONFIG(debug, debug|release): LIBS += "D:\opencv\opencv\build\x64\vc11\lib\opencv_photo249d.lib"
win32:CONFIG(release, debug|release): LIBS += "D:\opencv\opencv\build\x64\vc11\lib\opencv_stitching249.lib"
else:win32:CONFIG(debug, debug|release): LIBS += "D:\opencv\opencv\build\x64\vc11\lib\opencv_stitching249d.lib"
win32:CONFIG(release, debug|release): LIBS += "D:\opencv\opencv\build\x64\vc11\lib\opencv_superres249.lib"
else:win32:CONFIG(debug, debug|release): LIBS += "D:\opencv\opencv\build\x64\vc11\lib\opencv_superres249d.lib"
win32:CONFIG(release, debug|release): LIBS += "D:\opencv\opencv\build\x64\vc11\lib\opencv_ts249.lib"
else:win32:CONFIG(debug, debug|release): LIBS += "D:\opencv\opencv\build\x64\vc11\lib\opencv_ts249d.lib"
win32:CONFIG(release, debug|release): LIBS += "D:\opencv\opencv\build\x64\vc11\lib\opencv_video249.lib"
else:win32:CONFIG(debug, debug|release): LIBS += "D:\opencv\opencv\build\x64\vc11\lib\opencv_video249d.lib"
win32:CONFIG(release, debug|release): LIBS += "D:\opencv\opencv\build\x64\vc11\lib\opencv_videostab249.lib"
else:win32:CONFIG(debug, debug|release): LIBS += "D:\opencv\opencv\build\x64\vc11\lib\opencv_videostab249d.lib"

LIBS += "D:\fftw\fftw-3.3.4-dll64\libfftw3-3.lib"
LIBS += "D:\fftw\fftw-3.3.4-dll64\libfftw3f-3.lib"
LIBS += "D:\fftw\fftw-3.3.4-dll64\libfftw3l-3.lib"

DISTFILES +=

RESOURCES +=
