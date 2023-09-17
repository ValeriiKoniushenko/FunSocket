cmake_minimum_required(VERSION 3.0...3.5)

project(FunSocket)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(clients)
add_subdirectory(examples)
add_subdirectory(libs)
add_subdirectory(servers)
