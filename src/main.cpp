#include <iostream>
#include "window_centering.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "После Enter у тебя 3 секунды, чтобы переключиться на нужное окно...";
    std::cin.get();

    Sleep(3000);

    HWND hwnd = GetForegroundWindow();
    CenterWindow(hwnd);






    std::cin.get();
    return 0;
}
