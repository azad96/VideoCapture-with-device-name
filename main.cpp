//////////////////////////////////////////////////////////////////////////
//
// main.cpp. Application entry-point.
// 
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
//////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <windowsx.h>
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <assert.h>
#include <strsafe.h>
#include <shlwapi.h>
#include <Dbt.h>
#include <ks.h>
#include <ksmedia.h>

#include <iostream>
#include <vector>
#include <string>
#include <locale>
#include <codecvt>

#include "capture.h"
#include "resource.h"

using namespace std;

// // Include the v6 common controls in the manifest
// #pragma comment(linker, \
//     "\"/manifestdependency:type='Win32' "\
//     "name='Microsoft.Windows.Common-Controls' "\
//     "version='6.0.0.0' "\
//     "processorArchitecture='*' "\
//     "publicKeyToken='6595b64144ccf1df' "\
//     "language='*'\"")

vector< string > _get_devices() {
    vector< string > result;
    DeviceList  g_devices;
    HRESULT hr = S_OK;

    WCHAR* szFriendlyName = NULL;
    g_devices.Clear();

    hr = g_devices.EnumerateDevices();

    if (FAILED(hr)) {
        return result;
    }

    for (UINT32 iDevice = 0; iDevice < g_devices.Count(); iDevice++)
    {

        hr = g_devices.GetDeviceName(iDevice, &szFriendlyName);

        if (FAILED(hr)) { return result; }
        wstring ws(szFriendlyName);
        std::string deviceName = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(ws);
        result.push_back(deviceName);
        CoTaskMemFree(szFriendlyName);
        szFriendlyName = NULL;
    }
    return result;
}

int main()
{
    vector<string> tmp = _get_devices();
    for (auto device_name: tmp){
       std::cout << device_name << std::endl;

    }
}
