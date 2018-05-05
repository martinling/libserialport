# This will define the following variables:
#
#   Serialport_FOUND        - True if the system has the libserialport library
#   SERIALPORT_INCLUDE_DIRS - location of header files
#   SERIALPORT_LIBRARIES    - location of library files

find_path(SERIALPORT_INCLUDE_DIRS libserialport.h
	"/usr/include"
	"/usr/local/include")

find_library(SERIALPORT_LIBRARIES serialport
	"/usr/lib"
	"/usr/local/lib")

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(Serialport
	FOUND_VAR Serialport_FOUND
	REQUIRED_VARS SERIALPORT_INCLUDE_DIRS SERIALPORT_LIBRARIES)
