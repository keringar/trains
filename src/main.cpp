#ifndef UNICODE
#define UNICODE
#endif

// Standard Library
#include <iostream>

// Windows API
#include <windows.h>
#include <shellapi.h>
#include <commctrl.h>
#include <strsafe.h>
#include <winrt/base.h>

#include "resource.h"

using namespace winrt;

static const GUID ICON_GUID = {0x84e0a177, 0xc003, 0x4825, {0xbf, 0x45, 0x63, 0xc6, 0x0b, 0xf7, 0x71, 0x43}};

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    winrt::init_apartment(apartment_type::single_threaded);

    const wchar_t CLASS_NAME[] = L"TransparentTB Window Class";
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        WS_EX_TRANSPARENT,
        CLASS_NAME,
        L"TrayWindow",
        0,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL) {
        return -1;
    }

    NOTIFYICONDATA nid = {};
    nid.cbSize = sizeof(nid);
    nid.hWnd = hwnd;
    nid.uFlags = NIF_ICON | NIF_GUID | NIF_TIP;
    nid.guidItem = ICON_GUID;
    StringCchCopy(nid.szTip, ARRAYSIZE(nid.szTip), L"TransparentTB");
    LoadIconMetric(hInstance, MAKEINTRESOURCE(IDI_ICON), LIM_SMALL, &nid.hIcon);
    Shell_NotifyIcon(NIM_ADD, &nid);

  	MSG msg;
    BOOL bRet;
    while( (bRet = GetMessage( &msg, hwnd, 0, 0 )) != 0) { 
        if (bRet == -1) {
            break;
        } else {
            TranslateMessage(&msg); 
            DispatchMessage(&msg); 
        }
    }

    Shell_NotifyIcon(NIM_DELETE, &nid);

    return 0;
}
