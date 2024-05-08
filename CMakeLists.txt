cmake_minimum_required(VERSION 3.16.3)
project(protoc-gen-spicy)
set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

#set(CMAKE_VERBOSE_MAKEFILE ON)
if(MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(
    -Wall -Wextra -Wpedantic -Werror
    $<$<CONFIG:RELEASE>:-Ofast>
    $<$<CONFIG:DEBUG>:-O0>
    $<$<CONFIG:DEBUG>:-ggdb3>
  )
endif()

include_directories(include)
include_directories(src)
#set("${CMAKE_PROJECT_NAME}_SRC"
#)
#add_executable(${CMAKE_PROJECT_NAME} ${${CMAKE_PROJECT_NAME}_SRC})

option(PGS_BUILD_EXAMPLES "Include examples in the build" OFF)

if(PGS_BUILD_EXAMPLES)
  add_subdirectory(examples/)
endif()
