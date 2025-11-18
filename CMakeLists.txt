cmake_minimum_required(VERSION 4.0)
project(sleepy_log)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(sleepy_log main.cpp
        src/ui/mainWindow.cpp
        src/ui/mainWindow.h
        src/ui/sleepRowWidget.cpp
        src/ui/sleepRowWidget.h
)
target_link_libraries(sleepy_log
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)
