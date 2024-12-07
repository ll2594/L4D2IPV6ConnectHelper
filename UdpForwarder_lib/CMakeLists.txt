project(ipv6fowarder_lib LANGUAGES CXX)

add_library(${PROJECT_NAME} SHARED)


set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory(include)
add_subdirectory(src)

find_package(Qt5 COMPONENTS
        Network
        REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC
        Qt5::Network)
target_include_directories(${PROJECT_NAME} PUBLIC
        include
)

# 使用AUTOMOC来自动运行moc
set_target_properties(${PROJECT_NAME} PROPERTIES
        AUTOMOC ON
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON)
