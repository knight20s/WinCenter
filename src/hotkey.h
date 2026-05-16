#pragma once
#include <windows.h>

// Устанавливает глобальный хук клавиатуры.
// Возвращает HHOOK, который надо передать в UninstallHotkey при выходе.
HHOOK InstallHotkey(HINSTANCE hInstance);

// Снимает хук.
void UninstallHotkey(HHOOK hook);
