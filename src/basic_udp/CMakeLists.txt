set(SERVER udp_server)
set(CLIENT udp_client)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ../../archives)

set(INCDIRS "../../lib/boost_1_71_0")
set(LINKDIRS "../../lib/boost_1_71_0/stage/lib")


add_library(${SERVER} STATIC server.cpp udp_endpoint.cpp)
add_library(${CLIENT} STATIC client.cpp udp_endpoint.cpp)
# add_executable(${SERVER} server.cpp udp_endpoint.cpp)
# add_executable(${CLIENT} client.cpp udp_endpoint.cpp)

target_include_directories(${SERVER} PRIVATE ${INCDIRS})
target_link_directories(${SERVER} PRIVATE ${LINKDIRS})

target_include_directories(${CLIENT} PRIVATE ${INCDIRS})
target_link_directories(${CLIENT} PRIVATE ${LINKDIRS})
