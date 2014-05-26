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

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

Message(inner CMAKE)
Message(${Boost_INCLUDE_DIRS})
Message(${Boost_LIBRARY_DIRS})
Message(inner CMAKE)

if (Econix_build_cpp_tests)
  find_package(GTest REQUIRED)
  include_directories(${GTEST_INCLUDE})
  add_executable(CppTesting ${cpp_testing_SOURCES} )
  add_dependencies(CppTesting GTest utility)    
  target_link_libraries(CppTesting utility ${GTEST_LIBRARIES} pthread )
endif()	
	
    if (CUSTOM_LIB_OPENSSL)
	  # E.g. for Win 7 x86: point to pre-built static libs
      set(OPENSSL_INCLUDE "Point me to OPENSSL include" CACHE FILEPATH "description")
	  set(OPENSSL_LIBRARY_A "Point me to OPENSSL library A" CACHE FILEPATH "description")
	  set(OPENSSL_LIBRARY_B "Point me to OPENSSL library B" CACHE FILEPATH "description")
	  
	  find_package(OpenSSL QUIET)
	  include_directories(${OPENSSL_INCLUDE})
	  #add_library(utility ${OPENSSL_INCLUDE} ${UTILITY_SRCS})
	  message(${OPENSSL_INCLUDE})
      #add_dependencies(CppTesting GTest)    
	  #add_library(utility ${UTILITY_SRCS})
	  target_link_libraries(CppTesting ${OPENSSL_LIBRARY_A} ${OPENSSL_LIBRARY_B} )
	else()	
	  # E.g. for Ubuntu and Debian: use package manager to get libgtest-dev, build it, then use
	  # standard cmake
	  find_package(OpenSSL REQUIRED)
	  include_directories(${OPENSSL_INCLUDE})  
	  #add_library(utility ${OPENSSL_INCLUDE})
      #add_library(utility ${UTILITY_SRCS})	  
	  target_link_libraries(CppTesting ${OPENSSL_LIBRARIES})
    endif()	
	
	
	
endif()
# # something
target_link_libraries(CppTesting ${Boost_LIBRARY_DIRS} )
