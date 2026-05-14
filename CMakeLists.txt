cmake_minimum_required(VERSION 4.2)
project(WinCenter)

set(CMAKE_CXX_STANDARD 20)

add_executable(WinCenter src/main.cpp
        src/window_centering.cpp
        src/window_centering.h)

target_link_libraries(WinCenter PRIVATE user32 shell32 dwmapi)
target_link_options(WinCenter PRIVATE -static-libgcc -static-libstdc++ -static)
