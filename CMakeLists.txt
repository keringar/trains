cmake_minimum_required(VERSION 3.15.0)
project(transparentTB VERSION 0.1.0 LANGUAGES CXX)

# Standard C++17 for WinRT
set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

# Specify UWP related settings
set(CMAKE_SYSTEM_NAME       WindowsStore)
set(CMAKE_SYSTEM_VERSION    10)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# Main executable GUI mode
add_executable(transparentTB WIN32
    src/main.cpp
    app.rc
    app.manifest
)

target_include_directories(transparentTB
    PRIVATE include
)

target_link_libraries(transparentTB
    PRIVATE WindowsApp
    PRIVATE Comctl32
)