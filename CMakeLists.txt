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
    set(GTEST_DIR "testing/gtest")
    set(GTEST_INCLUDE_DIRECTORIES ${GTEST_DIR}/include ${GTEST_DIR}
	    ${GTEST_DIR}/src)
    include_directories(${GTEST_INCLUDE_DIRECTORIES})
    add_library(gtest ${GTEST_DIR}/src/gtest-all.cc ${GTEST_DIR}/src/gtest_main.cc)
    enable_testing(true)

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
include_directories(".")

set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

add_library(libnyx STATIC ${Nyx_ALL_SRC})

add_executable(nyx_testrunner "testing/testrunner.cc" ${Nyx_TESTS_SRC})
TARGET_LINK_LIBRARIES(nyx_testrunner libnyx gtest)
