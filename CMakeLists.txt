cmake_minimum_required(VERSION 3.6)
project(dbms_study_implementation)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES_UTILS_DISK_WRITE_PERFORMANCE utils/disk_write_performance/main.cpp)
add_executable(disk_write_performance ${SOURCE_FILES_UTILS_DISK_WRITE_PERFORMANCE})