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

# Get and define libraries globally for all projects
# Boost 1.55.0
FIND_PACKAGE(Boost 1.55.0 REQUIRED COMPONENTS system thread regex)
IF(Boost_FOUND)
  INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
  LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
ENDIF(Boost_FOUND)

#Gtest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE})

#Openssl
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE})  
#add_library(utility ${OPENSSL_INCLUDE})
#add_library(utility ${UTILITY_SRCS})	  
	  
# Add subdirs

# other stuff

file(GLOB UTILITY_SRCS
    "sources/utility/*.h"
    "sources/utility/*.cpp"
)
add_library(utility ${UTILITY_SRCS})
target_link_libraries(utility ${Boost_LIBRARY_DIRS} )

include_directories(${UTILITY_SRCS})

file(GLOB cpp_testing_SOURCES
    "sources/testing/*.h"
    "sources/testing/*.cpp"
)
add_executable(CppTesting ${cpp_testing_SOURCES} )
add_dependencies(CppTesting GTest utility)    
target_link_libraries(CppTesting utility ${GTEST_LIBRARIES} ${OPENSSL_LIBRARIES} pthread )


#add_subdirectory( "sources/executable" )
#add_subdirectory( "sources/utility" )
#add_subdirectory( "sources/testing" )

