cmake_minimum_required(VERSION 3.1)

project(liblod VERSION 0.1 LANGUAGES C)

set(lod_PUBLIC_HEADERS
	include/lod/lod.h
	include/lod/lod_export.h)
set(lod_SOURCES
	src/lod.c
	src/lod_private.h)
add_library(lod ${lod_PUBLIC_HEADERS} ${lod_SOURCES})
target_include_directories(lod PUBLIC include)
set_target_properties(lod PROPERTIES
	DEFINE_SYMBOL LOD_EXPORTS
	PUBLIC_HEADER "${lod_PUBLIC_HEADERS}"
	SOVERSION ${PROJECT_VERSION_MAJOR}
	VERSION ${PROJECT_VERSION}
	C_VISIBILITY_PRESET hidden)
if (BUILD_SHARED_LIBS)
	target_compile_definitions(lod
		INTERFACE LOD_IMPORTS)
endif()