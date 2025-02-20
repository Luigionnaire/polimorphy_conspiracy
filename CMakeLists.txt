cmake_minimum_required(VERSION 3.10...3.29)

set(APPLICATION_NAME "PolyPloy")

project(${APPLICATION_NAME} VERSION 0.0.1)

# Application File
# YOU WILL NEED TO ADD YOUR LAYER FILES HERE
#set (PROJECT_HEADER_FILES
#	"application/include/app.hpp"
#	"application/include/GAMR3531.hpp"
#	"application/include/ImGui/bloomPanel.hpp"
#	"application/include/ui.hpp"
#)

set (PROJECT_SOURCE_FILES
	"src/OOP.cpp"
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