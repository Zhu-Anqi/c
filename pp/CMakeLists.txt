cmake_minimum_required(VERSION 3.10)
project(textIDE)
add_executable(textIDE main.c raw_mode.c )
include_directories(${CMAKE_CURRENT_SOURCE_DIR})