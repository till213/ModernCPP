cmake_minimum_required(VERSION 3.5)

set(MODERN_CPP_DESC "Modern C++ by example code")
project(ModernCPP LANGUAGES CXX VERSION 0.1.0 DESCRIPTION ${MODERN_CPP_DESC})
set(PROJECT_APPLICATION_NAME "Modern C++")
set(PROJECT_ORGANISATION_NAME till213)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Platform identifiers

# https://gitlab.kitware.com/cmake/community/-/wikis/doc/tutorials/How-To-Write-Platform-Checks
string(COMPARE EQUAL "Windows" ${CMAKE_SYSTEM_NAME} PLATFORM_IS_WINDOWS)
string(COMPARE EQUAL "Darwin" ${CMAKE_SYSTEM_NAME} PLATFORM_IS_MACOS)
string(COMPARE EQUAL "Linux" ${CMAKE_SYSTEM_NAME} PLATFORM_IS_LINUX)
message(STATUS PLATFORM="${CMAKE_SYSTEM_NAME}")

# Definitions

# Debug output
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_definitions(-DDEBUG)
endif()

# Example code
add_subdirectory(${CMAKE_SOURCE_DIR}/src/language)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/templates)

# Documentation
add_subdirectory(${CMAKE_SOURCE_DIR}/doc)
