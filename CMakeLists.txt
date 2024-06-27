cmake_minimum_required(VERSION 3.10)
project(netsukuku VERSION 0.1.0 LANGUAGES C)

add_compile_definitions(-DPACKAGE_NAME="${CMAKE_PROJECT_NAME}")
add_compile_definitions(-DPACKAGE_VERSION="${CMAKE_PROJECT_VERSION}")

include(CheckIncludeFile)
set(CMAKE_REQUIRED_DEFINITIONS ON)

if(UNIT_TESTING)
	find_package(cmocka 1.1.0 REQUIRED)
	include(CTest)
endif()

add_subdirectory(lib)
add_subdirectory(libQSPN)
add_subdirectory(ntkd)