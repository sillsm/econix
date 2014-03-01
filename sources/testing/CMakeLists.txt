## CMakeLists.txt
include_directories(..)
option(Econix_build_cpp_tests "Build all of Econix's c++ unit tests." ON)
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

if (Econix_build_cpp_tests)
    option(CUSTOM_LIB_GTEST "Use custom-built gtest library." OFF)
    Message(${CMAKE_SOURCE_DIR}/Libraries/bin/src/googletest/include/gtest/)
	
    enable_testing()	
	find_package(GTest QUIET)
	if (CUSTOM_LIB_GTEST)
	  # E.g. for Win 7 x86: point to pre-built static libs
	  message("could not find it")
      set(GTEST_INCLUDE "Point me to GTEST include" CACHE FILEPATH "description")
	  set(GTEST_LIBRARY_BIG "Point me to GTEST libraries" CACHE FILEPATH "description")
	  
	  find_package(GTest QUIET)
	  include_directories(${GTEST_INCLUDE})
      add_executable(CppTesting ${cpp_testing_SOURCES} )
      #add_dependencies(CppTesting GTest)    
	  target_link_libraries(CppTesting utility ${GTEST_LIBRARY_BIG} ${PThread} )
	  message(${GTEST_INCLUDE_DIR})
	else()	
	  # E.g. for Ubuntu and Debian: use package manager to get libgtest-dev, build it, then use
	  # standard cmake
	  find_package(GTest REQUIRED)
	  include_directories(${GTEST_INCLUDE})
      add_executable(CppTesting ${cpp_testing_SOURCES} )
      add_dependencies(CppTesting GTest)    
	  target_link_libraries(CppTesting utility ${GTEST_LIBRARIES} pthread )
    endif()	
endif()
