#pragma once
#include <windows.h>

// Сообщение, которое будет приходить от иконки трея.
// WM_APP — стандартное "начало" диапазона пользовательских сообщений.
constexpr UINT WM_TRAYICON = WM_APP + 1;

// ID пунктов меню. Любые числа, главное — уникальные.
constexpr UINT ID_TRAY_SETTINGS = 1001;
constexpr UINT ID_TRAY_EXIT     = 1002;

// Добавляет иконку в трей. hwnd — наше скрытое окно для приёма сообщений.
void AddTrayIcon(HWND hwnd);

// Убирает иконку. Вызывать перед выходом из программы.
void RemoveTrayIcon();

// Показывает контекстное меню в позиции курсора.
void ShowTrayMenu(HWND hwnd);