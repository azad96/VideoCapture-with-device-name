#include "devicelist.h"

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <cstdlib>

using namespace cv;

int main()
{
    VideoCapture cap;
    Mat frame;
    int deviceID = 0;          // 0 = open default camera
    int apiID = CAP_MSMF;      // 0 = autodetect default API

    if (apiID == CAP_MSMF) {
        _putenv("OPENCV_VIDEOIO_MSMF_ENABLE_HW_TRANSFORMS=0");
    }
    
    DeviceList deviceList;
    std::vector<std::string> videoDevices = deviceList.GetVideoDevices();

    std::cout << "Number of video devices: " << videoDevices.size() << "\n";

    for (int i = 0; i < videoDevices.size(); i++)
        std::cout << "[" << i << "]: " << videoDevices[i] << "\n";

    std::cout << "\nEnter the id of the video device to be selected: ";
    std::cin >> deviceID;
    
    std::cout << "\nOpening video device: " << videoDevices[deviceID] << "\n";
    cap.open(deviceID, apiID); // open selected camera using selected API
    if (!cap.isOpened()) {
        std::cerr << "ERROR! Unable to open camera\n";
        return -1;
    }

    std::cout << "\nPress any key to terminate\n";
    for (;;)
    {
        // wait for a new frame from camera and store it into 'frame'
        cap.read(frame);
        // check if we succeeded
        if (frame.empty()) {
            std::cerr << "ERROR! blank frame grabbed\n";
            break;
        }
        // show live and wait for a key with timeout long enough to show images
        imshow("Live", frame);
        if (waitKey(5) >= 0)
            break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
 	return 0;
}
