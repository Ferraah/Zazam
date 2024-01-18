cmake_minimum_required(VERSION 3.10)

project(ZAZAM VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_library(ZAZAM SHARED ${SOURCES})

# Find Eigen3
find_package(Eigen3 REQUIRED NO_MODULE
    HINTS $ENV{mkEigenPrefix})


target_link_libraries(ZAZAM PUBLIC Eigen3::Eigen)

add_executable(test.out tests/test.cpp)
target_link_libraries(test.out PUBLIC ZAZAM)
#target_include_directories(test.out PUBLIC "${PROJECT_SOURCE_DIR}/src" ${EIGEN3_INCLUDE_DIR})