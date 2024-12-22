cmake_minimum_required(VERSION 3.29)
set(CMAKE_CXX_STANDARD 20)
project(PI)

file(GLOB HEADER_FILE ${PROJECT_SOURCE_DIR}/.h)
file(GLOB SOURCE_FILE ${PROJECT_SOURCE_DIR}/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILE})