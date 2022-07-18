cmake_minimum_required(VERSION 3.20)
project(tracer)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE .)