#include "capture.h"

#include <iostream>


int main()
{
    DeviceList deviceList;
    std::vector<std::string> tmp = deviceList.GetVideoDevices();
    for (const auto &device_name: tmp){
       std::cout << device_name << std::endl;

    }
}
