cmake_minimum_required(VERSION 3.5)

project(ipv6fowarder LANGUAGES CXX)

# 更改编码为UF-8
if(MSVC)
    add_compile_options(/wd4828) #屏蔽4828错误
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options( /utf-8 ) # 修改msvc默认utf-8编码支持
elseif (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexec-charset=UTF-8")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fexec-charset=UTF-8")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory(ipv6forwarder-gui)
add_subdirectory(socatCmdGenerator)

add_subdirectory(UdpForwarder_lib)








