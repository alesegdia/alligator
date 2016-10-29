cmake_minimum_required(VERSION 2.6)
project(alligator)

if(WIN32)
	list(APPEND CMAKE_EXE_LINKER_FLAGS "-static-libstdc++ -static-libgcc")
endif()

set(LIBRARY_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/bin)

set(ALLIGATOR_SOURCES
	src/alligator/audio/audiosample.cpp
	src/alligator/audio/audiosample.h
	src/alligator/audio/audiostream.cpp
	src/alligator/audio/audiostream.h

	src/alligator/camera/camera.cpp
	src/alligator/camera/camera.h

	src/alligator/game/game.cpp
	src/alligator/game/game.h
	src/alligator/game/iscreen.cpp
	src/alligator/game/iscreen.h

	src/alligator/graphics/animation.cpp
	src/alligator/graphics/animation.h
	src/alligator/graphics/spritesheet.cpp
	src/alligator/graphics/spritesheet.h

	src/alligator/input/iinputprocessor.cpp
	src/alligator/input/iinputprocessor.h
	src/alligator/input/input.cpp
	src/alligator/input/input.h

	src/alligator/util/math.cpp
	src/alligator/util/math.h
	src/alligator/util/matrix.h
	src/alligator/util/rng.cpp
	src/alligator/util/rng.h
	)

add_library(alligator ${ALLIGATOR_SOURCES})

set_target_properties(alligator PROPERTIES
	COMPILE_FLAGS "-std=c++11"
	LINK_FLAGS "-g -ftest-coverage -fprofile-arcs"
	INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/src
	)


