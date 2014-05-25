cmake_minimum_required(VERSION 2.8)
add_definitions(-std=c++11)

project(Econix)

IF(MSVC)
ADD_DEFINITIONS(/D _CRT_SECURE_NO_WARNINGS)
ELSE(MSVC)
SET( CMAKE_CXX_FLAGS  "-O2 -Wno-unused-result" )
SET( CMAKE_CXX_FLAGS_DEBUG  "-O2 -Wno-unused-result" )
SET( CMAKE_CXX_FLAGS_RELEASE  "-O2 -Wno-unused-result" )
ENDIF(MSVC)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/helper/")
set( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR} )



add_subdirectory( "sources/executable" )
add_subdirectory( "sources/utility" )
add_subdirectory( "sources/testing" )


