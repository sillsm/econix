cmake_minimum_required(VERSION 2.8)
project(EconixExec)

#add_definitions( -Wall )


SET(CMAKE_CXX_FLAGS_DEBUG "/MTd")

set(UTILITY_SRCS
    picojson.h
    transactionblob.h
    transactionblob.cpp
   )
   
 include_directories( "." 
 ${UTILITY_SRCS}
 ${OPENSSL_INCLUDE}
           )

add_library(utility ${UTILITY_SRCS})

option(CUSTOM_LIB_OPENSSL "Use custom-built OPENSSL library." OFF)

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
	  target_link_libraries(utility ${OPENSSL_LIBRARY_A} ${OPENSSL_LIBRARY_B} )
	else()	
	  # E.g. for Ubuntu and Debian: use package manager to get libgtest-dev, build it, then use
	  # standard cmake
	  find_package(OpenSSL REQUIRED)
	  include_directories(${OPENSSL_INCLUDE})  
	  #add_library(utility ${OPENSSL_INCLUDE})
      #add_library(utility ${UTILITY_SRCS})	  
	  target_link_libraries(utility ${OPENSSL_LIBRARIES})
    endif()	