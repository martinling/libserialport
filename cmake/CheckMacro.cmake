macro(CHECK_TYPE TYPE INCLUDE_PATH VAR)
	CHECK_C_SOURCE_COMPILES(
		"#include ${INCLUDE_PATH}
		int main(void) { ${TYPE} tmp; return 0; }"
		${VAR})
endmacro()

macro(CHECK_MEMBER TYPE MEMBER INCLUDE_PATH VAR)
	CHECK_C_SOURCE_COMPILES(
		"#include ${INCLUDE_PATH}
		int main(void) { ((${TYPE}*)0)->${MEMBER}; return 0; }"
		${VAR})
endmacro()

macro(CHECK_DECL DEF INCLUDE_PATH VAR)
	CHECK_C_SOURCE_COMPILES(
		"#include ${INCLUDE_PATH}
		int main(void) {
		#ifndef ${DEF}
		#error Symbol undefined
		#endif
		return 0; }"
		${VAR})
endmacro()

macro(TYPE_SIZE_T VAR)
	CHECK_C_SOURCE_COMPILES(
		"#include <sys/types.h>
		int main(void) { size_t test; return 0; }"
		HAVE_SIZE_T)
	if(NOT ${HAVE_SIZE_T})
		set(SIZE_T "unsigned int")
	endif()
endmacro()

macro(HEADER_STDC VAR)
	CHECK_C_SOURCE_COMPILES(
		"#include <stdlib.h>
		#include <stdarg.h>
		#include <string.h>
		#include <float.h>
		int main(void) { return 0; }"
		${VAR})
endmacro()
