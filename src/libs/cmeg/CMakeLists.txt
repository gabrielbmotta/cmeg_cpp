cmake_minimum_required(VERSION 3.20)
project(networking)

set(SOURCES
    tcpsocket.cpp)

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC .)