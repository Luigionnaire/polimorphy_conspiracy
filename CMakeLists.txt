cmake_minimum_required(VERSION 3.10...3.29)

set(APPLICATION_NAME "PolyPloy")

project(${APPLICATION_NAME} VERSION 0.0.1)

set (PROJECT_HEADER_FILES
	"include/timer.h"
	"include/switch.h"
	"include/shape_base.h"
	"include/square.h"
	"include/rectangle.h"
	"include/triangle.h"
	"include/circle.h"
)

set (PROJECT_SOURCE_FILES
	"src/OOP.cpp"
	"src/timer.cpp"
)

# Add executable target and include directory
add_executable(${APPLICATION_NAME} ${PROJECT_SOURCE_FILES} ${PROJECT_HEADER_FILES})
target_include_directories(${APPLICATION_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Set start up project in VS
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${APPLICATION_NAME})
set_target_properties(${APPLICATION_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# Visual Studio filters
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}../src" PREFIX "src" FILES ${PROJECT_SOURCE_FILES})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}../include" PREFIX "include" FILES ${PROJECT_HEADER_FILES})

# Use C++20
set_target_properties(${APPLICATION_NAME} PROPERTIES CXX_STANDARD 20)

#Enable AVX2
SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /arch:AVX2")