# Macro to print some message to stdout, useful for debugging purpose.
MACRO(DBG_MSG _MSG)
FOREACH(_MSG_STRING ${_MSG})
  MESSAGE(STATUS "${CMAKE_CURRENT_LIST_FILE}(${CMAKE_CURRENT_LIST_LINE}): ${_MSG_STRING}")
ENDFOREACH()
ENDMACRO(DBG_MSG)

# The name of our project is "test". CMakeLists files in this project can
# refer to the root source directory of the project as ${test_SOURCE_DIR} and
# to the root binary directory of the project as ${test_BINARY_DIR}.
cmake_minimum_required (VERSION 2.6)
project (test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
#set(LINK_FLAGS "-g")
#set(CMAKE_CXX_FLAGS "-g")
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE Release)

find_package(OpenGL REQUIRED)
if (WIN32)
	# Can't seem to use find_package for GLFW or OpenAL on my Windows 7 box...
	set(OPENAL_INCLUDE_DIR "D:/msysgit/msysgit/local/include")
	set(OPENAL_LIBRARY "D:/msysgit/msysgit/local/lib/OpenAL32.lib")
	set(GLFW_INCLUDE_DIR "D:/msysgit/msysgit/local/include")
	set(GLFW_LIBRARY "D:/msysgit/msysgit/local/lib/libglfw.a")
endif (WIN32)
if (UNIX)
	find_package(GLFW REQUIRED)
	find_package(OpenAL REQUIRED)
endif (UNIX)

include_directories(${GLFW_INCLUDE_DIR} ${OPENAL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})
set(LIBS ${LIBS} ${GLFW_LIBRARY} ${OPENAL_LIBRARY} ${OPENGL_LIBRARY})

# Platform differences
include_directories ("${test_SOURCE_DIR}/engine/independent")
if (WIN32)
	include_directories ("${test_SOURCE_DIR}/engine/windows")
endif (WIN32)
if (UNIX)
	include_directories ("${test_SOURCE_DIR}/engine/linux")
endif (UNIX)

#get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
#DBG_MSG("INCLUDE_DIRECTORIES = [${dirs}]")
#DBG_MSG("LIBS = [${LIBS}]")
set(PLATFORM_INDEPENDENT_SOURCES
 	engine/independent/common/stdafx.cpp
 	engine/independent/input/keyboard.cpp
	engine/independent/graphics/display.cpp
	engine/independent/kernel/time/realtimeclock.cpp
	engine/independent/kernel/time/timer.cpp
	engine/independent/kernel/time/timesource.cpp
	)
if (WIN32)
set(PLATFORM_SPECIFIC_SOURCES
	engine/windows/kernel/time/platform_systemclock.cpp
	)
endif (WIN32)
if (UNIX)
set(PLATFORM_SPECIFIC_SOURCES
	engine/linux/kernel/time/platform_systemclock.cpp
	)
endif (UNIX)

add_executable (test main.cpp ${PLATFORM_INDEPENDENT_SOURCES} ${PLATFORM_SPECIFIC_SOURCES} )
target_link_libraries (test ${LIBS})

