cmake_minimum_required(VERSION 3.29)
project(SkipList)

file(GLOB SOURCE_FILE ${PROJECT_SOURCE_DIR}/*.cpp)
file(GLOB HEADER_FILE ${PROJECT_SOURCE_DIR}/*.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILE} ${HEADER_FILE})