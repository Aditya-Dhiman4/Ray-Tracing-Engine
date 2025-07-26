cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(ray-tracing-engine VERSION 0.1.0 LANGUAGES C CXX)

add_compile_options(-O3 -march=native)

add_executable(ray-tracing-engine main.cpp)

