cmake_minimum_required(VERSION 3.7)

project(bestsellingbooks)

set(CMAKE_CXX_STANDARD 11)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Boost COMPONENTS system filesystem REQUIRED)
find_package(Threads)

include_directories(${CMAKE_SOURCE_DIR}/jsoncons)
include_directories(${Boost_INCLUDE_DIRS})
add_executable(bestsellingbooks main.cpp)
target_link_libraries(bestsellingbooks ${Boost_LIBRARIES} Threads::Threads)
