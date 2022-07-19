cmake_minimum_required(VERSION 3.20)
project(cmeg)

find_package(Protobuf REQUIRED)

set(SOURCES
    cmeg.cpp
    net-protocol.pb.cc)

add_library(${PROJECT_NAME} ${SOURCES})

include_directories(${PROTOBUF_INCLUDE_DIR})

target_include_directories(${PROJECT_NAME} PUBLIC .)

target_link_libraries(${PROJECT_NAME} tracer utils networking ${PROTOBUF_LIBRARY})