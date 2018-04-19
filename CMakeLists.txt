cmake_minimum_required(VERSION 2.8)

# Disable in-source builds to prevent source tree corruption.
if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
	message(FATAL_ERROR "FATAL: In-source builds are not allowed.
       You should create a separate directory for build files.")
endif()

# Set variables
set(PROJECT_NAME serialport)
set(PROJECT_LANGUAGE C)

set(SP_PACKAGE_VERSION_MAJOR 0)
set(SP_PACKAGE_VERSION_MINOR 1)
set(SP_PACKAGE_VERSION_MICRO 1)
set(SP_PACKAGE_VERSION
	"${SP_PACKAGE_VERSION_MAJOR}.${SP_PACKAGE_VERSION_MINOR}.${SP_PACKAGE_VERSION_MICRO}")

set(SP_LIB_VERSION_CURRENT 1)
set(SP_LIB_VERSION_REVISION 0)
set(SP_LIB_VERSION_AGE 1)
set(SP_LIB_VERSION
	"${SP_LIB_VERSION_CURRENT}:${SP_LIB_VERSION_REVISION}:${SP_LIB_VERSION_AGE}")

# Environment variables
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "Installation directory")
set(BUILD_TEST OFF CACHE BOOL "Enable building test")

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Build configure" FORCE)
if(DEFINED CMAKE_BUILD_TYPE)
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${CMAKE_CONFIGURATION_TYPES})
endif()
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

project(${PROJECT_NAME} ${PROJECT_LANGUAGE})
