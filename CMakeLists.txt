cmake_minimum_required(VERSION 2.6)
project(alligator)

list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -g -ftest-coverage -fprofile-arcs")

file(GLOB_RECURSE CPPs src/**/*.cpp)
file(GLOB_RECURSE HPPs src/**/*.h)

set(LIBRARY_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/bin)
add_library(alligator ${CPPs} ${HPPs})

include_directories(src/)

if(WIN32)
	list(APPEND CMAKE_EXE_LINKER_FLAGS "-static-libstdc++ -static-libgcc")
endif()

install(DIRECTORY src/ DESTINATION include/alligator FILES_MATCHING PATTERN "*.h")
install(TARGETS alligator
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)
