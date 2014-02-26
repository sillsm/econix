cmake_minimum_required(VERSION 2.8)
project(EconixExec)

#add_definitions( -Wall )

include_directories( "." )


set( EXEC_SRCS
     main.cpp
   )

add_executable( execproj ${EXEC_SRCS} )
target_link_libraries( execproj)

