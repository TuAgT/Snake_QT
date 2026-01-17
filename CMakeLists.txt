cmake_minimum_required(VERSION 4.1)
project(QTGuiDemo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

# 包含头文件目录
include_directories(include)

# 定义源文件
set(SOURCES
    src/main.cpp
    src/SnakeGame.cpp
    src/SnakeWidget.cpp
    src/GameWindow.cpp
)

# 定义头文件
set(HEADERS
    include/SnakeGame.h
    include/SnakeWidget.h
    include/GameWindow.h
)

add_executable(QTGuiDemo ${SOURCES} ${HEADERS})
target_link_libraries(QTGuiDemo
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

