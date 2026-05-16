cmake_minimum_required(VERSION 4.2)
project(WinCenter)

set(CMAKE_CXX_STANDARD 20)

add_executable(WinCenter WIN32
        src/main.cpp
        src/window_centering.cpp
        src/window_centering.h
        src/hotkey.cpp
        src/hotkey.h
        src/tray.cpp
        src/tray.h
        src/settings_window.cpp
        src/settings_window.h
        src/settings.cpp
        src/settings.h
)

target_link_libraries(WinCenter PRIVATE user32 shell32 dwmapi comctl32)
target_link_options(WinCenter PRIVATE -static-libgcc -static-libstdc++ -static)