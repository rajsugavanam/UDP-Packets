set(PACKET_CLIENT client_packets)
set(PACKET_SERVER server_packets)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(${PACKET_CLIENT} packet_client.cpp)
add_executable(${PACKET_SERVER} packet_server.cpp)

target_include_directories(${PACKET_SERVER} PRIVATE ${INCDIRS})
target_link_directories(${PACKET_SERVER} PRIVATE ${LINKDIRS})

target_include_directories(${PACKET_CLIENT} PRIVATE ${INCDIRS})
target_link_directories(${PACKET_CLIENT} PRIVATE ${LINKDIRS})

target_include_directories(${PACKET_CLIENT} PRIVATE ${CMAKE_SOURCE_DIR}/src/basic_udp)
target_include_directories(${PACKET_SERVER} PRIVATE ${CMAKE_SOURCE_DIR}/src/basic_udp)

target_link_libraries(${PACKET_CLIENT}
    udp_client
    udp_server
)
target_link_libraries(${PACKET_SERVER}
    udp_client
    udp_server
)
