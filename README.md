# VideoCapture-with-device-name

This is a useful program to capture videos in OpenCV by using device names. There are some codes on the Internetfor this purpose, however they use Windows.h library. The issue with it is OpenCV and Windows have different device orders. Integrated cameras have priority and always have the device id 0. On the other hand, they might get ids different than 0 with Windows, which results in an incompatibility with OpenCV.

Instead, I used mfidl.h and mfapi.h to get the connected video devices in the same order as OpenCV expects. This repository is a simplified and modified version of https://github.com/Microsoft/Windows-classic-samples/tree/main/Samples/Win7Samples/multimedia/mediafoundation/MFCaptureToFile. I also converted the sample into a console application, and created a CMakeLists.txt file in order to run it without Visual Studio.

## Running the application
~~~
mkdir build
cd build
cmake ..
make
./video_devices
~~~
