cmake_minimum_required (VERSION 2.6) 
project (Nyx)

# The version number.
set (Nyx_VERSION_MAJOR 0)
set (Nyx_VERSION_MINOR 1)

set(CMAKE_CXX_FLAGS "-std=c++11")

# Add project root directory to CMake module path
list( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR} )

################################################################################
# GTest
# See: http://code.google.com/p/googletest/
################################################################################
message (STATUS "Setting up GTest")
if (CMAKE_USE_PTHREADS_INIT)  # The pthreads library is available and allowed.
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGTEST_HAS_PTHREAD=1")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGTEST_HAS_PTHREAD=0")
endif()
set(GTEST_DIR "third_party/gtest")
set(GTEST_INCLUDE_DIRECTORIES ${GTEST_DIR}/include ${GTEST_DIR}
    ${GTEST_DIR}/src)
include_directories(${GTEST_INCLUDE_DIRECTORIES})
add_library(gtest ${GTEST_DIR}/src/gtest-all.cc ${GTEST_DIR}/src/gtest_main.cc)
enable_testing(true)

################################################################################
# Boost 
# See: http://www.boost.org/
################################################################################
message (STATUS "Setting up Boost paths")
set(Boost_USE_STATIC_LIBS ON) # only find static libs
find_package(Boost REQUIRED COMPONENTS filesystem system)
include_directories(${Boost_INCLUDE_DIRS})

################################################################################
# Threading Building Blocks 
# See: http://www.threadingbuildingblocks.org
################################################################################
message (STATUS "Setting up TBB paths")
find_package(TBB REQUIRED)
if (TBB_FOUND)
  message(STATUS "TBB is found installed in the path:" ${TBB_ROOT})
  set(TBB_LIBRARIES ${TBB_LIBRARY};${TBB_LIBRARY_MALLOC})  
else ()
  message(FATAL_ERROR
      "TBB not found. Install TBB and set TBB_ROOT env variable")
endif()

# find all compilable files
file(GLOB_RECURSE Nyx_ALL_SRC
  "src/*.h"
  "src/*.cc"
)

# find all tests
file(GLOB_RECURSE Nyx_TESTS_SRC
  "src/*test.cc"
)

# subtract tests from all files
foreach(test ${Nyx_TESTS_SRC})
  list(REMOVE_ITEM Nyx_ALL_SRC ${test})
endforeach()

include_directories("src")
include_directories("third_party")

set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

add_library(libnyx STATIC ${Nyx_ALL_SRC})

add_executable(nyx_testrunner "testing/testrunner.cc" ${Nyx_TESTS_SRC})
TARGET_LINK_LIBRARIES(nyx_testrunner libnyx gtest ${TBB_LIBRARIES})
