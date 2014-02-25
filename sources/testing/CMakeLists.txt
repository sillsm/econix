## CMakeLists.txt
option(Econix_build_cpp_tests "Build all of foo's c++ unit tests." ON)
project(EconixCPlusPlusTesting)
cmake_minimum_required(VERSION 2.8)
include_directories("/usr/local/include")
link_directories("/usr/local/lib")
set(cpp_testing_SOURCES
    main.cpp
	)
	
########################### GTEST
# Enable ExternalProject CMake module
INCLUDE(ExternalProject)
 
# Set default ExternalProject root directory
SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/third_party)
 
# Add gtest
# http://stackoverflow.com/questions/9689183/cmake-googletest
ExternalProject_Add(
    googletest
    URL http://googletest.googlecode.com/files/gtest-1.6.0.zip

    # TIMEOUT 10
    # # Force separate output paths for debug and release builds to allow easy
    # # identification of correct lib in subsequent TARGET_LINK_LIBRARIES commands
     CMAKE_ARGS -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=DebugLibs
                -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=ReleaseLibs
                -Dgtest_force_shared_crt=ON
    # Disable install step
    INSTALL_COMMAND ""
    # Wrap download, configure and build steps in a script to log output
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON)
	
 # Specify include dir
ExternalProject_Get_Property(googletest source_dir)
include_directories(${source_dir}/include)

# Add compiler flag for MSVC 2012
if(MSVC_VERSION EQUAL 1700)
  add_definitions(-D_VARIADIC_MAX=10)
endif()

SET(CMAKE_CXX_FLAGS_DEBUG "/MTd")

# Add test executable target
#add_executable(MainTest ${PROJECT_SOURCE_DIR}/src/main.cpp)

# Create dependency of MainTest on googletest
#add_dependencies(MainTest googletest)

# Specify MainTest's link libraries


#END add gtest

if (Econix_build_cpp_tests)
    enable_testing()
	include_directories(${GTEST_INCLUDE_DIR})
    add_executable(CppTesting ${cpp_testing_SOURCES} )
	add_dependencies(CppTesting googletest)

ExternalProject_Get_Property(googletest binary_dir)
if(MSVC)
  set(Suffix ".lib")
else()
  set(Suffix ".a")
  set(Pthread "-pthread")
endif()
target_link_libraries(
    CppTesting
    debug ${binary_dir}/Debug/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${Suffix}
    optimized ${binary_dir}/Release/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${Suffix}
    ${Pthread})

endif()
