cmake_minimum_required(VERSION 3.25)

project(log4cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set_source_files_properties(PROPERTIES LANGUAGE CXX)

add_compile_options(
  "-Wall" "-Wpedantic" "-Wextra" "-fexceptions"
  "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb>"
)

set(IS_LIBRARY, true)

if(!IS_LIBRARY)
  add_executable(
    ${PROJECT_NAME}
    log4cpp.cpp
  )
else()
  add_library(
    ${PROJECT_NAME}
    log4cpp.cpp
  )
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ../include)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

if(FILE-INSPECTOR_PROJECT_BUILD_TESTING)
  add_subdirectory(../tests)
endif()

# target_link_libraries(${PROJECT_NAME} PUBLIC yaml-cpp::yaml-cpp systemd)
set(CMAKE_C_FLAGS_DEBUG "-g -DDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")
