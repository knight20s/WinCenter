#include "window_centering.h"

void CenterWindow(HWND hwnd) {
    RECT rect;
    GetWindowRect(hwnd, &rect);

    HMONITOR mon = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
    MONITORINFO mi;
    mi.cbSize = sizeof(mi);
    GetMonitorInfo(mon, &mi);

    // Window size
    int windowWidth = rect.right - rect.left;
    int windowHeight = rect.bottom - rect.top;

    // Size work place
    int workWidth = mi.rcWork.right - mi.rcWork.left;
    int workHeight = mi.rcWork.bottom - mi.rcWork.top;

    // new X Y
    int newX = mi.rcWork.left + (workWidth - windowWidth) / 2;
    int newY = mi.rcWork.top + (workHeight - windowHeight) / 2;

    // Move
    SetWindowPos(hwnd, nullptr, newX, newY, 0, 0,
                 SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOZORDER);
}