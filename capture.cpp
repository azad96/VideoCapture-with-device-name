//////////////////////////////////////////////////////////////////////////
//
// capture.cpp: Manages video capture.
// 
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
//////////////////////////////////////////////////////////////////////////

#include "capture.h"

#include <mfidl.h>

#include <codecvt>


template <class T> void SafeRelease(T **ppT)
{
    if (*ppT)
    {
        (*ppT)->Release();
        *ppT = nullptr;
    }
}


void DeviceList::Clear()
{
    for (UINT32 i = 0; i < m_cDevices; i++)
    {
        SafeRelease(&m_ppDevices[i]);
    }
    CoTaskMemFree(m_ppDevices);
    m_ppDevices = nullptr;

    m_cDevices = 0;
}


HRESULT DeviceList::EnumerateDevices()
{
    HRESULT hr = S_OK;
    IMFAttributes *pAttributes = nullptr;

    Clear();

    // Initialize an attribute store. We will use this to 
    // specify the enumeration parameters.

    hr = MFCreateAttributes(&pAttributes, 1);

    // Ask for source type = video capture devices
    if (SUCCEEDED(hr))
    {
        hr = pAttributes->SetGUID(
            MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE, 
            MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_GUID
            );
    }

    // Enumerate devices.
    if (SUCCEEDED(hr))
    {
        hr = MFEnumDeviceSources(pAttributes, &m_ppDevices, &m_cDevices);
    }

    SafeRelease(&pAttributes);

    return hr;
}


HRESULT DeviceList::GetDevice(UINT32 index, IMFActivate **ppActivate)
{
    if (index >= Count())
    {
        return E_INVALIDARG;
    }

    *ppActivate = m_ppDevices[index];
    (*ppActivate)->AddRef();

    return S_OK;
}


HRESULT DeviceList::GetDeviceName(UINT32 index, WCHAR **ppszName)
{
    if (index >= Count())
    {
        return E_INVALIDARG;
    }

    HRESULT hr = S_OK;

    hr = m_ppDevices[index]->GetAllocatedString(
        MF_DEVSOURCE_ATTRIBUTE_FRIENDLY_NAME, 
        ppszName, 
        nullptr
        );

    return hr;
}


std::vector<std::string> DeviceList::GetVideoDevices() {
    std::vector<std::string> videoDevices;
    HRESULT hr = S_OK;
    WCHAR* szFriendlyName = nullptr;

    hr = EnumerateDevices();

    if (FAILED(hr)) {
        return videoDevices;
    }

    for (UINT32 iDevice = 0; iDevice < Count(); iDevice++)
    {
        hr = GetDeviceName(iDevice, &szFriendlyName);

        if (FAILED(hr)) { return videoDevices; }

        std::wstring ws(szFriendlyName);
        std::string deviceName = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(ws);
        videoDevices.push_back(deviceName);
        CoTaskMemFree(szFriendlyName);
        szFriendlyName = nullptr;
    }
    return videoDevices;
}