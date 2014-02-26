cmake_minimum_required(VERSION 2.8)
project(EconixExec)

#add_definitions( -Wall )

include_directories( "." )


set( UTILITY_SRCS
     transactionblob.h
	 transactionblob.cpp
   )

add_library(utility ${UTILITY_SRCS})
target_link_libraries(utility)