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
set(SP_PACKAGE_VERSION_STRING
	"\"${SP_PACKAGE_VERSION_MAJOR}.${SP_PACKAGE_VERSION_MINOR}.${SP_PACKAGE_VERSION_MICRO}\"")

set(SP_LIB_VERSION_CURRENT 1)
set(SP_LIB_VERSION_REVISION 0)
set(SP_LIB_VERSION_AGE 1)
set(SP_LIB_VERSION_STRING
	"\"${SP_LIB_VERSION_CURRENT}:${SP_LIB_VERSION_REVISION}:${SP_LIB_VERSION_AGE}\"")

set(PACKAGE_NAME "\"libserialport\"")
set(PACKAGE_VERSION ${SP_PACKAGE_VERSION_STRING})
set(PACKAGE_BUGREPORT "\"martin-libserialport@earth.li\"")
set(PACKAGE_TARNAME "\"libserialport\"")
set(PACKAGE_URL "\"http://sigrok.org/wiki/Libserialport\"")
set(PACKAGE_STRING "\"libserialport ${SP_PACKAGE_VERSION_MAJOR}.${SP_PACKAGE_VERSION_MINOR}.${SP_PACKAGE_VERSION_MICRO}\"")

# Environment variables
option(BUILD_SHARED_LIBS "Build shared library" OFF)

if(NOT CMAKE_CONFIGURATION_TYPE AND NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

project(${PROJECT_NAME} ${PROJECT_LANGUAGE})

# Export configuration files
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(CheckIncludeFile)
include(CheckCSourceCompiles)
include(CheckFunctionExists)
include(CheckMacro)

CHECK_INCLUDE_FILE("dlfcn.h" HAVE_DLFCN_H)
CHECK_INCLUDE_FILE("inttypes.h" HAVE_INTTYPES_H)
CHECK_INCLUDE_FILE("memory.h" HAVE_MEMORY_H)
CHECK_INCLUDE_FILE("stdint.h" HAVE_STDINT_H)
CHECK_INCLUDE_FILE("stdlib.h" HAVE_STDLIB_H)
CHECK_INCLUDE_FILE("strings.h" HAVE_STRINGS_H)
CHECK_INCLUDE_FILE("string.h" HAVE_STRING_H)
CHECK_INCLUDE_FILE("sys/stat.h" HAVE_SYS_STAT_H)
CHECK_INCLUDE_FILE("sys/types.h" HAVE_SYS_TYPES_H)
CHECK_INCLUDE_FILE("unistd.h" HAVE_UNISTD_H)

CHECK_TYPE("struct termios2" "<linux/termios.h>" HAVE_STRUCT_TERMIOS2)
CHECK_TYPE("struct termiox" "<linux/termios.h>" HAVE_STRUCT_TERMIOX)
CHECK_TYPE("struct serial_struct" "<linux/serial.h>" HAVE_STRUCT_SERIAL_STRUCT)

CHECK_MEMBER("struct termios2" "c_ispeed" "<linux/termios.h>" HAVE_STRUCT_TERMIOS2_C_ISPEED)
CHECK_MEMBER("struct termios2" "c_ospeed" "<linux/termios.h>" HAVE_STRUCT_TERMIOS2_C_OSPEED)
CHECK_MEMBER("struct termios" "c_ispeed" "<linux/termios.h>" HAVE_STRUCT_TERMIOS_C_ISPEED)
CHECK_MEMBER("struct termios" "c_ospeed" "<linux/termios.h>" HAVE_STRUCT_TERMIOS_C_OSPEED)

CHECK_DECL("BOTHER" "<linux/termios.h>" HAVE_DECL_BOTHER)

CHECK_FUNCTION_EXISTS("realpath" HAVE_REALPATH)

TYPE_SIZE_T(SIZE_T)

HEADER_STDC(STDC_HEADERS)

set(SP_SAVED_CFLAGS ${CMAKE_C_FLAGS})
if(MSVC)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -WX")
else()
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror")
endif()
CHECK_C_SOURCE_COMPILES(
	"__attribute__((visibility(\"hidden\"))) void foo(void) {} int main(void) { return 0; }"
	HAVE_ATTRIBUTE)
if(${HAVE_ATTRIBUTE})
	set(SP_CV_VISIBILITY_CONTROL "attribute")
else()
	CHECK_C_SOURCE_COMPILES(
		"__declspec(dllexport) void foo(void) {} int main(void) { return 0; }"
		HAVE_DECLSPEC)
	if(${HAVE_DECLSPEC})
		set(SP_CV_VISIBILITY_CONTROL "declspec")
	else()
		set(SP_CV_VISIBILITY_CONTROL "none")
	endif()
endif()
set(CMAKE_C_FLAGS ${SP_SAVED_CFLAGS})

if(SP_CV_VISIBILITY_CONTROL MATCHES "attribute")
	set(SP_API "__attribute__((visibility(\"default\")))")
	set(SP_PRIV "__attribute__((visibility(\"hidden\")))")
elseif(SP_CV_VISIBILITY_CONTROL MATCHES "declspec")
	set(SP_API "__declspec(dllexport)")
	set(SP_PRIV " ")
else()
	set(SP_API " ")
	set(SP_PRIV " ")
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.cmake
	${CMAKE_CURRENT_BINARY_DIR}/config.h)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/libserialport.h.cmake
	${CMAKE_CURRENT_BINARY_DIR}/libserialport.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Compile library
set(SP_SRCS
	"${CMAKE_CURRENT_SOURCE_DIR}/serialport.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/libserialport_internal.h")

set(SP_HEADERS "${CMAKE_CURRENT_BINARY_DIR}/libserialport.h")

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	set(SP_SRCS ${SP_SRCS}
		"${CMAKE_CURRENT_SOURCE_DIR}/linux.c"
		"${CMAKE_CURRENT_SOURCE_DIR}/linux_termios.c"
		"${CMAKE_CURRENT_SOURCE_DIR}/linux_termios.h")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	set(SP_SRCS ${SP_SRCS}
		"${CMAKE_CURRENT_SOURCE_DIR}/windows.c")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set(SP_SRCS ${SP_SRCS}
		"${CMAKE_CURRENT_SOURCE_DIR}/macosx.c")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
	set(SP_SRCS ${SP_SRCS}
		"${CMAKE_CURRENT_SOURCE_DIR}/freebsd.c")
else()
	message(FATAL_ERROR "Unexpected host operating system")
endif()

add_library(${PROJECT_NAME} ${SP_SRCS})
set_target_properties(${PROJECT_NAME} PROPERTIES
	OUTPUT_NAME ${PROJECT_NAME}
	PREFIX "lib")

if(${BUILD_SHARED_LIBS})
	if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
		target_link_libraries(${PROJECT_NAME} setupapi)
	endif()
endif()

install(TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin"
	ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib"
	LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")

install(FILES ${SP_HEADERS}
	DESTINATION "${CMAKE_INSTALL_PREFIX}/include")
