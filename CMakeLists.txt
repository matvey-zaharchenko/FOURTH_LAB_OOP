cmake_minimum_required(VERSION 3.10)
project(lab04)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Используем системный gtest вместо FetchContent
find_package(GTest REQUIRED)

add_library(${CMAKE_PROJECT_NAME}_lib INTERFACE
    include/figure.h
    include/rectangle.h
    include/triangle.h
    include/square.h
    include/array.h
    include/point.h
)

target_include_directories(${CMAKE_PROJECT_NAME}_lib INTERFACE include)

add_executable(${CMAKE_PROJECT_NAME}_out main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME}_out PRIVATE ${CMAKE_PROJECT_NAME}_lib)

enable_testing()

add_executable(tests tests/test_figures.cpp)
target_link_libraries(tests PRIVATE ${CMAKE_PROJECT_NAME}_lib GTest::gtest GTest::gtest_main)

target_include_directories(tests PRIVATE include)

add_test(NAME FigureTests COMMAND tests)