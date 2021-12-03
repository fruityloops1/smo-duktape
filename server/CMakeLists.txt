cmake_minimum_required(VERSION 3.5)
project(smo-duktape-server)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(smo-duktape-server src/smo-server.cpp include/server.h src/server.cpp include/packet.h src/packet.cpp src/types.cpp)

find_package(Threads REQUIRED)
target_link_libraries(smo-duktape-server PRIVATE Threads::Threads)