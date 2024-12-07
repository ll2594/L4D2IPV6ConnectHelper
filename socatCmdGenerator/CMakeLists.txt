project(socatCmdGenerator LANGUAGES CXX)


find_package(Qt5 COMPONENTS
        Core
        Network
        REQUIRED)


add_executable(${PROJECT_NAME} WIN32
        main.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt5::Core
        Qt5::Network
)