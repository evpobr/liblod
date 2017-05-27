cmake_minimum_required(VERSION 3.1)

project(liblod VERSION 0.1 LANGUAGES C CXX)

include(GenerateExportHeader)

set(lod_PUBLIC_HEADERS
	include/lod/lod.h)
set(lod_SOURCES
	src/lod.c
	src/lod_private.h
	src/std_io.c
	src/std_io.h)
add_library(lod ${lod_PUBLIC_HEADERS} ${lod_SOURCES})
target_include_directories(lod PUBLIC include ${CMAKE_CURRENT_BINARY_DIR})
set_target_properties(lod PROPERTIES
	PUBLIC_HEADER "${lod_PUBLIC_HEADERS}")
if(BUILD_SHARED_LIBS)
	set_target_properties(lod PROPERTIES
		DEFINE_SYMBOL LOD_EXPORTS
		VERSION ${PROJECT_VERSION}
		SOVERSION ${PROJECT_VERSION_MAJOR}
		C_VISIBILITY_PRESET hidden
		VISIBILITY_INLINES_HIDDEN 1)
else()
	target_compile_definitions(lod PUBLIC -DLOD_STATIC_DEFINE)
endif()
if(MSVC)
	target_compile_definitions(lod PRIVATE -DUSE_MSVC_SAFE_CRT)
endif()

generate_export_header(lod)
target_sources(lod PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/lod_export.h)
