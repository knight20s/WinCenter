#include "window_centering.h"

void CenterWindow(HWND hwnd) {
    RECT rect;
    GetWindowRect(hwnd, &rect);

    // Window size
    int windowWidth = rect.right - rect.left;
    int windowHeight = rect.bottom - rect.top;

    // Size work place
    RECT workArea;
    SystemParametersInfoW(SPI_GETWORKAREA, 0, &workArea, 0);
    int workWidth = workArea.right - workArea.left;
    int workHeight = workArea.bottom - workArea.top;

    // new X Y
    int newX = workArea.left + (workWidth  - windowWidth)  / 2;
    int newY = workArea.top  + (workHeight - windowHeight) / 2;

    // Move
    SetWindowPos(hwnd, nullptr, newX, newY, 0, 0,
                 SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOZORDER);

}