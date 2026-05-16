#include "tray.h"
#include <shellapi.h>

namespace {
    constexpr UINT TRAY_UID = 1;       // ID нашей иконки
    NOTIFYICONDATAW g_nid = {};        // данные иконки, храним глобально
}

void AddTrayIcon(HWND hwnd) {
    g_nid.cbSize           = sizeof(g_nid);
    g_nid.hWnd             = hwnd;
    g_nid.uID              = TRAY_UID;
    g_nid.uFlags           = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    g_nid.uCallbackMessage = WM_TRAYICON;
    g_nid.hIcon            = LoadIcon(nullptr, IDI_APPLICATION);
    lstrcpynW(g_nid.szTip, L"WinCenter", ARRAYSIZE(g_nid.szTip));

    Shell_NotifyIconW(NIM_ADD, &g_nid);
}

void RemoveTrayIcon() {
    Shell_NotifyIconW(NIM_DELETE, &g_nid);
}

void ShowTrayMenu(HWND hwnd) {
    POINT pt;
    GetCursorPos(&pt);

    HMENU menu = CreatePopupMenu();
    AppendMenuW(menu, MF_STRING, ID_TRAY_SETTINGS, L"Настройки");
    AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
    AppendMenuW(menu, MF_STRING, ID_TRAY_EXIT, L"Выход");

    // Костыль для корректного закрытия меню по клику вне него
    SetForegroundWindow(hwnd);

    TrackPopupMenu(menu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, hwnd, nullptr);
    DestroyMenu(menu);
}