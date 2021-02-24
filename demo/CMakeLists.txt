cmake_minimum_required(VERSION 2.8)
project(videoManager)


# Add block directories
add_subdirectory(LoginForm)
# Target
add_executable(videoManager ${DIRSRCS})
target_link_libraries(videoManager LoginForm)
