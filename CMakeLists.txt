cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project("Fun Questions")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

enable_testing()
include(gmock)

set(warnings "-Wall -Wextra -Werror")
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

if (NOT CONFIGURED_ONCE)
    set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} ${warnings}"
        CACHE STRING "FLags used by the compiler during all build types." FORCE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${warnings}"
        CACHE STRING "FLags used by the compiler during all build types." FORCE)
endif()


file(GLOB question_dirs *question*)
foreach(question_dir IN LISTS question_dirs)
    add_subdirectory(${question_dir})
endforeach()

set(CONFIRGURED_ONCE TRUE CACHE INTERNAL
    "A flag showing that CMake has configured at least once.")
