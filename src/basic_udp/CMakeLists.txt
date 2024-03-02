set(SERVER udp_server)
set(CLIENT udp_client)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/archives)

add_library(${SERVER} STATIC server.cpp udp_endpoint.cpp)
add_library(${CLIENT} STATIC client.cpp udp_endpoint.cpp)

target_include_directories(${SERVER} PRIVATE ${INCDIRS})
target_link_directories(${SERVER} PRIVATE ${LINKDIRS})

target_include_directories(${CLIENT} PRIVATE ${INCDIRS})
target_link_directories(${CLIENT} PRIVATE ${LINKDIRS})
