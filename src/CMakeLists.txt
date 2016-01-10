include_directories(../include)

add_definitions("-std=c++11")

find_package(Threads REQUIRED)

set(ThreadPoolSourceFile ThreadPool.cpp)
set(ThreadPoolHeaderFile ThreadPool.hpp)
add_library(ThreadPool ${ThreadPoolHeaderFile} ${ThreadPoolSourceFile})
target_link_libraries(ThreadPool ${CMAKE_THREAD_LIBS_INIT})
