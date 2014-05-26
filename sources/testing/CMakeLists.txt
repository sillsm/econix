## CMakeLists.txt
include_directories(..)
option(Econix_build_cpp_tests "Build all of Econix's c++ unit tests." ON)
project(EconixCPlusPlusTesting)
cmake_minimum_required(VERSION 2.8)
include_directories("/usr/local/include")
link_directories("/usr/local/lib")


########################### GTEST

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

Message(inner CMAKE)
Message(${Boost_INCLUDE_DIRS})
Message(${Boost_LIBRARY_DIRS})
Message(inner CMAKE)


