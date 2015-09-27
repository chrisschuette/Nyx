cmake_minimum_required (VERSION 2.6) 
project (Nyx)

# The version number.
set (Nyx_VERSION_MAJOR 0)
set (Nyx_VERSION_MINOR 1)

################################################################################
# GTest
# See: http://code.google.com/p/googletest/
################################################################################
if (CMAKE_USE_PTHREADS_INIT)  # The pthreads library is available and allowed.
	  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGTEST_HAS_PTHREAD=1")
  else()
	    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGTEST_HAS_PTHREAD=0")
    endif()
    set(GTEST_DIR "third_party/gtest-1.7.0")
    set(GTEST_INCLUDE_DIRECTORIES ${GTEST_DIR}/include ${GTEST_DIR}
	    ${GTEST_DIR}/src)
    include_directories(${GTEST_INCLUDE_DIRECTORIES})
    add_library(gtest ${GTEST_DIR}/src/gtest-all.cc ${GTEST_DIR}/src/gtest_main.cc)
    enable_testing(true)

file(GLOB_RECURSE Nyx_SRC
  "src/*.h"
  "src/*.cc"
)

set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

add_library(libnyx STATIC ${Nyx_SRC})

add_executable(nyx_testrunner "testing/testrunner.cc")
TARGET_LINK_LIBRARIES(nyx_testrunner libnyx gtest)
