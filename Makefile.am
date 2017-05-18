ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}

pkginclude_HEADERS = \
	include/lod/lod.h \
	include/lod/lod_export.h

lib_LTLIBRARIES = src/liblod.la

src_liblod_la_SOURCES = \
	src/lod.c \
	src/lod_private.h

src_liblod_la_CFLAGS = $(CFLAG_VISIBILITY)
src_liblod_la_CPPFLAGS = -DLOD_EXPORTS \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/src
src_liblod_la_LDFLAGS = -no-undefined

EXTRA_DIST = CMakeLists.txt .editorconfig \
	.gitignore .gitattributes README.md \
	m4/visibility.m4

