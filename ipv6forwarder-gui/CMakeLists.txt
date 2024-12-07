project(ipv6fowarder-gui LANGUAGES CXX)


find_package(Qt5 COMPONENTS
        Widgets
        REQUIRED)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_executable(${PROJECT_NAME} WIN32
        main.cpp
        widget.cpp
        widget.h
        widget.ui
)
target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt5::Widgets
        ipv6fowarder_lib
)
