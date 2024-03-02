set(PACKET packet_test)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(${PACKET} main.cpp)

target_include_directories(${PACKET} PRIVATE ${INCDIRS})
target_link_directories(${PACKET} PRIVATE ${LINKDIRS})
target_include_directories(${PACKET} PRIVATE ${CMAKE_SOURCE_DIR}/src/basic_udp)
target_link_libraries(${PACKET}
    ${CMAKE_SOURCE_DIR}/archives/udp_client.a
    ${CMAKE_SOURCE_DIR}/archives/udp_server.a
)
