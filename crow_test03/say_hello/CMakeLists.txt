cmake_minimum_required(VERSION 3.7)

project(say_hello)

set(CMAKE_CXX_STANDARD 11)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Boost COMPONENTS system filesystem REQUIRED)
find_package(Threads)
include_directories(${Boost_INCLUDE_DIRS})
add_executable(say_hello main.cpp)
target_link_libraries(say_hello ${Boost_LIBRARIES} Threads::Threads)