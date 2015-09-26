cmake_minimum_required (VERSION 2.6) 
project (Nyx)

file(GLOB_RECURSE Nyx_SRC
  "src/*.h"
  "src/*.cc"
)
set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")
add_executable(nyx ${Nyx_SRC})
