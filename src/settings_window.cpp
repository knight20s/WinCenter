#include "settings_window.h"
#include "settings.h"
#include <commctrl.h>
#include <cwchar>

namespace {
    constexpr wchar_t SETTINGS_CLASS[] = L"WinCenterSettingsClass";
    constexpr int IDC_LABEL         = 1001;
    constexpr int IDC_SLIDER        = 1002;
    constexpr int IDC_OK_BUTTON     = 1003;
    constexpr int IDC_CANCEL_BUTTON = 1004;

    HWND g_settingsHwnd = nullptr;

    // Обновляет текст метки в зависимости от значения ползунка
    void UpdateLabel(HWND hwnd, int value) {
        wchar_t text[64];
        swprintf(text, 64, L"Количество нажатий: %d", value);
        HWND label = GetDlgItem(hwnd, IDC_LABEL);
        SetWindowTextW(label, text);
    }

    LRESULT CALLBACK SettingsWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        switch (msg) {
            case WM_CREATE: {
                CREATESTRUCT* cs = (CREATESTRUCT*)lParam;
                HINSTANCE hInst = cs->hInstance;
                int current = GetRequiredPresses();

                // Метка
                wchar_t labelText[64];
                swprintf(labelText, 64, L"Количество нажатий: %d", current);
                CreateWindowExW(
                    0, L"STATIC", labelText,
                    WS_CHILD | WS_VISIBLE,
                    20, 20, 360, 20,
                    hwnd, (HMENU)IDC_LABEL, hInst, nullptr
                );

                // Ползунок
                HWND slider = CreateWindowExW(
                    0, L"msctls_trackbar32", L"",
                    WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS,
                    20, 60, 360, 40,
                    hwnd, (HMENU)IDC_SLIDER, hInst, nullptr
                );
                SendMessageW(slider, TBM_SETRANGE, TRUE, MAKELONG(1, 5));
                SendMessageW(slider, TBM_SETPOS,   TRUE, current);

                // Кнопка OK
                CreateWindowExW(
                    0, L"BUTTON", L"OK",
                    WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
                    220, 170, 80, 30,
                    hwnd, (HMENU)IDC_OK_BUTTON, hInst, nullptr
                );

                // Кнопка Отмена
                CreateWindowExW(
                    0, L"BUTTON", L"Отмена",
                    WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                    310, 170, 80, 30,
                    hwnd, (HMENU)IDC_CANCEL_BUTTON, hInst, nullptr
                );
                return 0;
            }

            // Ползунок шлёт WM_HSCROLL родителю при изменении
            case WM_HSCROLL: {
                HWND slider = GetDlgItem(hwnd, IDC_SLIDER);
                if ((HWND)lParam == slider) {
                    int value = (int)SendMessageW(slider, TBM_GETPOS, 0, 0);
                    UpdateLabel(hwnd, value);
                }
                return 0;
            }

            case WM_COMMAND:
                switch (LOWORD(wParam)) {
                    case IDC_OK_BUTTON: {
                        HWND slider = GetDlgItem(hwnd, IDC_SLIDER);
                        int value = (int)SendMessageW(slider, TBM_GETPOS, 0, 0);
                        SetRequiredPresses(value);
                        DestroyWindow(hwnd);
                        return 0;
                    }
                    case IDC_CANCEL_BUTTON:
                        DestroyWindow(hwnd);
                        return 0;
                }
                break;

            case WM_DESTROY:
                g_settingsHwnd = nullptr;
                return 0;
        }

        return DefWindowProcW(hwnd, msg, wParam, lParam);
    }

    void RegisterSettingsClass(HINSTANCE hInstance) {
        static bool registered = false;
        if (registered) return;

        WNDCLASSW wc = {};
        wc.lpfnWndProc   = SettingsWndProc;
        wc.hInstance     = hInstance;
        wc.lpszClassName = SETTINGS_CLASS;
        wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
        wc.hCursor       = LoadCursor(nullptr, IDC_ARROW);
        RegisterClassW(&wc);

        registered = true;
    }
}

void ShowSettingsWindow(HINSTANCE hInstance) {
    if (g_settingsHwnd && IsWindow(g_settingsHwnd)) {
        SetForegroundWindow(g_settingsHwnd);
        return;
    }

    RegisterSettingsClass(hInstance);

    g_settingsHwnd = CreateWindowExW(
        0,
        SETTINGS_CLASS,
        L"WinCenter — Настройки",
        WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
        CW_USEDEFAULT, CW_USEDEFAULT,
        400, 250,
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );

    ShowWindow(g_settingsHwnd, SW_SHOW);
    UpdateWindow(g_settingsHwnd);
}