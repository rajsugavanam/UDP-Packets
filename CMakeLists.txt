cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 14)

project(UDPTest)

set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_STATIC_LIBRARY_PREFIX "")

add_subdirectory(src/basic_udp)
