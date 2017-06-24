# CASA_GUI
Compact and Light-Weight Automated Semen Analysis Platform Using Lensfree on-Chip Microscopy

Instructions to run the application without setting up the Qt project code.
1. Download Deployment_executable.zip.
2. Unzip the file.
3. Run CASA_GUI.exe.

Instructions for local project setup:

1. Install Qt creator (community edition)
	- choose the Qt 5.4.2 MSVC2013 OpenGL 64-bit kit
2. Install Basler Pylon v4.2.1 (64-bit)
	- If plugging in the Basler camera via USB does not automatically install
		the required driver, navigate to the
		Basler\pylon 4\bin\drivers\Basler Pylon USB Driver folder and execute
		dpinst.exe
3. Install openvc v2.4.9
4. Download fftw 64-bit or get it from Kiran to avoid having to create the .lib files
	- downloading directly will require the .lib files to be created manually.
5. Make sure all Microsoft Visual C++ redistributables are up-to-date
	- Visual Studio 2013
6. Create a new Qt Widgets Application
7. Add all existing CASA_GUI .pro, .cpp, .h, and .ui files to the project
8. Configure the CASA_GUI.pro file to contain the appropriate paths to the
	Pylon, genicam, opencv, and fftw .lib files as given in the .pro file.
9. Add the following four paths in Qt by going to the Projects window,
	scrolling down to Build Environment, clicking on Details, selecting
	the PATH variable, and clicking Edit:
	- Basler\pylon 4\pylon\bin\x64
	- Basler\pylon 4\genicam\bin\win64_x64
	- opencv\build\x64\vc11\bin
	- fftw-3.3.4-dll64
10. Make sure the ImageDatasets, Images, TempImages, and TrackCoords folders
	are all located within the release folder of the main project build directory.
