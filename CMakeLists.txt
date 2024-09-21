cmake_minimum_required(VERSION 3.25)

project(log4cpp
  VERSION 0.1.0 # https://semver.org/spec/v0.1.0.html
  DESCRIPTION "Log for CPP"
)

project(log4cpp LANGUAGES CXX)

if(LOG4CPP_PROJECT_BUILD_TESTING)
  enable_testing()
  # or alternatively, `include(CTest)`, if you want to use CDash
  # https://cmake.org/cmake/help/book/mastering-cmake/chapter/CDash.html
endif()

set(BUILD_SHARED_AND_STATIC_LIBS ON)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../yaml-cpp ./src/Debug)
add_subdirectory(src)