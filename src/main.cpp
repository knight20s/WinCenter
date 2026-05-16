#include <windows.h>
#include <commctrl.h>
#include "hotkey.h"
#include "tray.h"
#include "settings_window.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_TRAYICON:
            if (lParam == WM_RBUTTONUP) {
                ShowTrayMenu(hwnd);
            }
            return 0;

        case WM_COMMAND:
            switch (LOWORD(wParam)) {
            case ID_TRAY_EXIT:
                    DestroyWindow(hwnd);
                    return 0;
            case ID_TRAY_SETTINGS:
                    ShowSettingsWindow((HINSTANCE)GetWindowLongPtrW(hwnd, GWLP_HINSTANCE));
                    return 0;
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    INITCOMMONCONTROLSEX icc = { sizeof(icc), ICC_STANDARD_CLASSES | ICC_BAR_CLASSES };
    InitCommonControlsEx(&icc);

    WNDCLASSW wc = {};
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = L"WinCenterClass";
    RegisterClassW(&wc);

    HWND hwnd = CreateWindowExW(
        0, L"WinCenterClass", L"WinCenter",
        0, 0, 0, 0, 0,
        HWND_MESSAGE, nullptr, hInstance, nullptr
    );

    HHOOK hook = InstallHotkey(hInstance);
    AddTrayIcon(hwnd);

    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    RemoveTrayIcon();
    UninstallHotkey(hook);
    return 0;
}