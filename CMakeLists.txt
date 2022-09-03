cmake_minimum_required(VERSION 3.0.0)
project("ooc" VERSION 0.1.0)

set(CMAKE_C_STANDARD 11)

include(CTest)
enable_testing()

add_compile_options(-Wall -Wextra -g)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
include_directories(./inc)

aux_source_directory(./src SRC_LIST)

add_executable(ooc test.c ${SRC_LIST})