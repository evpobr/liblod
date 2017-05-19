cmake_minimum_required(VERSION 3.1)

project(liblod VERSION 0.1 LANGUAGES C CXX)

include(GenerateExportHeader)

set(lod_PUBLIC_HEADERS
	include/lod/lod.h)
set(lod_SOURCES
	src/lod.c
	src/lod_private.h)
add_library(lod ${lod_PUBLIC_HEADERS} ${lod_SOURCES})
target_include_directories(lod PUBLIC include ${CMAKE_CURRENT_BINARY_DIR})
set_target_properties(lod PROPERTIES
	DEFINE_SYMBOL LOD_EXPORTS
	PUBLIC_HEADER "${lod_PUBLIC_HEADERS}"
	SOVERSION ${PROJECT_VERSION_MAJOR}
	VERSION ${PROJECT_VERSION}
	C_VISIBILITY_PRESET hidden)
if(NOT BUILD_SHARED_LIBS)
	target_compile_definitions(lod PUBLIC -DLOD_STATIC_DEFINE)
endif()

generate_export_header(lod)
target_sources(lod PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/lod_export.h)
