//////////////////////////////////////////////////////////////////////////
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
//////////////////////////////////////////////////////////////////////////

#pragma once

#include <mfapi.h>

#include <string>
#include <vector>


class DeviceList
{
public:
    DeviceList() :  m_cDevices(0), m_ppDevices(nullptr) {}
    ~DeviceList() { Clear(); }
    
    UINT32  Count() const { return m_cDevices; }

    std::vector<std::string> GetVideoDevices();

private:
    void    Clear();
    HRESULT EnumerateDevices();
    HRESULT GetDevice(UINT32 index, IMFActivate **ppActivate);
    HRESULT GetDeviceName(UINT32 index, WCHAR **ppszName);


    UINT32      m_cDevices;
    IMFActivate **m_ppDevices;
};
