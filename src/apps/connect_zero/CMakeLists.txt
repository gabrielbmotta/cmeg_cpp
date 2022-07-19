cmake_minimum_required(VERSION 3.20)
project(connect_zero)

set(SOURCES
    main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC .)

target_link_libraries(${PROJECT_NAME} cmeg)