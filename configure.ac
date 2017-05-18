#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([lod], [0.1.0], [evpobr@gmail.com])
AC_CONFIG_SRCDIR([src/lod.c])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])
AM_SILENT_RULES([yes])
AM_INIT_AUTOMAKE([1.15 -Wall -Werror foreign subdir-objects])
AM_MAINTAINER_MODE([enable])

AM_PROG_AR
AC_PROG_CC
AC_PROG_CC_C99
AC_PROG_CXX


LT_PREREQ([2.4.6])
LT_INIT([win32-dll])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.

gl_VISIBILITY

# Checks for library functions.
AC_FUNC_MALLOC

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT

