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
