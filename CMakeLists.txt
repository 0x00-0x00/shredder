cmake_minimum_required(VERSION 3.5)
project(shredder)

set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu99 -Wall -lpthread -D_FILE_OFFSET_BITS=64")

set(SOURCE_FILES main.c)
add_executable(shredder ${SOURCE_FILES})