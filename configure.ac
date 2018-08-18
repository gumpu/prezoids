#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Prezoids],[1.0],[rfsber@xs4all.nl])
AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_HEADERS([config.h])
# Tread warnings as errors: -Werror
# This fails on % rules in makefiles, and we
# want those.
AM_INIT_AUTOMAKE([-Wall foreign])
AC_CONFIG_FILES([
    Makefile
    src/Makefile
    Images/Makefile
    ])

# Checks for programs.
AC_PROG_CXX

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL

# Checks for library functions.
AC_CHECK_FUNCS([clock_gettime])

AC_OUTPUT

