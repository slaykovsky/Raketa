cmake_minimum_required(VERSION 2.8)

project(Raketa)

add_subdirectory(src)

include_directories(src)
include_directories(include)

add_definitions("-std=c++0x -Wall")

add_executable(Raketa main.cxx)

target_link_libraries(Raketa ThreadPool)
