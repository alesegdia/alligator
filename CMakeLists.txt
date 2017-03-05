cmake_minimum_required(VERSION 2.6)
project(alligator)

if(WIN32)
	list(APPEND CMAKE_EXE_LINKER_FLAGS "-static-libstdc++ -static-libgcc")
endif()

set(LIBRARY_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/bin)


file(GLOB_RECURSE SRCS *.cpp)
file(GLOB_RECURSE HDRS *.h)

set(ALLIGATOR_SOURCES
    ${SRCS} ${HDRS})

add_library(alligator ${ALLIGATOR_SOURCES})

set_target_properties(alligator PROPERTIES
	COMPILE_FLAGS "-std=c++11"
	LINK_FLAGS "-g -ftest-coverage -fprofile-arcs"
	INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/src
	)


