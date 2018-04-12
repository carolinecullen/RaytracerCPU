cmake_minimum_required(VERSION 2.8)

project(raytrace)

file(GLOB_RECURSE SOURCES "src/*.cpp")

file(GLOB_RECURSE HEADERS "src/*.h")

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES} ${HEADERS})

if(WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4996")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall -pedantic")
endif()