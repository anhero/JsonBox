cmake_minimum_required(VERSION 2.6)

project(JsonBox)
set(LIBRARY_OUTPUT_PATH lib/${CMAKE_BUILD_TYPE})

include_directories(include)

file(
	GLOB_RECURSE
	source_files
	src/*
	include/*
)

add_library(
	JsonBox
	STATIC
	${source_files}
)

add_executable(
	test1
	examples/main.cpp
	${source_files}
)