#include "hotkey.h"
#include "window_centering.h"
#include "settings.h"

namespace {
    constexpr DWORD DOUBLE_TAP_TIMEOUT_MS = 400;

    int   g_pressCount = 0;
    DWORD g_lastPress  = 0;

    LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
        if (nCode == HC_ACTION) {
            KBDLLHOOKSTRUCT* kb = (KBDLLHOOKSTRUCT*)lParam;

            if (wParam == WM_KEYDOWN && kb->vkCode == VK_RSHIFT) {
                DWORD now = GetTickCount();
                if (now - g_lastPress > DOUBLE_TAP_TIMEOUT_MS) {
                    g_pressCount = 0;
                }
                g_pressCount++;
                g_lastPress = now;

                if (g_pressCount >= GetRequiredPresses()) {
                    CenterWindow(GetForegroundWindow());
                    g_pressCount = 0;
                }
            }
        }
        return CallNextHookEx(nullptr, nCode, wParam, lParam);
    }
}

HHOOK InstallHotkey(HINSTANCE hInstance) {
    return SetWindowsHookExW(WH_KEYBOARD_LL, KeyboardProc, hInstance, 0);
}

void UninstallHotkey(HHOOK hook) {
    UnhookWindowsHookEx(hook);
}