cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 14)

project(UDPTest)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_STATIC_LIBRARY_PREFIX "")

set(INCDIRS ${CMAKE_SOURCE_DIR}/lib/boost_1_71_0)
set(LINKDIRS ${CMAKE_SOURCE_DIR}/lib/boost_1_71_0/stage/lib)

add_subdirectory(src/basic_udp)
add_subdirectory(src/packet_handling)
