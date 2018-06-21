cmake_minimum_required(VERSION 2.6)
project(alligator)

if(WIN32)
	list(APPEND CMAKE_EXE_LINKER_FLAGS "-static-libstdc++ -static-libgcc")
endif()

set(LIBRARY_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/bin)

if(NOT MSVC)
    find_package(Allegro REQUIRED)
    if(NOT ALLEGRO_FOUND)
        message(FATAL_ERROR "NO ALLEGRO DETECTED!")
    else()
        message("ALLEGRO INCLUDE: ${ALLEGRO_INCLUDE_DIR}")
    endif(NOT ALLEGRO_FOUND)
endif()

file(GLOB_RECURSE SRCS *.cpp)
file(GLOB_RECURSE HDRS *.h)

set(ALLIGATOR_SOURCES
    ${SRCS} ${HDRS})

add_library(alligator ${ALLIGATOR_SOURCES})

if(NOT MSVC)
    target_include_directories(alligator PUBLIC "${ALLEGRO_INCLUDE_DIR}")
    target_include_directories(alligator PUBLIC src)
        set_target_properties(alligator PROPERTIES
                COMPILE_FLAGS "-std=gnu++11  -Wall -Wextra"
                LINK_FLAGS "-g -ftest-coverage -fprofile-arcs"
                )
        target_link_libraries(alligator ${ALLEGRO_LIBRARIES})
endif()
