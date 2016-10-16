set (PROJECT_NAME "ppp-project")

set (CMAKE_C_FLAGS "-Werror -Wall -g -Wstrict-prototypes")

project (${PROJECT_NAME})
cmake_minimum_required (VERSION 2.8)

set (INCLUDE_DIR ./include/)
include_directories (${INCLUDE_DIR})

file (GLOB_RECURSE PROJECT_INCLUDES "include/*.h")
file (GLOB_RECURSE PROJECT_SOURCES "src/*.c")

include_directories (PROJECT_INCLUDES)
add_executable (${PROJECT_NAME} ${PROJECT_SOURCES})
