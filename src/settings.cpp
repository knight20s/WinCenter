#include "settings.h"

#include <cwchar>
#include <windows.h>
#include <shlobj.h>

namespace {
    int g_requiredPresses = 2;
    bool g_loaded = false;

    constexpr wchar_t SECTION[] = L"General";
    constexpr wchar_t KEY_PRESSES[] = L"RequiredPresses";

    // Полный путь к settings.ini.
    // Создаёт папку, если её нет. Кэширует результат.
    const wchar_t* GetSettingsPath() {
        static wchar_t path[MAX_PATH] = {0};
        if (path[0] != 0) return path;  // уже посчитан

        SHGetFolderPathW(nullptr, CSIDL_APPDATA, nullptr, 0, path);
        wcscat_s(path, MAX_PATH, L"\\WinCenter");
        CreateDirectoryW(path, nullptr);  // если уже есть — просто вернёт ошибку
        wcscat_s(path, MAX_PATH, L"\\settings.ini");
        return path;
    }

    void LoadIfNeeded() {
        if (g_loaded) return;
        g_loaded = true;

        const wchar_t* path = GetSettingsPath();
        int n = GetPrivateProfileIntW(SECTION, KEY_PRESSES, 2, path);
        if (n < 1) n = 1;
        if (n > 5) n = 5;
        g_requiredPresses = n;
    }

    void Save() {
        const wchar_t* path = GetSettingsPath();
        wchar_t buf[16];
        swprintf(buf, 16, L"%d", g_requiredPresses);
        WritePrivateProfileStringW(SECTION, KEY_PRESSES, buf, path);
    }
}

int GetRequiredPresses() {
    LoadIfNeeded();
    return g_requiredPresses;
}

void SetRequiredPresses(int n) {
    if (n < 1) n = 1;
    if (n > 5) n = 5;
    g_requiredPresses = n;
    Save();
}