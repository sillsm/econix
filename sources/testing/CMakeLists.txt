## CMakeLists.txt
include_directories(..)

option(Econix_build_cpp_tests "Build all of foo's c++ unit tests." ON)
project(EconixCPlusPlusTesting)
cmake_minimum_required(VERSION 2.8)
include_directories("/usr/local/include")
link_directories("/usr/local/lib")
set(cpp_testing_SOURCES
    main.cpp
	SimpleResourceTransactionTest.h
	SimpleResourceTransactionTest.cpp
	TestBase.h
	)
	
########################### GTEST

SET(CMAKE_CXX_FLAGS_DEBUG "/MTd")


# Specify MainTest's link libraries


#END add gtest

if (Econix_build_cpp_tests)
    Message(${CMAKE_SOURCE_DIR}/Libraries/bin/src/googletest/include/gtest/)
	#export CMAKE_INCLUDE_PATH="$CMAKE_SOURCE_DIR/Libraries/bin/src/googletest/include:$CMAKE_INCLUDE_PATH"
	#export CMAKE_INCLUDE_PATH="/stuff/lib.boost.1.52/include:$CMAKE_INCLUDE_PATH"
	
    enable_testing()
	
	find_package(GTest QUIET)
	if (NOT Gtest_FOUND)
	  message("could not find it")
      set(GTEST_INCLUDE "default value" CACHE FILEPATH "description")
	  set(GTEST_LIBRARY_BIG "default value" CACHE FILEPATH "description")
	  
	  set (GTEST_INCLUDE_DIR ${GTEST_INCLUDE})
	  set(GTEST_LIBRARY ${GTEST_LIBRARY_BIG} )
	  message(${GTEST_INCLUDE_DIR})
	endif()	
	
	include_directories(${GTEST_INCLUDE_DIRS})
    add_executable(CppTesting ${cpp_testing_SOURCES} )
    add_dependencies(CppTesting GTest)    
	
	target_link_libraries(CppTesting utility ${GTEST_LIBRARIES} pthread)


endif()
