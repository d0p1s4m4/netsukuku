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

if(MSVC)
	find_package(PThreads4W CONFIG REQUIRED)
	find_package(unofficial-getopt-win32 CONFIG REQUIRED)
	add_compile_definitions(-DHAVE_GETOPT_H)
endif()
CHECK_INCLUDE_FILE(getopt.h HAVE_GETOPT_H)

add_subdirectory(lib)
add_subdirectory(libQSPN)
add_subdirectory(ntkd)
add_subdirectory(ntk-cli)


set(CPACK_PACKAGE_NAME "${CMAKE_PROJECT_NAME}")
set(CPACK_PACKAGE_VENDOR "d0p1.eu")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY
	"Netsukuku aims to be a mesh network or a peer to peer protocol that generates and sustains itself autonomously.")
set(CPACK_RESOURCE_FILE_LICENSE
	"${CMAKE_CURRENT_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "${CMAKE_PROJECT_NAME}")

include(CPack)