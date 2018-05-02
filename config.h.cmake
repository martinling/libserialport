/* config.h.in.  Generated from configure.ac by autoheader.  */
/* config.h.cmake. Modify from config.h.in. */

/* Define to 1 if you have the declaration of `BOTHER', and to 0 if you don't.
   */
#cmakedefine HAVE_DECL_BOTHER @HAVE_DECL_BOTHER@

/* Define to 1 if you have the <dlfcn.h> header file. */
#cmakedefine HAVE_DLFCN_H @HAVE_DLFCN_H@

/* Define to 1 if you have the <inttypes.h> header file. */
#cmakedefine HAVE_INTTYPES_H @HAVE_INTTYPES_H@

/* Define to 1 if you have the <memory.h> header file. */
#cmakedefine HAVE_MEMORY_H @HAVE_MEMORY_H@

/* realpath is available. */
#undef HAVE_REALPATH

/* Define to 1 if you have the <stdint.h> header file. */
#cmakedefine HAVE_STDINT_H @HAVE_STDINT_H@

/* Define to 1 if you have the <stdlib.h> header file. */
#cmakedefine HAVE_STDLIB_H @HAVE_STDLIB_H@

/* Define to 1 if you have the <strings.h> header file. */
#cmakedefine HAVE_STRINGS_H @HAVE_STRINGS_H@

/* Define to 1 if you have the <string.h> header file. */
#cmakedefine HAVE_STRING_H @HAVE_STRING_H@

/* Define to 1 if the system has the type `struct serial_struct'. */
#cmakedefine HAVE_STRUCT_SERIAL_STRUCT @HAVE_STRUCT_SERIAL_STRUCT@

/* Define to 1 if the system has the type `struct termios2'. */
#cmakedefine HAVE_STRUCT_TERMIOS2 @HAVE_STRUCT_TERMIOS2@

/* Define to 1 if `c_ispeed' is a member of `struct termios2'. */
#cmakedefine HAVE_STRUCT_TERMIOS2_C_ISPEED @HAVE_STRUCT_TERMIOS2_C_ISPEED@

/* Define to 1 if `c_ospeed' is a member of `struct termios2'. */
#cmakedefine HAVE_STRUCT_TERMIOS2_C_OSPEED @HAVE_STRUCT_TERMIOS2_C_OSPEED@

/* Define to 1 if `c_ispeed' is a member of `struct termios'. */
#cmakedefine HAVE_STRUCT_TERMIOS_C_ISPEED @HAVE_STRUCT_TERMIOS_C_ISPEED@

/* Define to 1 if `c_ospeed' is a member of `struct termios'. */
#cmakedefine HAVE_STRUCT_TERMIOS_C_OSPEED @HAVE_STRUCT_TERMIOS_C_OSPEED@

/* Define to 1 if the system has the type `struct termiox'. */
#cmakedefine HAVE_STRUCT_TERMIOX @HAVE_STRUCT_TERMIOX@

/* Define to 1 if you have the <sys/stat.h> header file. */
#cmakedefine HAVE_SYS_STAT_H @HAVE_SYS_STAT_H@

/* Define to 1 if you have the <sys/types.h> header file. */
#cmakedefine HAVE_SYS_TYPES_H @HAVE_SYS_TYPES_H@

/* Define to 1 if you have the <unistd.h> header file. */
#cmakedefine HAVE_UNISTD_H @HAVE_UNISTD_H@

/* Define to the sub-directory where libtool stores uninstalled libraries. */
#undef LT_OBJDIR

/* Enumeration is unsupported. */
#undef NO_ENUMERATION

/* Port metadata is unavailable. */
#undef NO_PORT_METADATA

/* Define to the address where bug reports for this package should be sent. */
#undef PACKAGE_BUGREPORT

/* Define to the full name of this package. */
#undef PACKAGE_NAME

/* Define to the full name and version of this package. */
#undef PACKAGE_STRING

/* Define to the one symbol short name of this package. */
#undef PACKAGE_TARNAME

/* Define to the home page for this package. */
#undef PACKAGE_URL

/* Define to the version of this package. */
#undef PACKAGE_VERSION

/* Macro preceding public API functions */
#undef SP_API

/* . */
#define SP_LIB_VERSION_AGE @SP_LIB_VERSION_AGE@

/* . */
#define SP_LIB_VERSION_CURRENT @SP_LIB_VERSION_CURRENT@

/* . */
#define SP_LIB_VERSION_REVISION @SP_LIB_VERSION_REVISION@

/* . */
#define SP_LIB_VERSION_STRING @SP_LIB_VERSION_STRING@

/* . */
#define SP_PACKAGE_VERSION_MAJOR @SP_PACKAGE_VERSION_MAJOR@

/* . */
#define SP_PACKAGE_VERSION_MICRO @SP_PACKAGE_VERSION_MICRO@

/* . */
#define SP_PACKAGE_VERSION_MINOR @SP_PACKAGE_VERSION_MINOR@

/* . */
#define SP_PACKAGE_VERSION_STRING @SP_PACKAGE_VERSION_STRING@

/* Macro preceding private functions */
#undef SP_PRIV

/* Define to 1 if you have the ANSI C header files. */
#cmakedefine STDC_HEADERS @STDC_HEADERS@

/* Enable large inode numbers on Mac OS X 10.5.  */
#ifndef _DARWIN_USE_64_BIT_INODE
# define _DARWIN_USE_64_BIT_INODE 1
#endif

/* Number of bits in a file offset, on hosts where this is settable. */
#undef _FILE_OFFSET_BITS

/* Define for large files, on AIX-style hosts. */
#undef _LARGE_FILES

/* Define to `unsigned int' if <sys/types.h> does not define. */
#undef size_t

#if HAVE_STRUCT_TERMIOS_C_ISPEED && HAVE_STRUCT_TERMIOS_C_OSPEED
# define HAVE_TERMIOS_SPEED 1
#endif
#if HAVE_STRUCT_TERMIOS2_C_ISPEED && HAVE_STRUCT_TERMIOS2_C_OSPEED
# define HAVE_TERMIOS2_SPEED 1
#endif
